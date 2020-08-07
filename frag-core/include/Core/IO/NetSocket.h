
#ifndef FRAGVIEW_NETSOCKET_H_
#define FRAGVIEW_NETSOCKET_H_ 1
#include "../SmartReference.h"
#include "IP.h"

namespace fragview {
	/**
	 *
	 */
	class FVDECLSPEC NetSocket : public SmartReference {
	public:
		NetSocket(void);
		~NetSocket(void);
		enum Type {
			UDP,
			TCP,
		};

		/*virtual int bind(IP adddrr, Type _type);
		virtual int connect(void);
		virtual int listen(void);

		virtual int close(void);
		virtual int read(void);
		virtual int write(void);
*/
	};
}

#endif