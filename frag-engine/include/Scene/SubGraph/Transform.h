
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

		//Transform (const PVQuaternion &q, const PVVector3 &c=btVector3(btScalar(0), btScalar(0), btScalar(0)));
		//Transform (const btMatrix3x3 &b, const btVector3 &c=btVector3(btScalar(0), btScalar(0), btScalar(0)));
		Transform(const Transform &other);

		void rotate(const PVVector3 &eular);

		void setPosition(const PVVector3 &pos);

		void setLocalPosition(const PVVector3 &pos);

		inline PVVector3 getPosition(void) {
			return this->pos;
		}

		inline const PVVector3 &getPosition(void) const {
			return this->pos;
		}

		inline PVVector3 getLocalPosition(void) const {
			return PVVector3();
		}

		void setScale(const PVVector3 &scale);

		void setLocalScale(const PVVector3 &scale);

		inline PVVector3 getScale(void) const {
			return this->scale;
		}

		PVVector3 getLocalScale(void) const {
			return PVVector3();
		}

		void setRotation(const PVQuaternion &quat);

		void setLocalRotation(const PVQuaternion &quat);

		const PVQuaternion &getRotation(void) const;

		PVQuaternion getLocalRotation(void) const;

		PVMatrix4x4 getMatrix(void) const;

		PVMatrix4x4 getLocalMatrix(void) const;

		PVMatrix4x4 getViewMatrix(void) const;

		PVMatrix4x4 getViewLocalMatrix(void) const;

		float getMinimumScale(void) const;

		float getMaximumScale(void) const;

		void setMinimumScale(float min);

		void setMaximumScale(float max);

		PVMatrix3x3 &getBasis(void);

		const PVMatrix3x3 &getBasis(void) const;

		Transform &operator*=(const Transform &t);

		Transform operator*(const Transform &t) const;

		PVVector3 operator()(const PVVector3 &x) const;

		PVVector3 operator*(const PVVector3 &x) const;

		PVQuaternion operator*(const PVQuaternion &q) const;

		//Transform &operator=(const Transform &other);

	protected:  /*  Internal methods.   */

		void updateModelMatrix(void);

	private:    /*	Attributes.	*/

		PVVector3 pos;              /*	Position in world space.	*/
		PVVector3 scale;            /*	Scale.	*/
		PVQuaternion quat;          /*	Rotation in world space.	*/
		PVMatrix4x4 model;          /*  Precomputed model matrix.   */
		float maxScale;
		float minScale;
	};

}
#endif
