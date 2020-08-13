#ifndef FRAGVIEW_ZBUFFERSTATE_H_
#define FRAGVIEW_ZBUFFERSTATE_H_ 1
#include "GlobalState.h"

namespace fragcore {

	/**
	 *
	 */
	class FVDECLSPEC ZBufferState : public GlobalState {
	public:
		int getGlobalStateType(void) const override {
			return ZBUFFER;
		}

	private:
		bool Enabled;
		bool Writable;
		int Compare;
	};
}

#endif