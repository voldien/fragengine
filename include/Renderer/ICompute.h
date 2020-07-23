#ifndef _FV_ICOMPUTE_H_
#define _FV_ICOMPUTE_H_ 1
#include "../Def.h"
#include "../Core/SmartReference.h"
#include "../Prerequisites.h"

namespace fragview {
	class FVDECLSPEC ICompute : public SmartReference {
	public:

		/*	*/
		virtual bool supportCompute(void);
		
		/**
		 * Dispatch compute program.
		 * @param global global workgroup.
		 * @param local local workgroup
		 * @param offset offset in indirect buffer in number of bytes.
		 */
		virtual void dispatchCompute(unsigned int *global, unsigned int *local, unsigned int offset = 0);

		//TODO add memory barrier.
		virtual void memoryBarrier(void);

		// virtual Sync *createSync(SyncDesc *desc);

		// virtual void deleteSync(Sync *sync);

		// virtual const char *getVersion(void) const;
	};
}
#endif