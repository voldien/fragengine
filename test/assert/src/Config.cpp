#include<gtest/gtest.h>
#include"Renderer/RendererFactory.h"
#include"Core/IO/BufferIO.h"
#include"IConfigTest.h"

#define CONFIG_DEFAULT_NAME "Config"

using namespace fragcore;

void IConfigTest::TearDown() {
	Test::TearDown();
}

void IConfigTest::SetUp() {
	Test::SetUp();
	this->config = new IConfig();
	this->config->setName(CONFIG_DEFAULT_NAME);
	this->config->set<int>("a", 0);
	this->config->set<int>("b", 1);
	this->config->set<int>("c", 2);
}

//TODO move the config to fragview client.
/*
TEST (Config, ShortOptions) {
	const char *arg[] = {
			"fragview",
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
			"fragview",
			"--renderer-opengl",
			"--disable-notify-file",
			"--fragment=fractual.frag",
			"--poly=cube.obj",
			"-f", "wave.frag",
			"--inline-script=",
			"--no-decoration",
			"--save-config",
			"--screen-width=100",
			"--screen-height=200",
			"--screen-x=100",
			"--screen-y=200",
			"--anti-aliasing=2",
			"--srgb",
			"--alpha",
			"--v-sync",
			"--compression",
			"--save-config=tmp.xml",
			"--texture=tmp.png"

	};
	const int nArg = sizeof(arg) / sizeof(arg[0]);

	Config *config = Config::createConfig(nArg, arg, NULL);
	ASSERT_STREQ(config->get<const char *>("renderer-dynamicInterface"),
	             RenderingFactory::getInterfaceLibraryPath(RenderingFactory::eOpenGL));
	ASSERT_STREQ(config->get<const char *>("poly0"), "cube.obj");
	ASSERT_STREQ(config->get<const char *>("shader0"), "wave.frag");
	ASSERT_STREQ(config->get<const char *>("texture0"), "tmp.png");

	ASSERT_EQ(config->get<int>("screen_width"), 100);
	ASSERT_EQ(config->get<int>("screen-height"), 200);

	ASSERT_EQ(config->get<int>("screen-x"), 100);
	ASSERT_EQ(config->get<int>("screen-y"), 100);

	ASSERT_EQ(config->get<bool>("save-configuration"), true);
}

TEST(Config, SubConfig) {

}

*/

//
//TEST(Config, XMLLoadConfiguration) {
//	const char *arg[] = {
//		"fragview",
//	};
//	const int nArg = sizeof(arg) / sizeof(arg[0]);
//
//	Config *config = Config::createConfig(nArg, arg, "config.xml");
//}
//
//TEST(Config, XMLSaveConfiguration) {
//
//}
//
//TEST(Config, YAMLLoadConfiguration) {
//	const char *arg[] = {
//
//	};
//	const int nArg = sizeof(arg) / sizeof(arg[0]);
//
//	Config *config = Config::createConfig(nArg, arg, "config.yaml");
//}
//
//TEST(Config, YAMLSaveConfiguration) {
//
//}

TEST_F(IConfigTest, Copy) {
	IConfig config = *this->config;
	IConfig *pConfig = &config;

	//TODO
	/*  Assert true.    */
	for (int i = 0; i < config.getNumChildren() - 1; i++) {
		IConfig *subConfig = config.getChild(i);
	}

}

TEST_F(IConfigTest, Set) {
	const char *name = "The current name of the config object";
	IConfig *config = new IConfig();
	ASSERT_NO_THROW(config->setName(name));
	ASSERT_STREQ(config->getName().c_str(), name);

	ASSERT_NO_THROW(config->set("a", 0));
	ASSERT_NO_THROW(config->set("a", 1));
}

TEST_F(IConfigTest, Get) {
	ASSERT_STREQ(this->config->getName().c_str(), CONFIG_DEFAULT_NAME);
	ASSERT_EQ(this->config->get<int>("a"), 0);
	ASSERT_EQ(this->config->get<int>("b"), 1);
	ASSERT_EQ(this->config->get<int>("c"), 2);
}

TEST_F(IConfigTest, SubConfig) {
	/*  Copy.   */
	IConfig config = *this->config;
	IConfig *pConfig = &config;

	IConfig *subConfig;
	IConfig *subConfig2;
	ASSERT_NO_THROW(subConfig = &pConfig->getSubConfig("sub"));
	subConfig->setName("subconfig");
	ASSERT_NO_THROW(subConfig2 = &pConfig->getSubConfig("sub"));
	ASSERT_TRUE(*subConfig == *subConfig2);
}

TEST_F(IConfigTest, TypeCheck) {
	IConfig *config = new IConfig();

	config->get<int>("a1");
	config->get<float>("a1");
	config->get<double>("a1");
	config->get<bool>("a1");
	config->get<void *>("a1");
}

TEST_F(IConfigTest, Conditional) {

}
/*

TEST_F(IConfigTest, Formats){
		const char *arg[] = {
			"fragview",
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

	IConfig *config = Config::createConfig(nArg, arg, NULL);
	BufferIO bufferIo(65536);
	Ref<IO> buffer_ref = Ref<IO>(&bufferIo);
	config->save(buffer_ref, IConfig::ConfigFormat::JSON);
	config->parseConfigFile(buffer_ref, IConfig::ConfigFormat::JSON);

	config->save(buffer_ref, IConfig::ConfigFormat::YAML);
	config->parseConfigFile(buffer_ref, IConfig::ConfigFormat::YAML);

	config->save(buffer_ref, IConfig::ConfigFormat::XML);
	config->parseConfigFile(buffer_ref, IConfig::ConfigFormat::XML);

}*/
