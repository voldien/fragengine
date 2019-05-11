#include<gtest/gtest.h>
#include <FragView.h>
#include <RendererFactory.h>
#include<Utils/TextureUtil.h>
#include<Renderer/Sampler.h>
#include <common.h>

static void deleteRenderer(IRenderer *renderer) {
	EXPECT_NO_THROW(delete renderer);
}

TEST(OpenGL, CreateInterface) {
	Config *config = Config::createConfig(0, NULL, NULL);
	IRenderer *renderer;

	EXPECT_ANY_THROW(renderer = RenderingFactory::createRendering(0, config));
	EXPECT_ANY_THROW(renderer = RenderingFactory::createRendering("", config));
	EXPECT_NO_THROW(renderer = RenderingFactory::createRendering(RenderingFactory::eOpenGL, config));
}

TEST(OpenGL, Buffer) {
	const int size = 4096;
	Buffer *buffer;

	IRenderer *renderer = createRendererInterface(RenderingFactory::eOpenGL);
	const std::vector<BufferDesc::BufferHint> hints1 = {
			BufferDesc::eRead, BufferDesc::eWrite,
			(BufferDesc::BufferHint)(BufferDesc::eRead | BufferDesc::eWrite),
	};
	const std::vector<BufferDesc::BufferHint> hints2 = {
			BufferDesc::eStatic, BufferDesc::eDynamic, BufferDesc::eStream
	};
	const std::vector<BufferDesc::BufferType> targets = {
			BufferDesc::eArray,
			BufferDesc::eElementArray,
			BufferDesc::eUniform,
			BufferDesc::eTexture,
			BufferDesc::eShaderStorage,
			BufferDesc::eTransformFeedback,
			BufferDesc::ePixelUnpack,
			BufferDesc::ePixelPack
	};

	/*	Test all possible combinations of buffers.	*/
	for (int t = 0; t < hints1.size(); t++) {
		for (int h = 0; h < hints2.size(); h++) {
			for (int tar = 0; tar < targets.size(); tar++) {
				BufferDesc::BufferType target = targets[tar];
				BufferDesc::BufferHint hint = (BufferDesc::BufferHint)(hints1[t] | hints2[h]);

				/**/
				BufferDesc desc;
				desc.size = size;
				desc.type = target;
				desc.hint = hint;
				desc.data = NULL;

				/**/
				EXPECT_NO_THROW(buffer = renderer->createBuffer(&desc));
				ASSERT_EQ(buffer->getRenderer(), renderer);
				ASSERT_EQ(buffer->getSize(), size);
				ASSERT_NE(buffer->mapBuffer(Buffer::eRead), NULL);

				/**/
				EXPECT_NO_THROW(renderer->deleteBuffer(buffer));
			}
		}
	}

	/*	Handling of big sizes.	*/
	Capability capability;
	renderer->getCapability(&capability);
	const std::vector<int> maxSizes= {
		capability.sMaxUniformBlockSize,
		capability.sMaxTextureBufferSize,
	};

	/*	Test all possible combinations of buffers.	*/
	for (int t = 0; t < hints1.size(); t++) {
		for (int h = 0; h < hints2.size(); h++) {
			for (int tar = 0; tar < targets.size(); tar++) {
				BufferDesc::BufferType target = targets[tar];
				BufferDesc::BufferHint hint = (BufferDesc::BufferHint)(hints1[t] | hints2[h]);

				/*	*/
				BufferDesc desc;
				desc.size = size;
				desc.type = target;
				desc.hint = hint;
				desc.data = NULL;

				/**/
				EXPECT_NO_THROW(buffer = renderer->createBuffer(&desc));
				ASSERT_EQ(buffer->getRenderer(), renderer);
				ASSERT_EQ(buffer->getSize(), size);
				ASSERT_NE(buffer->mapBuffer(Buffer::eRead), NULL);

				/**/
				EXPECT_NO_THROW(renderer->deleteBuffer(buffer));
			}
		}
	}

	deleteRenderer(renderer);
}

TEST(OpenGL, Texture) {
	unsigned int width, height;
	void *pixels;
	unsigned long size;
	Texture *texture;
	IRenderer *renderer = createRendererInterface(RenderingFactory::eOpenGL);

	/*	Load the pixel data used for testing all the combination with the texture create function.	*/
	EXPECT_NO_THROW(pixels = TextureUtil::loadTextureData("../../fragview.png", &width, &height, &size));

	const std::vector<TextureDesc::Compression> compressions = {
			TextureDesc::eNonCompression,
			TextureDesc::eCompression,
			TextureDesc::eRGTC,
			TextureDesc::eDXT1,
			TextureDesc::eDXT4,
			TextureDesc::eS3TC

	};
	const std::vector<bool> mimaps = {false, true};
	const float ansio = 4.0f;
	for (int m = 0; m < mimaps.size(); m++) {
		bool mipmap = mimaps[m];
		for (int c = 0; c < compressions.size(); c++) {
			TextureDesc::Compression compression = compressions[c];

			TextureDesc desc;
			desc.target = TextureDesc::eTexture2D;
			desc.width = width;
			desc.height = height;
			desc.type = TextureDesc::eUnsignedByte;
			desc.usemipmaps = mipmap;
			desc.pixel = pixels;
			desc.pixelSize = size;
			desc.numlevel = 5;
			desc.compression = compression;
			desc.sampler.AddressU = SamplerDesc::eRepeat;
			desc.sampler.AddressV = SamplerDesc::eRepeat;
			desc.sampler.AddressW = (SamplerDesc::AddressMode) 0;
			desc.sampler.anisotropy = ansio;
			EXPECT_NO_THROW(texture = renderer->createTexture(&desc));
			ASSERT_NE(texture, NULL);
			ASSERT_EQ(texture->width(), width);
			ASSERT_EQ(texture->height(), height);
			ASSERT_FLOAT_EQ(texture->getAnisotropic(), ansio);
			ASSERT_EQ(texture->getRenderer(), renderer);
			/*	TODO.	*/
			//texture->getWrapMode();
			//texture->getFilterMode();
			//texture->getFormat();

			renderer->deleteTexture(texture);
		}
	}
	deleteRenderer(renderer);
}

TEST(OpenGL, Shader){

}

TEST(OpenGL, Geometry){

}

TEST(OpenGL, Sampler){
	IRenderer *renderer = createRendererInterface(RenderingFactory::eOpenGL);

	const std::vector<SamplerDesc::AddressMode> addresses = {
			SamplerDesc::eRepeat,
			SamplerDesc::eRepeatMirror,
			SamplerDesc::eClamp,
			SamplerDesc::eClampBorder

	};

	const std::vector<SamplerDesc::FilterMode> filterModes = {
			SamplerDesc::eLinear,
			SamplerDesc::eNearset
	};

	for(int f = 0; f < filterModes.size(); f++){
		SamplerDesc::FilterMode filter;
		for (int a = 0; a < addresses.size(); a++) {
			SamplerDesc::AddressMode addressMode = addresses[a];
			Sampler *sampler;

			SamplerDesc desc;
			desc.anisotropy = 4.0f;
			desc.minLOD = 0;
			desc.minFilter = filter;
			desc.magFilter = filter;
			desc.AddressU = addressMode;    
			desc.AddressV = addressMode;
			desc.AddressW = addressMode;
			desc.maxLOD = 5;
			desc.compareFunc = SamplerDesc::eNoCompare;
			desc.mipmapFilter = filter;
			desc.biasLOD = 2;
			desc.borderColor[0] = 0.0f;
			desc.borderColor[1] = 0.0f;
			desc.borderColor[2] = 0.0f;
			desc.borderColor[3] = 0.0f;

			EXPECT_NO_THROW(sampler = renderer->createSampler(&desc));
			/*  */
			ASSERT_EQ(sampler->getRenderer(), renderer);
			ASSERT_FLOAT_EQ(sampler->getAnisotropic(), desc.anisotropy);
			ASSERT_NE(sampler, NULL);

			/*  */
			Sampler::WrapMode wrapMode = sampler->getWrapMode();
			Sampler::FilterMode  filterMode = sampler->getFilterMode();

			renderer->deleteSampler(sampler);
		}
	}

	/*  Test bad description.   */

	deleteRenderer(renderer);
}

//TEST (OpenGL, FragmentShader) {
//	const char* arg[] = {
//			"--debug",
//			"-f", "./samples/glsl/wave.frag"
//
//	};
//	const int nArg = sizeof(arg) / sizeof(arg[0]);
//
//	try {
//		FragView(nArg, arg).run();
//	} catch (std::exception &ex) {
//		std::cerr << ex.what() << std::endl;
//
//	}
//}
//
//TEST (OpenGL, ComputeShader) {
//	const char* arg[] = {
//			"--debug",
//			"-H", "./samples/glsl/compute.comp"
//	};
//	const int nArg = sizeof(arg) / sizeof(arg[0]);
//
//	try {
//		FragView(nArg, arg).run();
//	} catch (std::exception &ex) {
//		std::cerr << ex.what() << std::endl;
//
//	}
//}