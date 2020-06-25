#include"Scene/SubGraph/Frustum.h"

using namespace fragview;

Frustum::Frustum(void) {
//	this->setObjectType(Object::eFrustum);
	/*  Default frustum value.  */
	this->setFov(70.0f);
	this->Zfar = 1000.0f;
	this->Znear = 0.15f;
	this->ratio = 1.33333f;
//	updatePerspective();
}

Frustum::Frustum(const Frustum &other) {
	*this = other;
}

const PVMatrix4x4 &Frustum::getPerspectiveMatrix(void) const {
	return this->percmatrix;
}

void Frustum::setFov(float fov) {
	this->fov = HPM_DEG2RAD(fov);
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


float Frustum::getFov(void) const {
	return HPM_RAD2DEG(this->fov);
}

float Frustum::getNear(void) const {
	return this->Znear;
}

float Frustum::getFar(void) const {
	return this->Zfar;
}

float Frustum::getRatio(void) const {
	return this->ratio;
}

void Frustum::updatePerspective(void) {
	this->percmatrix = PVMatrix4x4::perspective(this->getFov(), this->getRatio(), this->getNear(), this->getFar());
	const Transform &transform = this->local;

	calcFrustumPlanes(transform.getPosition(), transform.getRotation().getVector(),
	                  transform.getRotation().getVector(PVVector3::up()),
	                  transform.getRotation().getVector(PVVector3::right()));
}

void Frustum::calcFrustumPlanes(const PVVector3 &position, const PVVector3 &look, const PVVector3 &up,
                                const PVVector3 &right) {
	PVVector3 dir, nc, fc, X, Y, Z;

	planes[eNEARP].setNormalAndPoint(-Z, nc);
	planes[eFARP].setNormalAndPoint(Z, fc);

	PVVector3 aux, normal;

	aux = (nc + Y * nh) - position;
	aux.normalize();
	normal = aux * X;
	planes[eTOP].setNormalAndPoint(normal, nc + Y * nh);

	aux = (nc - Y * nh) - position;
	aux.normalize();
	normal = X * aux;
	planes[eBOTTOM].setNormalAndPoint(normal, nc - Y * nh);

	aux = (nc - X * nw) - position;
	aux.normalize();
	normal = aux * Y;
	planes[eLEFT].setNormalAndPoint(normal, nc - X * nw);

	aux = (nc + X * nw) - position;
	aux.normalize();
	normal = Y * aux;
	planes[eRIGHT].setNormalAndPoint(normal, nc + X * nw);
}


Frustum::Intersection Frustum::checkPoint(const PVVector3 &pos) const {
	int x;

	/*	Iterate through each plane.	*/
	for (x = 0; x < 6; x++) {
		if (planes[x].distance(pos) < 0) {
			return eOut;
		}
	}

	return eIn;
}

Frustum::Intersection Frustum::intersectionAABB(const PVVector3 &min, const PVVector3 &max) {

	Frustum::Intersection result = Frustum::eIn;
	int i;

	for (i = 0; i < 6; i++) {

		PVVector3 p = min;
		PVVector3 n = max;
		PVVector3 N = planes[i].getNormal();

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
			return eOut;
		} else if (planes[i].distance(n) < 0.0f) {
			result = Intersection::eIntersect;
		}
	}

	return result;
}

Frustum::Intersection Frustum::intersectionAABB(const PVAABB &bounds) {
	return eIn;
	return intersectionAABB(bounds.min(), bounds.max());
}


Frustum::Intersection Frustum::intersectionSphere(const PVVector3 &pos, float radius) const {
	return eOut;
}

Frustum::Intersection Frustum::intersectionSphere(const PVBoundingSphere &sphere) const {
	return eOut;
}


Frustum::Intersection Frustum::intersectPlane(const PVPlane &plane) const {
	return eIn;
}

Frustum::Intersection Frustum::intersectionFrustum(const Frustum &frustum) const {
	return eIn;
}

