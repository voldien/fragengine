#include <Core/Math.h>
#include"Scene/SubGraph/Transform.h"
using namespace fragcore;
using namespace fragengine;

Transform::Transform(void)
{
	this->pos = PVVector3(0.0f);
	this->scale = PVVector3(1.0f);
	this->quat = PVQuaternion::identity();
}

void Transform::rotate(const PVVector3 &eular) {
	PVQuaternion rotation = PVQuaternion::createQuaternionOfAxis(
			(float) HPM_DEG2RAD(eular.x()),
			(float) HPM_DEG2RAD(eular.y()),
			(float) HPM_DEG2RAD(eular.z()));
	PVQuaternion rotat = this->getRotation() * rotation;
	rotat.makeUnitQuaternion();
	this->setRotation(rotat);
}


void Transform::setPosition(const PVVector3 &pos) {
//	int i;
//
//	/*	Update rest of the nodes.	*/
//	for(i = 0; i < this->getNumChildren(); i++){
//		Node* c = this->getChild(i);
//		//c->setPosition((getPosition() - pos) + c->getPosition());
//	}
//
//	this->pos = pos;
}

void Transform::setLocalPosition(const PVVector3 &pos) {

}

void Transform::setScale(const PVVector3 &scale) {
	this->scale = scale;
}

void Transform::setLocalScale(const PVVector3 &scale) {

}


void Transform::setRotation(const PVQuaternion &quat) {
	this->quat = quat;
}

void Transform::setLocalRotation(const PVQuaternion &quat) {

//	if(this->getParent()){
//		PVVector3 old = this->getRotation().forward();
//		this->quat = quat * this->getRotation().conjugate() * this->getRotation(); // setRotation * getLocalRotation();
//		this->quat.makeUnitQuaternion();
//		PVVector3 newrotat = this->getRotation().forward();
//		for(unsigned int x = 0; x < this->getNumChildren(); x++){			//send transform position information to children.
//			//this->child(x)->SetLocalRotationTransformation(this->rotation,newrotat - old);
//		}
//	}
//	else{
//		PVVector3 old = this->getRotation().forward();
//		this->quat = quat * this->getRotation().conjugate() * this->getRotation(); // setRotation * getLocalRotation();
//		this->quat.makeUnitQuaternion();
//		PVVector3 newrotat = this->getRotation().forward();
//		for(unsigned int x = 0; x < this->getNumChildren(); x++){			//send transform position information to children.
//			//	this->children[x]->SetLocalRotationTransformation(this->_rotation,old - newrotat);
//
//		}
//	}
}

const PVQuaternion &Transform::getRotation(void) const {

	return this->quat;
}

PVQuaternion Transform::getLocalRotation(void) const {

}

PVMatrix4x4 Transform::getMatrix(void) const {
	return PVMatrix4x4::translate(this->getPosition()) *
	       PVMatrix4x4::rotate(this->getRotation()) *
	       PVMatrix4x4::scale(this->getScale());
}

PVMatrix4x4 Transform::getLocalMatrix(void) const {
	return PVMatrix4x4::translate(this->getLocalPosition()) *
	       PVMatrix4x4::rotate(this->getLocalRotation()) *
	       PVMatrix4x4::scale(this->getLocalScale());
}

PVMatrix4x4 Transform::getViewMatrix(void) const {
	/*  TODO resolve camera and non camerae view matrix.    */
	return PVMatrix4x4::rotate(this->getRotation().conjugate()) *
	       PVMatrix4x4::translate(-this->getPosition()) *
	       PVMatrix4x4::scale(this->getScale());
}

PVMatrix4x4 Transform::getViewLocalMatrix(void) const {
	return PVMatrix4x4::translate(-this->getLocalPosition()) *
	       PVMatrix4x4::rotate(this->getLocalRotation().conjugate()) *
	       PVMatrix4x4::scale(-this->getLocalScale());
}

float Transform::getMinimumScale(void) const {
	return minScale;
}

float Transform::getMaximumScale(void) const {
	return maxScale;
}

void Transform::setMinimumScale(float min) {
	this->minScale = min;
}

void Transform::setMaximumScale(float max) {
	this->maxScale = max;

	float x = Math::clamp(this->getScale().x(), getMinimumScale(), getMaximumScale());
	float y = Math::clamp(this->getScale().y(), getMinimumScale(), getMaximumScale());
	float z = Math::clamp(this->getScale().z(), getMinimumScale(), getMaximumScale());

	PVVector3 clampedScale = PVVector3(x,y,z);
	this->setScale(clampedScale);
}

//PVMatrix3x3 &Transform::getBasis(void) {
//	return PVMatrix3x3();
//}
//
//const PVMatrix3x3 &Transform::getBasis(void) const {
//	return PVMatrix3x3();
//}

Transform &Transform::operator*=(const Transform &t) {
	return *this;
}

Transform Transform::operator*(const Transform &t) const {
	return Transform();
}

PVVector3 Transform::operator()(const PVVector3 &x) const {
	return PVVector3();
}

PVVector3 Transform::operator*(const PVVector3 &x) const {
	return PVVector3();
}

PVQuaternion Transform::operator*(const PVQuaternion &q) const {
	return PVQuaternion();
}
