#ifndef FRAGVIEW_FILEACCESS_H_
#define FRAGVIEW_FILEACCESS_H_ 1
#include"../SmartReference.h"

namespace fragview {
	
	/**
	 *
	 */
	class FVDECLSPEC FileAccess : public SmartReference {
	public:
		FileAccess(void);
		~FileAccess(void);

//		virtual uint32_t _get_unix_permissions(void) = 0;
//		virtual void _set_unix_permissions(uint32_t p_permissions) = 0;
	};
}

#endif