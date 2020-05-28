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

extern fragview::IRenderer *createOpenGLRenderer(void);
extern fragview::IRenderer *createRendererInterface(fragview::RenderingFactory::RenderingAPI api, fragview::IConfig* config);
extern void deleteRenderer(fragview::IRenderer *renderer);

#endif