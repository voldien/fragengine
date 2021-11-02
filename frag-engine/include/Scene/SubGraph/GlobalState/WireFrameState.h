#ifndef FRAGVIEW_WIREFRAMESTATE_H_
#define FRAGVIEW_WIREFRAMESTATE_H_ 1

#include "GlobalState.h"

namespace fragengine
{
	/**
	 *
	 */
	class FVDECLSPEC WireFrameState : public GlobalState {
	public:
		WireFrameState() = default;
		virtual ~WireFrameState() = default;

		virtual int GetGlobalStateType() const { return WIREFRAME; }

		bool Enabled; // default: false
	};
} // namespace fragengine

#endif