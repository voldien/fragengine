
#ifndef _FRAG_CORE_GEOMETRYUTIL_H_
#define _FRAG_CORE_GEOMETRYUTIL_H_ 1
#include"../Def.h"

namespace fragcore{

	/**
	 * 
	 */
	//TODO name class to match the file name.
	class FVDECLSPEC GeometryUtility {
	public:
	
		static bool TestPlanesAABB(const PVPlane &plane, const PVAABB &bound);
		
	};
}
#endif