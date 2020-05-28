#ifndef _FV_CORE_NOTSUPPORTEDEXCEPTION_H_
#define _FV_CORE_NOTSUPPORTEDEXCEPTION_H_ 1
#include "IException.h"

namespace fragview {
	/**
	 *	Class responsible for showing
	 *	the method is not supported.
	 */
	class NotSupportedException : public IException {
	public:

		NotSupportedException(void) : IException("Functionality not supported") {}

		NotSupportedException(const std::string &arg) : IException(arg) {}

		const char *getName(void) const override {
			return typeid(this).name();
		}
	};
}

#endif
