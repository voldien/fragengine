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
#ifndef _FV_RIGIDBODY_H_
#define _FV_RIGIDBODY_H_ 1
#include"../Def.h"


namespace fragcore {
	/**
	 *	Rigidbody.
	 */
	class FVDECLSPEC RigidBody {
		friend class DynamicInterface;
	private:
		inline RigidBody(void){}

		virtual ~RigidBody(void);

	public:	/*	Public methods.	*/

//
//		inline void useGravity(bool use) {
//
//		}
//
//		inline bool useGravity(void) {
//
//		}
//
//		/**
//		 *	Get mass of the object.
//		 */
//		inline float getMass(void) {
//			return this->getMass(this->getMappedObject());
//		}
//
//		/**
//		 *	Set mass of body.
//		 */
//		inline void setMass(float mass) {
//			this->setMass(this->getMappedObject(), mass);
//		}
//
//		/**
//		 *	Get position in world space.
//		 *	@Return
//		 */
//		inline PVVector3 getPosition(void) {
//			return this->getPosition(this->getMappedObject());
//		}
//
//		/**
//		 *	Set body position in world space.
//		 */
//		inline void setPosition(const PVVector3 &position) {
//			this->setPosition(this->getMappedObject(), position);
//		}
//
//		/**
//		 *	Get body oritention in world space.
//		 */
//		inline PVQuaternion getOrientation(void) {
//			return this->getOrientation(this->getMappedObject());
//		}
//
//		/**
//		 *
//		 */
//		inline void setOrientation(const PVQuaternion &quat) {
//			this->setOrientation(this->getMappedObject(), quat);
//		}
//
//		/**
//		 *
//		 */
//		inline PVVector3 getScale(void) {
//			return this->getScale(this->getMappedObject());
//		}
//
//		/**
//		 *
//		 */
//		inline void setScale(const PVVector3 &scale) {
//			this->setScale(this->getMappedObject(), scale);
//		}
//
//		/**
//		 *	Apply fource.
//		 */
//		inline void setForce(const PVVector3 &force) {
//			this->setForce(this->getMappedObject(), force);
//		}
//
//		/**
//		 *	Get linear drag.
//		 *	@Return
//		 */
//		inline float getDrag(void) {
//			return this->getDrag(this->getMappedObject());
//		}
//
//		inline void setDrag(float drag) {
//			this->setDrag(this->getMappedObject(), drag);
//		}
//
//		/**
//		 *	@Return
//		 */
//		inline float getAngularDrag(void) {
//			return this->getAngularDrag(this->getMappedObject());
//		}
//
//		inline void setAngularDrag(float angularDrag) {
//			this->setAngularDrag(this->getMappedObject(), angularDrag);
//		}
//
//
//		inline PVVector3 getVelocity(void) {
//			return this->getVelocity(this->getMappedObject());
//		}
//
//		/**
//		 *	TODO evoluate
//		 */
//		inline void attachNode(Node *node) {
//			this->node = node;
//		}
//
//		/**
//		 *	Get node assoicated with
//		 */
//		inline Node *getNode(void) const {
//			return this->node;
//		}

	protected:	/*	Protected virtual methods.	*/

		virtual float getMass(void* pobj);
		virtual void setMass(void* pobj, float mass);

		//virtual void setInertia(void* pobj);

		virtual PVVector3 getPosition(void* pobj);
		virtual void setPosition(void* pobj, const PVVector3& position);


		virtual PVQuaternion getOrientation(void* pobj);
		virtual void setOrientation(void* pobj, const PVQuaternion& quat);

		virtual PVVector3 getScale(void* pobj);
		virtual void setScale(void* pobj, const PVVector3& scale);

		virtual void setForce(void* pobj, const PVVector3& force);

		/**/
		virtual float getDrag(void* pobj);
		virtual void setDrag(void* pobj, float drag);

		virtual float getAngularDrag(void* pobj);
		virtual void setAngularDrag(void* pobj, float angularDrag);

		virtual PVVector3 getVelocity(void* pobj);

		//intptr_t getNativePtr(void) const override;

	protected:
		//Node* node;

	};

}


#endif
