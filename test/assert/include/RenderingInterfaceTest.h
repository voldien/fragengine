#ifndef FRAGVIEW_TEST_RENDERINGINTERFACETEST_H_
#define FRAGVIEW_TEST_RENDERINGINTERFACETEST_H_ 1
#include "common.h"
using namespace fragcore;

#define SETRENDERAPISCOPE(obj, renderingApi)   \
    {                                               \
    switch (renderingApi) {                        \
        case RenderingFactory::eOpenGL:{            \
            SCOPED_TRACE(obj->apiNames[0]);         \
        }break;                                     \
        case RenderingFactory::eVulkan:{\
            SCOPED_TRACE(obj->apiNames[1]);\
        }break;\
        case RenderingFactory::eOpenCL:{\
            SCOPED_TRACE(obj->apiNames[2]);\
        }break;\
        case RenderingFactory::eDirectX:{\
            SCOPED_TRACE(obj->apiNames[3]);\
        }break;\
        default:\
            GTEST_FAIL();\
    }\
}\
\

class RenderingInterfaceTest : public CommonBaseTest {
protected:
	void TearDown() override;

	void SetUp() override;

	std::vector<RenderingFactory::RenderingAPI> apis;
	std::vector<const char *> apiNames;
	Capability capability;
	IConfig* config;
};

#endif
