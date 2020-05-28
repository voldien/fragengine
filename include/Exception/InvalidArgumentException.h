#ifndef FRAGVIEW_INVALIDARGUMENTEXCEPTION_H_
#define FRAGVIEW_INVALIDARGUMENTEXCEPTION_H_ 1
#include "IException.h"

namespace fragview {
	/**
	 *
	 */
	class InvalidArgumentException : public IException {
	public:
		InvalidArgumentException(void) : IException("Invalid argument exception"){}
		InvalidArgumentException(const std::string &arg) : IException(arg) {}

		const char *getName(void) const override {
			return typeid(this).name();
		}
	};
}

#endif