#pragma once

#include "btBulletDynamicsCommon.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtx/quaternion.hpp"

enum CollisionShape
{
	BOX, SPHERE, CYLINDER, CONVEX_HULL
};

class Physics
{
public:
	static void Initialize();
	static void AddRigidBody(void* pointer, glm::vec3 position, glm::vec3 orientation, float mass, CollisionShape shape, glm::vec3 half_extents);
	static void CastRay(glm::vec3 out_origin, glm::vec3 out_dir);

private:
	static btDefaultCollisionConfiguration* collision_configuration_;
	static btCollisionDispatcher* dispatcher_;
	static btBroadphaseInterface* overlapping_pair_cache_;
	static btSequentialImpulseConstraintSolver* solver_;
	static btDiscreteDynamicsWorld* dynamics_world_;
};