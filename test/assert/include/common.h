#ifndef _FRAGVIEW_ASSERT_COMMON_H_
#define _FRAGVIEW_ASSERT_COMMON_H_ 1

#include <Renderer/IRenderer.h>
#include <Renderer/RendererFactory.h>
#include<cstddef>

class CommonBaseTest : public testing::Test {
public:
protected:
	void SetUp() override;

	void TearDown() override;
};

extern fragcore::IRenderer *createOpenGLRenderer(void);
extern fragcore::IRenderer *createRendererInterface(fragcore::RenderingFactory::RenderingAPI api, fragcore::IConfig* config);
extern void deleteRenderer(fragcore::IRenderer *renderer);

#endif