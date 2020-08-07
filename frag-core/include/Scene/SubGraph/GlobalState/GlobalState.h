#ifndef FRAGVIEW_GLOBALSTATE_H_
#define FRAGVIEW_GLOBALSTATE_H_ 1
#include <Core/Object.h>

namespace fragview {
	/**
	 *
	 */
	class FVDECLSPEC GlobalState : public Object {
	public:

		enum {
			ALPHA,      /*  */
			CULL,       /*  */
			DITHER,     /*  */
			FOG,        /*  */
			MATERIAL,   /*  */
			SHADE,      /*  */
			WIREFRAME,  /*  */
			ZBUFFER,    /*  */
			MAX_STATE   /*  */
		};

		virtual int getGlobalStateType(void) const = 0;

		static GlobalState *Default[MAX_STATE];
	protected:
		GlobalState(void) = default;
	};
}

#endif