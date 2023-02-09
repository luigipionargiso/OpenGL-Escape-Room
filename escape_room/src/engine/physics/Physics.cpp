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

void Physics::AddRigidBody(void* pointer, glm::vec3 position, glm::vec3 orientation, float mass, CollisionShape shape, glm::vec3 half_extents)
{
    btCollisionShape* boxCollisionShape = nullptr;

    switch (shape)
    {
    case BOX:
        boxCollisionShape = new btBoxShape(btVector3(half_extents.y, half_extents.z, half_extents.x));
        break;
    }

    /* convert euler angles in quaternion */
    auto quat_x = glm::angleAxis(orientation.y, glm::vec3(1.0, 0.0, 0.0));
    auto quat_y = glm::angleAxis(orientation.z, glm::vec3(0.0, 1.0, 0.0));
    auto quat_z = glm::angleAxis(orientation.x, glm::vec3(0.0, 0.0, 1.0));
    auto quat = quat_x * quat_y * quat_z;

    btDefaultMotionState* motionstate = new btDefaultMotionState(
        btTransform(
            btQuaternion(quat.x, quat.y, quat.z, quat.w),
            btVector3(position.y, position.z, position.x)
        )
    );

    btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
        mass,               /* 0 -> static object */
        motionstate,
        boxCollisionShape,
        btVector3(0, 0, 0)  /* local inertia */
    );

    btRigidBody* rigidBody = new btRigidBody(rigidBodyCI);
    rigidBody->setUserPointer(pointer);
    dynamics_world_->addRigidBody(rigidBody);
}

void Physics::CastRay(glm::vec3 ray_origin, glm::vec3 ray_direction)
{
    glm::vec3 ray_end = ray_origin + glm::normalize(ray_direction) * 1000.0f;

    btCollisionWorld::ClosestRayResultCallback RayCallback(
        btVector3(ray_origin.y, ray_origin.z, ray_origin.x),
        btVector3(ray_end.y, ray_end.z, ray_end.x)
    );
    dynamics_world_->rayTest(
        btVector3(ray_origin.y, ray_origin.z, ray_origin.x),
        btVector3(ray_end.y, ray_end.z, ray_end.x),
        RayCallback
    );

    if (RayCallback.hasHit()) {
        std::cout << "mesh " << (int)RayCallback.m_collisionObject->getUserPointer() << '\r';
    }
}
