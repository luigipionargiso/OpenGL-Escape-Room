#include "Physics.h"
#include <iostream>

btDefaultCollisionConfiguration*  Physics::collision_configuration_ = nullptr;
btCollisionDispatcher* Physics::dispatcher_ = nullptr;
btBroadphaseInterface* Physics::overlapping_pair_cache_ = nullptr;
btSequentialImpulseConstraintSolver* Physics::solver_ = nullptr;
btDiscreteDynamicsWorld* Physics::dynamics_world_ = nullptr;

std::unordered_map<const btCollisionObject*, bool> Physics::ray_visibility_ = std::unordered_map<const btCollisionObject*, bool>();
std::unordered_map<const btCollisionObject*, bool> Physics::collision_visibility_ = std::unordered_map<const btCollisionObject*, bool>();


void Physics::Initialize()
{
    // collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
    collision_configuration_ = new btDefaultCollisionConfiguration();

    // use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
    dispatcher_ = new btCollisionDispatcher(collision_configuration_);

    // btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
    overlapping_pair_cache_ = new btDbvtBroadphase();

    // the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
    solver_ = new btSequentialImpulseConstraintSolver;

    dynamics_world_ = new btDiscreteDynamicsWorld(
        dispatcher_,
        overlapping_pair_cache_,
        solver_,
        collision_configuration_
    );

    dynamics_world_->setGravity(btVector3(0, -9.81f, 0));
}

RigidBody* Physics::AddRigidBody(void* user_pointer, glm::vec3 position, glm::quat orientation, float mass, CollisionShape shape, glm::vec3 half_extents)
{
    btCollisionShape* collision_shape = nullptr;

    switch (shape)
    {
        case BOX:
            collision_shape = new btBoxShape(btVector3(half_extents.x, half_extents.y, half_extents.z));
            break;
        case SPHERE:
            collision_shape = new btSphereShape(half_extents.x);
            break;
    }

    btDefaultMotionState* motionstate = new btDefaultMotionState(
        btTransform(
            btQuaternion(orientation.x, orientation.y, orientation.z, orientation.w),
            btVector3(position.x, position.y, position.z)
        )
    );

    btVector3 local_inertia(0, 0, 0);
    if (mass > 0 && collision_shape)
        collision_shape->calculateLocalInertia(mass, local_inertia);

    btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
        mass,               /* 0 -> static object */
        motionstate,
        collision_shape,
        local_inertia
    );

    btRigidBody* rigid_body = new btRigidBody(rigidBodyCI);
    rigid_body->setUserPointer(user_pointer);
    dynamics_world_->addRigidBody(rigid_body);

    ray_visibility_[rigid_body] = true;
    collision_visibility_[rigid_body] = true;

    return rigid_body;
}

void Physics::UpdateRigidBody(RigidBody* pointer, glm::vec3 position, glm::quat orientation)
{
    btDefaultMotionState* motion_state = new btDefaultMotionState(
        btTransform(
            btQuaternion(orientation.x, orientation.y, orientation.z, orientation.w),
            btVector3(position.x, position.y, position.z)
        )
    );
    pointer->setMotionState(motion_state);
    dynamics_world_->updateAabbs();
}

void Physics::RemoveRigidBody(RigidBody* pointer)
{
    dynamics_world_->removeRigidBody(pointer);
}

void Physics::SetLinearVelocity(RigidBody* rigid_body, glm::vec3 linear_velocity)
{
    btVector3 velocity = btVector3(linear_velocity.x, linear_velocity.y, linear_velocity.z) * 2.0;
    rigid_body->setLinearVelocity(velocity);
}

void Physics::SetRigidBodyAttribute(RigidBody* rigid_body, RigidBodyAttribute attribute, bool value)
{
    switch (attribute)
    {
    case RAY_VISIBILITY:
        ray_visibility_[rigid_body] = value;
        break;
    case COLLISION_VISIBILITY:
        collision_visibility_[rigid_body] = value;
        break;
    }
}

void* Physics::CastRay(glm::vec3 ray_origin, glm::vec3 ray_direction)
{
    glm::vec3 ray_end = ray_origin + glm::normalize(ray_direction) * 1000.0f;

    btCollisionWorld::ClosestRayResultCallback RayCallback(
        btVector3(ray_origin.x, ray_origin.y, ray_origin.z),
        btVector3(ray_end.x, ray_end.y, ray_end.z)
    );
    dynamics_world_->rayTest(
        btVector3(ray_origin.x, ray_origin.y, ray_origin.z),
        btVector3(ray_end.x, ray_end.y, ray_end.z),
        RayCallback
    );

    if (RayCallback.hasHit() && ray_visibility_[RayCallback.m_collisionObject])
        return RayCallback.m_collisionObject->getUserPointer();
    else
        return nullptr;
}

bool Physics::CheckCollision(RigidBody* rigid_body)
{
    bool result = false;
    dynamics_world_->performDiscreteCollisionDetection();
    int numManifolds = dynamics_world_->getDispatcher()->getNumManifolds();

    for (int i = 0; i < numManifolds; i++)
    {
        btPersistentManifold* contact_manifold = dynamics_world_->getDispatcher()->getManifoldByIndexInternal(i);
        const btCollisionObject* b0 = contact_manifold->getBody0();
        const btCollisionObject* b1 = contact_manifold->getBody1();

        if (contact_manifold->getNumContacts() == 0)
            contact_manifold->clearManifold();

        if (b0 == rigid_body && collision_visibility_[b1])
        {
            result = true;
            break;
        }
        else if (b1 == rigid_body && collision_visibility_[b0])
        {
            result = true;
            break;
        }
    }

    dynamics_world_->updateAabbs();
    return result;
}

RigidBodyTranform Physics::Simulate(RigidBody* rigid_body)
{
    dynamics_world_->stepSimulation(1.f / 60.f, 1);
    btTransform trans;
    rigid_body->getMotionState()->getWorldTransform(trans);
    RigidBodyTranform result
    {
        glm::vec3(float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ())),
        glm::quat((float)trans.getRotation().getW(), (float)trans.getRotation().getX(), (float)trans.getRotation().getY(), (float)trans.getRotation().getZ())
    };
    return result;
}
