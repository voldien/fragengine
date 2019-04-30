#include<gtest/gtest.h>
#include <Core/Config.h>
#include <RendererFactory.h>


TEST (Config, ShortOptions) {
	const char *arg[] = {
			"-N",
			"-t", "brick1.png",
			"-t", "brick2.png",
			"-t", "brick3.png",
			"-t", "brick4.png",
			"-d",
			"-w",
			"-S",
			"-a",
			"-c",
			"-R", "2.0",
			"-p", "cube.obj",
			"-U",
			"-F", "w",
			"-G", "w",
			"-C", "w",
			"-H", "w",
			"-E", "w",

	};
	const int nArg = sizeof(arg) / sizeof(arg[0]);

	Config *config = Config::createConfig(nArg, arg, NULL);

	ASSERT_EQ(config->get<bool>("notify-file"), false);
	const std::vector<std::string> &textures = config->get<const std::vector<std::string>>("textures");
	ASSERT_STREQ(config->get<const char *>("texture0"), "brick1.png");
	ASSERT_STREQ(config->get<const char *>("texture1"), "brick2.png");
	ASSERT_STREQ(config->get<const char *>("texture2"), "brick3.png");
	ASSERT_STREQ(config->get<const char *>("texture3"), "brick4.png");
	ASSERT_STREQ(config->get<const char *>("texture4"), "brick5.png");
	ASSERT_EQ(config->get<bool>("save-configuration"), true);
}

TEST (Config, ConfigLongOptions) {
	const char *arg[] = {
			"--renderer-opengl",
			"--disable-notify-file",
			"--fragment=fractual.frag",
			"--poly=cube.obj",
			"-f", "wave.frag",
			"--inline-script=",
			"--no-decoration",
			"--save-config",
			"--screen-width=100",
			"--screen-height=100",
			"--screen-x=100",
			"--screen-y=100",
			"--anti-aliasing=2",
			"--srgb",
			"--alpha",
			"--v-sync",
			"--compression",
			"--save-config=tmp.xml",
			"--texture=tmp.png"

	};
	const int nArg = sizeof(arg) / sizeof(arg[0]);

	Config* config = Config::createConfig(nArg, arg, NULL);
	ASSERT_STREQ( config->get<const char*>("renderer-dynamicInterface"), RenderingFactory::getInterfaceLibraryPath(RenderingFactory::eOpenGL));
	//ASSERT_STREQ( config->get<const char*>("shader0"), "");
	//ASSERT_STREQ( config->get<const char*>("poly0"), "cube.obj");
	ASSERT_STREQ( config->get<const char*>("shader0"), "wave.frag");

	ASSERT_EQ( config->get<bool>("save-configuration"), true);
}