#include "Scene/SubGraph/Transform.h"
#include <Core/Math.h>
using namespace fragcore;
using namespace fragengine;

Transform::Transform() {
	this->pos = Vector3();
	this->scale = Vector3();
	this->quat = Quaternion();
}

void Transform::rotate(const Vector3 &eular) {
	Quaternion rotation; // = Quaternion::createQuaternionOfAxis(
	// 	Math::deg2RadHPM_DEG2RAD(eular.x()), Math::deg2Rad(eular.y()), Math::deg2Rad<float>(eular.z()));
	Quaternion rotat = this->getRotation() * rotation;
	rotat.normalized();
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

void Transform::setLocalPosition(const Vector3 &pos) {}

void Transform::setScale(const Vector3 &scale) { this->scale = scale; }

void Transform::setLocalScale(const Vector3 &scale) {}

void Transform::setRotation(const Quaternion &quat) { this->quat = quat; }

void Transform::setLocalRotation(const Quaternion &quat) {

	//	if(this->getParent()){
	//		Vector3 old = this->getRotation().forward();
	//		this->quat = quat * this->getRotation().conjugate() * this->getRotation(); // setRotation *
	// getLocalRotation(); 		this->quat.makeUnitQuaternion(); 		Vector3 newrotat =
	// this->getRotation().forward(); 		for(unsigned int x = 0; x < this->getNumChildren(); x++){			//send
	// transform
	// position information to children.
	//			//this->child(x)->SetLocalRotationTransformation(this->rotation,newrotat - old);
	//		}
	//	}
	//	else{
	//		Vector3 old = this->getRotation().forward();
	//		this->quat = quat * this->getRotation().conjugate() * this->getRotation(); // setRotation *
	// getLocalRotation(); 		this->quat.makeUnitQuaternion(); 		Vector3 newrotat =
	// this->getRotation().forward(); 		for(unsigned int x = 0; x < this->getNumChildren(); x++){			//send
	// transform
	// position information to children.
	//			//	this->children[x]->SetLocalRotationTransformation(this->_rotation,old - newrotat);
	//
	//		}
	//	}
}

const Quaternion &Transform::getRotation() const { return this->quat; }

Quaternion Transform::getLocalRotation() const {}

Matrix4x4 Transform::getMatrix() const {
	Eigen::Translation<float, 3>(this->getPosition());
	// return Matrix4x4::translate(this->getPosition()) * Matrix4x4::rotate(this->getRotation()) *
	// 	   Matrix4x4::scale(this->getScale());
}

Matrix4x4 Transform::getLocalMatrix() const {
	// return Matrix4x4::translate(this->getLocalPosition()) * Matrix4x4::rotate(this->getLocalRotation()) *
	// 	   Matrix4x4::scale(this->getLocalScale());
}

Matrix4x4 Transform::getViewMatrix() const {
	/*  TODO resolve camera and non camerae view matrix.    */
	// return Matrix4x4::rotate(this->getRotation().conjugate()) * Matrix4x4::translate(-this->getPosition()) *
	// 	   Matrix4x4::scale(this->getScale());
}

Matrix4x4 Transform::getViewLocalMatrix() const {
	// return Matrix4x4::translate(-this->getLocalPosition()) * Matrix4x4::rotate(this->getLocalRotation().conjugate())
	// * 	   Matrix4x4::scale(-this->getLocalScale());
}

float Transform::getMinimumScale() const { return minScale; }

float Transform::getMaximumScale() const { return maxScale; }

void Transform::setMinimumScale(float min) { this->minScale = min; }

void Transform::setMaximumScale(float max) {
	this->maxScale = max;

	float x = Math::clamp(this->getScale().x(), getMinimumScale(), getMaximumScale());
	float y = Math::clamp(this->getScale().y(), getMinimumScale(), getMaximumScale());
	float z = Math::clamp(this->getScale().z(), getMinimumScale(), getMaximumScale());

	Vector3 clampedScale = Vector3(x, y, z);
	this->setScale(clampedScale);
}

// PVMatrix3x3 &Transform::getBasis() {
//	return PVMatrix3x3();
//}
//
// const PVMatrix3x3 &Transform::getBasis() const {
//	return PVMatrix3x3();
//}

Transform &Transform::operator*=(const Transform &t) { return *this; }

Transform Transform::operator*(const Transform &t) const { return Transform(); }

Vector3 Transform::operator()(const Vector3 &x) const { return Vector3(); }

Vector3 Transform::operator*(const Vector3 &x) const { return Vector3(); }

Quaternion Transform::operator*(const Quaternion &q) const { return Quaternion(); }
