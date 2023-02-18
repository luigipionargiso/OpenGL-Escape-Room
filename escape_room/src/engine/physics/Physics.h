#pragma once

#include "btBulletDynamicsCommon.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtx/quaternion.hpp"
#include <unordered_map>

typedef btRigidBody RigidBody;

struct RigidBodyTranform
{
	glm::vec3 position;
	glm::quat rotation;
};

enum CollisionShape
{
	BOX, SPHERE
};

enum RigidBodyAttribute
{
	RAY_VISIBILITY, COLLISION_VISIBILITY
};

class Physics
{
public:
	static void Initialize();
	static RigidBody* AddRigidBody(void* user_pointer, glm::vec3 position, glm::quat orientation, float mass, CollisionShape shape, glm::vec3 half_extents);
	static void UpdateRigidBody(RigidBody* pointer, glm::vec3 position, glm::quat orientation);
	static void RemoveRigidBody(RigidBody* pointer);
	static void SetLinearVelocity(RigidBody* rigid_body, glm::vec3 linear_velocity);
	static void SetRigidBodyAttribute(RigidBody* rigid_body, RigidBodyAttribute attribute, bool value);

	static void* CastRay(glm::vec3 out_origin, glm::vec3 out_dir);
	static bool CheckCollision(RigidBody* rigid_body);
	static RigidBodyTranform Simulate(RigidBody* rigid_body);

private:
	static btDefaultCollisionConfiguration* collision_configuration_;
	static btCollisionDispatcher* dispatcher_;
	static btBroadphaseInterface* overlapping_pair_cache_;
	static btSequentialImpulseConstraintSolver* solver_;
	static btDiscreteDynamicsWorld* dynamics_world_;

	static std::unordered_map<const btCollisionObject*, bool> ray_visibility_;
	static std::unordered_map<const btCollisionObject*, bool> collision_visibility_;
};