#include "Scene/SubGraph/Frustum.h"
#include "Core/Math.h"

using namespace fragcore;
using namespace fragengine;

Frustum::Frustum() {
	//	this->setObjectType(Object::eFrustum);
	/*  Default frustum value.  */
	this->Zfar = 1000.0f;
	this->Znear = 0.15f;
	this->ratio = 1.33333f;
	this->setFov(70.0f);
}

Frustum::Frustum(const Frustum &other) { /**this = other;*/
}

const Matrix4x4 &Frustum::getPerspectiveMatrix() const { return this->percmatrix; }

void Frustum::setFov(float fov) {
	this->fov = Math::deg2Rad(fov);
	this->updatePerspective();
}

void Frustum::setNear(float near) {
	this->Znear = near;
	this->updatePerspective();
}

void Frustum::setFar(float far) {
	this->Zfar = far;
	this->updatePerspective();
}

void Frustum::setRatio(float ratio) {
	this->ratio = ratio;
	this->updatePerspective();
}

float Frustum::getFov() const { return Math::radToDeg(this->fov); }

float Frustum::getNear() const { return this->Znear; }

float Frustum::getFar() const { return this->Zfar; }

float Frustum::getRatio() const { return this->ratio; }

void Frustum::updatePerspective() {
	// this->percmatrix = Matrix4x4::perspective(this->getFov(), this->getRatio(), this->getNear(), this->getFar());
	const Transform &transform = this->local;

	/*	*/
	// calcFrustumPlanes(transform.getPosition(), transform.getRotation().getVector(),
	//                   transform.getRotation().getVector(Vector3::up()),
	//                   transform.getRotation().getVector(Vector3::right()));
}

void Frustum::calcFrustumPlanes(const Vector3 &position, const Vector3 &look, const Vector3 &up, const Vector3 &right) {
	Vector3 dir, nc, fc, X, Y, Z;

	planes[NEARP].setNormalAndPoint(-Z, nc);
	planes[FARP].setNormalAndPoint(Z, fc);

	Vector3 aux, normal;

	aux = (nc + Y * nh) - position;
	aux.normalize();
	normal = aux.cross(X);
	planes[TOPP].setNormalAndPoint(normal, nc + Y * nh);

	aux = (nc - Y * nh) - position;
	aux.normalize();
	normal = X.cross(aux);
	planes[BOTTOMP].setNormalAndPoint(normal, nc - Y * nh);

	aux = (nc - X * nw) - position;
	aux.normalize();
	normal = aux.cross(Y);
	planes[LEFTP].setNormalAndPoint(normal, nc - X * nw);

	aux = (nc + X * nw) - position;
	aux.normalize();
	normal = Y.cross(aux);
	planes[RIGHTP].setNormalAndPoint(normal, nc + X * nw);
}

Frustum::Intersection Frustum::checkPoint(const Vector3 &pos) const {
	int x;

	/*	Iterate through each plane.	*/
	for (x = 0; x < 6; x++) {
		if (planes[x].distance(pos) < 0) {
			return Out;
		}
	}
	return In;
}

Frustum::Intersection Frustum::intersectionAABB(const Vector3 &min, const Vector3 &max) {

	Frustum::Intersection result = Frustum::In;
	int i;

	for (i = 0; i < 6; i++) {

		Vector3 p = min;
		Vector3 n = max;
		Vector3 N = planes[i].getNormal();

		if (N.x() >= 0) {
			p[0] = max.x();
			n[0] = min.x();
		}
		if (N.y() >= 0) {
			p[1] = max.y();
			n[1] = min.y();
		}
		if (N.z() >= 0) {
			p[2] = max.z();
			n[2] = min.z();
		}

		if (planes[i].distance(p) < 0.0f) {
			return Out;
		} else if (planes[i].distance(n) < 0.0f) {
			result = Intersection::Intersect;
		}
	}

	return result;
}

Frustum::Intersection Frustum::intersectionAABB(const AABB &bounds) {
	return In;
	return intersectionAABB(bounds.min(), bounds.max());
}

Frustum::Intersection Frustum::intersectionOBB(const Vector3 &u, const Vector3 &v, const Vector3 &w) {}
Frustum::Intersection Frustum::intersectionOBB(const OBB &obb) {}

Frustum::Intersection Frustum::intersectionSphere(const Vector3 &pos, float radius) const { return Out; }

Frustum::Intersection Frustum::intersectionSphere(const BoundingSphere &sphere) const { return Out; }

Frustum::Intersection Frustum::intersectPlane(const Plane &plane) const { return In; }

Frustum::Intersection Frustum::intersectionFrustum(const Frustum &frustum) const { return In; }
