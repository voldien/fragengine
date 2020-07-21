#include <Exception/InvalidArgumentException.h>
#include"audio/AudioFactory.h"
#include"Core/Library.h"
#include"Core/Log.h"
using namespace fragview;

typedef AudioInterface *(*pcreateinternalaudio)(IConfig *config);


AudioInterface *AudioFactory::createAudioInterface(AudioAPI api, IConfig *config) {
	return AudioFactory::createAudioInterface(getInterfaceLibraryPath(api), config);
}

AudioInterface *AudioFactory::createAudioInterface(const char *cpathlib, IConfig *config) {
	Library library;
	AudioInterface *interface = NULL;
	const char *funcsymbol = "createInternalAudioInterface";
	pcreateinternalaudio pfunc;

	/*	Validate paramaters.	*/
	if (cpathlib == NULL || config == NULL)
		throw InvalidArgumentException("");

	assert(cpathlib);

	/*	Open library and validate.	*/
	library.open(cpathlib);
	if (library.isValid()) {

		/*	Get factory function for creating rendering dynamicInterface instance.	*/
		pfunc = (pcreateinternalaudio) library.getfunc(funcsymbol);
		interface = pfunc(config);

		/*	Assign resource object in order to work.	*/
		//interface->setResource(resources);
	} else {
		Log::error("Failed loading %s library for creating rendering dynamicInterface.\n", cpathlib);
	}

	return interface;
}

const char *AudioFactory::getInterfaceLibraryPath(AudioAPI api) {
#ifdef FV_UNIX
	switch (api) {
		case AudioFactory::OpenAL:
			return "libfragview-aal.so";
		case AudioFactory::FMOD:
			return "libfragview-afm.so";
		default:
			assert(0);

			return "";
	}
#else
	assert(0);
#endif
}
