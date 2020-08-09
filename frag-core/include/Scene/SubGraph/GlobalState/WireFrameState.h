#ifndef FRAGVIEW_WIREFRAMESTATE_H_
#define FRAGVIEW_WIREFRAMESTATE_H_ 1

#include "GlobalState.h"

namespace fragcore {
	/**
	 *
	 */
	class FVDECLSPEC WireFrameState : public GlobalState {
	public:
		WireFrameState(void) = default;
		virtual ~WireFrameState(void) = default;

		virtual int GetGlobalStateType() const { return WIREFRAME; }

		bool Enabled; // default: false
	};
}

#endif