#include <Core/Math.h>
#include"Scene/SubGraph/Transform.h"
using namespace fragcore;
using namespace fragengine;

Transform::Transform(void)
{
	this->pos = Vector3(0.0f);
	this->scale = Vector3(1.0f);
	this->quat = Quaternion::identity();
}

void Transform::rotate(const Vector3 &eular) {
	Quaternion rotation = Quaternion::createQuaternionOfAxis(
			(float) HPM_DEG2RAD(eular.x()),
			(float) HPM_DEG2RAD(eular.y()),
			(float) HPM_DEG2RAD(eular.z()));
	Quaternion rotat = this->getRotation() * rotation;
	rotat.makeUnitQuaternion();
	this->setRotation(rotat);
}


void Transform::setPosition(const Vector3 &pos) {
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

void Transform::setLocalPosition(const Vector3 &pos) {

}

void Transform::setScale(const Vector3 &scale) {
	this->scale = scale;
}

void Transform::setLocalScale(const Vector3 &scale) {

}


void Transform::setRotation(const Quaternion &quat) {
	this->quat = quat;
}

void Transform::setLocalRotation(const Quaternion &quat) {

//	if(this->getParent()){
//		Vector3 old = this->getRotation().forward();
//		this->quat = quat * this->getRotation().conjugate() * this->getRotation(); // setRotation * getLocalRotation();
//		this->quat.makeUnitQuaternion();
//		Vector3 newrotat = this->getRotation().forward();
//		for(unsigned int x = 0; x < this->getNumChildren(); x++){			//send transform position information to children.
//			//this->child(x)->SetLocalRotationTransformation(this->rotation,newrotat - old);
//		}
//	}
//	else{
//		Vector3 old = this->getRotation().forward();
//		this->quat = quat * this->getRotation().conjugate() * this->getRotation(); // setRotation * getLocalRotation();
//		this->quat.makeUnitQuaternion();
//		Vector3 newrotat = this->getRotation().forward();
//		for(unsigned int x = 0; x < this->getNumChildren(); x++){			//send transform position information to children.
//			//	this->children[x]->SetLocalRotationTransformation(this->_rotation,old - newrotat);
//
//		}
//	}
}

const Quaternion &Transform::getRotation(void) const {

	return this->quat;
}

Quaternion Transform::getLocalRotation(void) const {

}

Matrix4x4 Transform::getMatrix(void) const {
	return Matrix4x4::translate(this->getPosition()) *
	       Matrix4x4::rotate(this->getRotation()) *
	       Matrix4x4::scale(this->getScale());
}

Matrix4x4 Transform::getLocalMatrix(void) const {
	return Matrix4x4::translate(this->getLocalPosition()) *
	       Matrix4x4::rotate(this->getLocalRotation()) *
	       Matrix4x4::scale(this->getLocalScale());
}

Matrix4x4 Transform::getViewMatrix(void) const {
	/*  TODO resolve camera and non camerae view matrix.    */
	return Matrix4x4::rotate(this->getRotation().conjugate()) *
	       Matrix4x4::translate(-this->getPosition()) *
	       Matrix4x4::scale(this->getScale());
}

Matrix4x4 Transform::getViewLocalMatrix(void) const {
	return Matrix4x4::translate(-this->getLocalPosition()) *
	       Matrix4x4::rotate(this->getLocalRotation().conjugate()) *
	       Matrix4x4::scale(-this->getLocalScale());
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

	Vector3 clampedScale = Vector3(x,y,z);
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

Vector3 Transform::operator()(const Vector3 &x) const {
	return Vector3();
}

Vector3 Transform::operator*(const Vector3 &x) const {
	return Vector3();
}

Quaternion Transform::operator*(const Quaternion &q) const {
	return Quaternion();
}
