#ifndef _FRAG_CORE_RUNETIMEEXECPTION_H_
#define _FRAG_CORE_RUNETIMEEXECPTION_H_ 1
#include <stdexcept>
#include "IException.h"

namespace fragcore {
/**
 *
 */
	class RuntimeException : public IException {
	public:
		RuntimeException(void) : IException("Not implemented yet!") {}

		RuntimeException(const std::string &arg) : IException(arg) {}

		const char *getName(void) const override {
			return typeid(this).name();
		}
	};
}

#endif