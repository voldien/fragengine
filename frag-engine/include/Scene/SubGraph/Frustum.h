/**
	Simple physic simulation with a server-client model support.
	Copyright (C) 2016  Valdemar Lindberg

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _FV_FRUSTUM_H_
#define _FV_FRUSTUM_H_ 1
#include "Node.h"

namespace fragengine {
	using namespace fragcore;
	/*
	 *
	 */
	class FVDECLSPEC Frustum : public Node {
	  public:
		/**
		 *	Intersection.
		 */
		enum Intersection {
			Out = 0,	   /*	Outside frustum completly.*/
			In = 1,		   /*	Inside frustum completly.*/
			Intersect = 2, /*	Intresecting frustum planes.	*/
		};

		/**
		 *
		 */
		enum FrustumPlanes {
			TOPP = 0,	 /*	*/
			BOTTOMP = 1, /*	*/
			LEFTP = 2,	 /*	*/
			RIGHTP = 3,	 /*	*/
			NEARP = 4,	 /*	*/
			FARP = 5,	 /*	*/
		};

		/**
		 *	Get perspective matrix.
		 *	@Return current matrix of the frustum.
		 */
		const Matrix4x4 &getPerspectiveMatrix() const;

		void setFov(float fov);

		void setNear(float near);

		void setFar(float far);

		void setRatio(float ratio);

		float getFov() const;

		float getNear() const;

		float getFar() const;

		float getRatio() const;

		//    /**
		//     *	Get the n:th plane.
		//     *	@Return
		//     */
		//    PVPlane getPlane(int index) {
		//        return this->planes[index];
		//    }

		/**
		 *	Update camera matrix perspective.
		 */
		virtual void updatePerspective();

		/**
		 *	Comput the frustum planes.
		 */
		virtual void calcFrustumPlanes(const Vector3 &position, const Vector3 &look, const Vector3 &up,
									   const Vector3 &right);

		/**
		 *	Check if point is inside the frustum.
		 *	@Return eIn if inside frustum, eOut otherwise.
		 */
		virtual Intersection checkPoint(const Vector3 &pos) const;

		/**
		 * Check if AABB intersects frustum.
		 * @param min
		 * @param max
		 * @return eIntersect if intersect the frustum, eOut otherwise.
		 */
		virtual Intersection intersectionAABB(const Vector3 &min, const Vector3 &max);

		virtual Intersection intersectionAABB(const AABB &bounds);

		virtual Intersection intersectionOBB(const Vector3 &u, const Vector3 &v, const Vector3 &w);
		virtual Intersection intersectionOBB(const OBB &obb);

		/**
		 *	Check if sphere intersects frustum.
		 *	@Return
		 */
		virtual Intersection intersectionSphere(const Vector3 &pos, float radius) const;
		virtual Intersection intersectionSphere(const BoundingSphere &sphere) const;

		/**
		 *	Check if plane intersects frustum.
		 *	@Return
		 */
		virtual Intersection intersectPlane(const Plane &plane) const;

		/**
		 *	Check if frustum intersects frustum.
		 *	@Return
		 */
		virtual Intersection intersectionFrustum(const Frustum &frustum) const;

	  protected: /*	Makes the object only inheritable .	*/
		Frustum();
		Frustum(const Frustum &other);

	  private:								 /*	Attributes.	*/
		Matrix4x4 percmatrix;				 /*	*/
		Plane planes[6];					 /*	*/
		float fov, ratio, Znear, Zfar, tang; /*	*/
		float nw, nh, fh, fw;				 /*	*/
	};
} // namespace fragengine

#endif
