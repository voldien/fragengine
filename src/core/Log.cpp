#include <cstdarg>
#include <cstdio>
#include"Core/Log.h"

static Log::VERBOSITY g_verbosity = Log::eQuite;

void Log::setVerbosity(VERBOSITY verbosity) {
	g_verbosity = verbosity;
}

Log::VERBOSITY Log::getVerbosity(void) {
	return g_verbosity;
}


int Log::log(VERBOSITY verbosity, const char *format, ...) {
	int l = 0;
	va_list vl;

	va_start(vl, format);
	l = logv(verbosity, format, vl);
	va_end(vl);

	return l;
}

int Log::log(const char *format, ...) {
	int l = 0;
	va_list vl;

	va_start(vl, format);
	l = Log::logv(eVerbose, format, vl);
	va_end(vl);

	return l;
}

int Log::error(const char *format, ...) {
	int l = 0;
	va_list argptr;

	va_start(argptr, format);
	/*	output to stdout	*/
	l = Log::logv(eError, format, argptr);
	va_end(argptr);

	return l;
}

int Log::logv(VERBOSITY verbosity, const char *format, va_list va) {
	if (verbosity <= getVerbosity()) {
		return vprintf(format, va);
	}
	return 0;
}
