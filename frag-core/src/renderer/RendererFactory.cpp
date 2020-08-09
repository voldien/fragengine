
#include <Renderer/RendererFactory.h>
#include <cassert>
#include <Core/Library.h>
#include <exception>
#include <cstdio>
#include <stdexcept>
#include <Utils/StringUtil.h>
#include <Core/IConfig.h>
#include <Exception/InvalidArgumentException.h>
#include <Exception/RuntimeExecption.h>

using namespace fragcore;
typedef IRenderer *(*pcreateinternalrendering)(IConfig *config);

IRenderer *RenderingFactory::createRendering(RenderingFactory::RenderingAPI renderingapi, IConfig *config) {
	return RenderingFactory::createRendering(getInterfaceLibraryPath(renderingapi), config);
}

IRenderer *RenderingFactory::createRendering(const char *cpathlib, IConfig *config) {
	Library library;
	IRenderer *interface = NULL;
	const char *funcsymbol = "createInternalRenderer";
	pcreateinternalrendering pfunc;

	/*	Validate parameters.	*/
	if (cpathlib == NULL)
		throw InvalidArgumentException("path variable must not be null.");

	/*	Open library and validate.	*/
	library.open(cpathlib);
	if (library.isValid()) {

		/*	Get factory function for creating rendering instance.	*/
		pfunc = (pcreateinternalrendering) library.getfunc(funcsymbol);
		interface = pfunc(config);

	} else {
		throw RuntimeException(fvformatf("Failed loading %s library for creating renderer.", cpathlib));
	}

	return interface;
}

const char *RenderingFactory::getInterfaceLibraryPath(RenderingFactory::RenderingAPI api) {
#ifdef FV_UNIX
	switch (api) {
		case RenderingFactory::eOpenGL:
			return "libfragview-rgl.so";
		case RenderingFactory::eVulkan:
			return "libfragview-rvk.so";
		case RenderingAPI::eDirectX:
			throw InvalidArgumentException("Not supported on Unix Systems.");
		case RenderingAPI::eOpenCL:
			return "libfragview-rcl.so";
		default:
			assert(0);
			throw InvalidArgumentException("Not a valid rendering API enumerator.");
	}
#elif defined(FV_WINDOWS)
	switch (api) {
		case RenderingFactory::eOpenGL:
			return "libfragview-rgl.dll";
		case RenderingFactory::eVulkan:
			return "libfragview-rvk.dll";
		case RenderingAPI::eDirectX:
			return "libfragview-rdx.dll";
		case RenderingAPI::eOpenCL:
			return "libfragview-rcl.dll";
		default:
			assert(0);
			throw InvalidArgumentException("Not a valid rendering API enumerator.");
	}
#endif
}

RenderingFactory::RenderingFactory(void) {

}
