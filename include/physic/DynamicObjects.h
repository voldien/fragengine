
#ifndef _PV_DYNAMIC_OBJECT_H_
#define _PV_DYNAMIC_OBJECT_H_ 1
#include <physic/RigidBody.h>


/*  TODO rename.    */
/**
 * Contains all dynamic object references.
 */
class PVDECLSPEC DynamicObjects {
	friend class PhysicInterface;

public:
	DynamicObjects(void) {
		this->attachment = NULL;
	}

	/**
	 * Check if dynamic object is attached.
	 * @return
	 */
	bool isAttached(void) const {
		return attachment != NULL;
	}

	/*  */
	RigidBody *attachment;
};

#endif