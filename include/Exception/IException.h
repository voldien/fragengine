#ifndef _FRAGVIEW_IEXCEPTION_H_
#define _FRAGVIEW_IEXCEPTION_H_ 1
#include<stdexcept>
#include"../Def.h"

namespace fragview {

	//TODO add declspec
	class FVDECLSPEC IException : public std::exception {
	public:
		IException(void);

		IException(const char *what);

		IException(const std::string &what);

		const std::string &getBackTrace(void) const;

		const char *what(void) const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT;

		virtual const char *getName(void) const = 0;

	protected:
		void generateStackTrace(void);

	private:
		std::string stackTrace;
		std::string mwhat;
	};
}

#endif