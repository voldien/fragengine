
#ifndef FRAGVIEW_REFPTR_H_
#define FRAGVIEW_REFPTR_H_ 1

#include"../Def.h"
#include "SmartReference.h"

namespace fragview {

	template<class T>
	class RefPtr {
	public:

		FV_ALWAYS_INLINE T *operator->() {

			return ref;
		}

		FV_ALWAYS_INLINE T *operator*() {

			return ref;
		}

		FV_ALWAYS_INLINE const T *operator->() const {

			return ref;
		}

		FV_ALWAYS_INLINE const T *ptr() const {

			return ref;
		}

		FV_ALWAYS_INLINE T *ptr() {

			return ref;
		}

		FV_ALWAYS_INLINE const T *operator*() const {

			return ref;
		}
	public:

		FV_ALWAYS_INLINE RefPtr(void) {
			this->ref = NULL;
		}

		FV_ALWAYS_INLINE RefPtr(T *ref) {
			this->ref = ref;
		}

		FV_ALWAYS_INLINE ~RefPtr(void) {

		}

	private:
		T *ref;
		//AtomicRefCount count;
	};
}

#endif