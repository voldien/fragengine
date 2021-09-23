
#ifndef _FRAG_ENGINE_TRANSFORM_H_
#define _FRAG_ENGINE_TRANSFORM_H_ 1
#include<FragCore.h>


namespace fragengine {
	using namespace fragcore;

	/**
	 *
	 */
	class FVDECLSPEC Transform {
	public:
		Transform(void);
		//Transform (const Quaternion &q, const Vector3 &c=btVector3(btScalar(0), btScalar(0), btScalar(0)));
		//Transform (const btMatrix3x3 &b, const btVector3 &c=btVector3(btScalar(0), btScalar(0), btScalar(0)));
		Transform(const Transform &other);

		void rotate(const Vector3 &eular);

		void setPosition(const Vector3 &pos);

		void setLocalPosition(const Vector3 &pos);

		inline Vector3 getPosition(void) {
			return this->pos;
		}

		inline const Vector3 &getPosition(void) const {
			return this->pos;
		}

		inline Vector3 getLocalPosition(void) const {
			return Vector3();
		}

		void setScale(const Vector3 &scale);

		void setLocalScale(const Vector3 &scale);

		inline Vector3 getScale(void) const {
			return this->scale;
		}

		Vector3 getLocalScale(void) const {
			return Vector3();
		}

		void setRotation(const Quaternion &quat);

		void setLocalRotation(const Quaternion &quat);

		const Quaternion &getRotation(void) const;

		Quaternion getLocalRotation(void) const;

		Matrix4x4 getMatrix(void) const;

		Matrix4x4 getLocalMatrix(void) const;

		Matrix4x4 getViewMatrix(void) const;

		Matrix4x4 getViewLocalMatrix(void) const;

		float getMinimumScale(void) const;

		float getMaximumScale(void) const;

		void setMinimumScale(float min);

		void setMaximumScale(float max);

		PVMatrix3x3 &getBasis(void);

		const PVMatrix3x3 &getBasis(void) const;

		Transform &operator*=(const Transform &t);

		Transform operator*(const Transform &t) const;

		Vector3 operator()(const Vector3 &x) const;

		Vector3 operator*(const Vector3 &x) const;

		Quaternion operator*(const Quaternion &q) const;

		//Transform &operator=(const Transform &other);

	protected:  /*  Internal methods.   */

		void updateModelMatrix(void);

	private:    /*	Attributes.	*/

		Vector3 pos;              /*	Position in world space.	*/
		Vector3 scale;            /*	Scale.	*/
		Quaternion quat;          /*	Rotation in world space.	*/
		Matrix4x4 model;          /*  Precomputed model matrix.   */
		float maxScale;
		float minScale;
	};

}
#endif
