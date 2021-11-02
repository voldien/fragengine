#ifndef FRAGVIEW_GLOBALSTATE_H_
#define FRAGVIEW_GLOBALSTATE_H_ 1
#include <Core/Object.h>

namespace fragengine {
	/**
	 *
	 */
	class FVDECLSPEC GlobalState : public fragcore::Object {
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

		virtual int getGlobalStateType() const = 0;

		static GlobalState *Default[MAX_STATE];
	protected:
		GlobalState() = default;
	};
} // namespace fragengine

#endif