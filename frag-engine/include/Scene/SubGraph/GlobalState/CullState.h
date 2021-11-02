#ifndef FRAGVIEW_CULLSTATE_H
#define FRAGVIEW_CULLSTATE_H

#include "GlobalState.h"

namespace fragengine {

	class FVDECLSPEC CullState : public GlobalState {
	public:
		CullState() = default;
		virtual ~CullState() = default;

		virtual int GetGlobalStateType () const { return CULL; }

		enum // FrontType
		{
			FT_CCW, // front faces are counterclockwise ordered
			FT_CW,  // front faces are clockwise ordered
			FT_QUANTITY
		};
		enum // CullType
		{
			CT_FRONT, // cull front-facing triangles
			CT_BACK,    // cull back-facing triangles
			CT_QUANTITY
		};
		bool Enabled; // default: true
		int FrontFace; // default: FT_CCW
		int CullFace; // default: CT_BACK
	};
}

#endif