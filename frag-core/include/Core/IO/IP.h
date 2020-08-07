
#ifndef _FRAGVIEW_IP_H_
#define _FRAGVIEW_IP_H_ 1
#include"../Object.h"

namespace fragview {
	class FVDECLSPEC IP : public Object {
	public:
		IP(void);
		enum Type {

			TYPE_NONE = 0,
			TYPE_IPV4 = 1,
			TYPE_IPV6 = 2,
			TYPE_ANY = 3,
		};

	protected:
//		virtual IP_Address _resolve_hostname(const String &p_hostname, Type p_type = TYPE_ANY) = 0;
//		Array _get_local_addresses() const;
//		Array _get_local_interfaces() const;
	public:


	};
}

#endif