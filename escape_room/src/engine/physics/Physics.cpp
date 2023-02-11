#include "Physics.h"
#include <iostream>

btDefaultCollisionConfiguration*  Physics::collision_configuration_ = nullptr;
btCollisionDispatcher* Physics::dispatcher_ = nullptr;
btBroadphaseInterface* Physics::overlapping_pair_cache_ = nullptr;
btSequentialImpulseConstraintSolver* Physics::solver_ = nullptr;
btDiscreteDynamicsWorld* Physics::dynamics_world_ = nullptr;

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

RigidBody* Physics::AddRigidBody(void* pointer, glm::vec3 position, glm::quat orientation, float mass, CollisionShape shape, glm::vec3 half_extents)
{
    btCollisionShape* collision_shape = nullptr;

    switch (shape)
    {
        case BOX:
            collision_shape = new btBoxShape(btVector3(half_extents.x, half_extents.y, half_extents.z));
            break;
        case CYLINDER:
            collision_shape = new btCylinderShape(btVector3(half_extents.x, half_extents.y, half_extents.z));
            break;
    }

    btDefaultMotionState* motionstate = new btDefaultMotionState(
        btTransform(
            btQuaternion(orientation.x, orientation.y, orientation.z, orientation.w),
            btVector3(position.x, position.y, position.z)
        )
    );

    btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
        mass,               /* 0 -> static object */
        motionstate,
        collision_shape,
        btVector3(0, 0, 0)  /* local inertia */
    );

    btRigidBody* rigidBody = new btRigidBody(rigidBodyCI);
    rigidBody->setUserPointer(pointer);
    dynamics_world_->addRigidBody(rigidBody);

    return rigidBody;
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

    if (RayCallback.hasHit())
        return RayCallback.m_collisionObject->getUserPointer();
    else
        return nullptr;
}
