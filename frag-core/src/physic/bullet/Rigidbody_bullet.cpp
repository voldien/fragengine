#include"physic/RigidBody.h"

#include<bullet/btBulletCollisionCommon.h>
#include<bullet/btBulletDynamicsCommon.h>
using namespace fragcore;

RigidBody::~RigidBody(void){}
float RigidBody::getMass(void* pobj){
	btRigidBody* body = (btRigidBody*)pobj;
	return 1.0f / body->getInvMass();
}
void RigidBody::setMass(void* pobj, float mass){
	btRigidBody* body = (btRigidBody*)pobj;

	btVector3 inertia;
	body->getCollisionShape()->calculateLocalInertia(mass, inertia);
}

PVVector3 RigidBody::getPosition(void* pobj){

	btRigidBody* body;
	btTransform trans;
	btMotionState* mot;

	body = (btRigidBody*)pobj;

	/**/
	mot = body->getMotionState();
	mot->getWorldTransform(trans);

	return *(PVVector3*)&trans.getOrigin();
}
void RigidBody::setPosition(void* pobj, const PVVector3& position){
	btRigidBody* body;
	body = (btRigidBody*)pobj;

	/*  Both internal and rigidbody.    */

}

PVQuaternion RigidBody::getOrientation(void* pobj){

	btRigidBody* body;
	btQuaternion oritention;
	body = (btRigidBody*)pobj;

	oritention = body->getOrientation();

	return PVQuaternion(oritention.getW(),
			oritention.getX(),
			oritention.getY(),
			oritention.getZ());
}
void RigidBody::setOrientation(void* pobj, const PVQuaternion& quat){
	btRigidBody* body;
	body = (btRigidBody*)pobj;
}


PVVector3 RigidBody::getScale(void* pobj){
	btRigidBody* body;
	body = (btRigidBody*)pobj;

	const btVector3 scale = body->getCollisionShape()->getLocalScaling();

	return PVVector3(scale.x(),scale.y(),scale.z());
}
void RigidBody::setScale(void* pobj, const PVVector3& scale){
	btRigidBody* body;
	body = (btRigidBody*)pobj;

	btVector3 sc = btVector3(scale.x(),scale.y(),scale.z());
	body->getCollisionShape()->setLocalScaling(sc);
}

void RigidBody::setForce(void* pobj, const PVVector3& force){
	btRigidBody* body;
	body = (btRigidBody*)pobj;
}

float RigidBody::getDrag(void* pobj){
	btRigidBody* body;
	body = (btRigidBody*)pobj;

	return body->getLinearDamping();
}
void RigidBody::setDrag(void*pobj, float drag){
	btRigidBody* body;
	body = (btRigidBody*)pobj;

	body->setDamping(drag, body->getAngularDamping());
}

float RigidBody::getAngularDrag(void* pobj){
	btRigidBody* body;
	body = (btRigidBody*)pobj;

	return body->getAngularDamping();
}
void RigidBody::setAngularDrag(void* pobj, float angularDrag){
	btRigidBody* body;
	body = (btRigidBody*)pobj;

	body->setDamping(body->getLinearDamping(), angularDrag);
}


PVVector3 RigidBody::getVelocity(void* pobj){
	btRigidBody* body;
	body = (btRigidBody*)pobj;

	const btVector3& linear = body->getLinearVelocity();
	return PVVector3(linear.x(),linear.y(),linear.z());
}

