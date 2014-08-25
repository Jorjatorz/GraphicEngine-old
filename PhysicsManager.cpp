#include "PhysicsManager.h"

#include "RigidBody.h"
#include "SceneNode.h"
#include "Entity.h"

PhysicsManager::PhysicsManager()
{
}


PhysicsManager::~PhysicsManager()
{
	delete mBulletDebugDrawer;
	delete mBulletDynamicWorld;
	delete mBulletSolver;
	delete mBulletDispatcher;
	delete mBulletCollisionConfig;
	delete mBulletBroadphase;
}

void PhysicsManager::initPhysicsWorld()
{
	mBulletBroadphase = new btDbvtBroadphase(); //The broadphase is an excellent place for eliminating object pairs that should not collide.
	//The collision configuration allows you to fine tune the algorithms used for the full (not broadphase) collision detection.
	mBulletCollisionConfig = new btDefaultCollisionConfiguration();
	mBulletDispatcher = new btCollisionDispatcher(mBulletCollisionConfig);

	btGImpactCollisionAlgorithm::registerAlgorithm(mBulletDispatcher);	//f you introduce different types of collision object later (eg meshes using btGImpactMeshShape) then you may need to register a collision algorithm to get collisions recognised
	
	mBulletSolver = new btSequentialImpulseConstraintSolver;//This is what causes the objects to interact properly, taking into account gravity, game logic supplied forces, collisions, and hinge constraints.

	mBulletDynamicWorld = new btDiscreteDynamicsWorld(mBulletDispatcher, mBulletBroadphase, mBulletSolver, mBulletCollisionConfig);

	//Set the gravity
	mBulletDynamicWorld->setGravity(btVector3(0.0, -9.8, 0.0));

	//Drawer
	mBulletDebugDrawer = new GLDebugDrawer();
	mBulletDebugDrawer->setDebugMode(mBulletDebugDrawer->DBG_DrawWireframe);
	mBulletDynamicWorld->setDebugDrawer(mBulletDebugDrawer);
}


RigidBody* PhysicsManager::createRigidBody(std::string name)
{
	tRigidBodiesMap::iterator it = mRigidBodiesMap.find(name);

	if (it != mRigidBodiesMap.end())
	{
		return it->second;
	}

	RigidBody* newRigidBody = new RigidBody(name, mBulletDynamicWorld);

	mRigidBodiesMap.insert(std::pair<std::string, RigidBody*>(name, newRigidBody));

	return newRigidBody;
}

void PhysicsManager::processPhysicsWorld(real deltaTime)
{
	mBulletDynamicWorld->stepSimulation(deltaTime, 1.0);
	//mBulletDynamicWorld->debugDrawWorld(); Sacar de los demos de bullet

	tRigidBodiesMap::iterator it;
	for (it = mRigidBodiesMap.begin(); it != mRigidBodiesMap.end(); ++it)
	{
		btTransform worldTrans;
		it->second->getWorldTransform(worldTrans);
		btVector3 pos = worldTrans.getOrigin();
		btQuaternion rot = worldTrans.getRotation();

		it->second->getUserPointer()->getAttachedSceneNode()->setPosition(glm::vec3(pos.x(), pos.y(), pos.z()));
		if (it->second->getMass() != 0.0)
			it->second->getUserPointer()->getAttachedSceneNode()->setOrientation(glm::quat(rot.w(), rot.x(), rot.y(), rot.z()));

		
	}
}

void PhysicsManager::draw()
{
	mBulletDynamicWorld->debugDrawWorld();
}