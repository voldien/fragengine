#include<cstdio>
#include"Core/IO/FileSystem.h"
#include"Core/IO/BufferIO.h"
#include"Core/Ref.h"
#include"Exception/RuntimeExecption.h"
#include"Utils/ShaderUtil.h"
#include "Asset/AssetHandler.h"
#include "Asset/FileNotify.h"
#include "Utils/TextureUtil.h"
#include "Renderer/Texture.h"
#include "Renderer/ProgramPipeline.h"
using namespace fragcore;

void AssetHandler::handleAssetEvent(FileNotificationEvent *event) {

	assert(event && event->object);

	/*  Validate the event object.  */
	if (event == NULL || event->size <= 0 || event->data == NULL)
		throw std::invalid_argument("Bad file notification event.");

	switch (event->type) {
		case eTexture: {
			unsigned int width, height;
			unsigned long size;

			/*  Load new set of pixels. */
			void *texel = TextureUtil::loadTextureDataFromMem(event->data, event->size, &width, &height, NULL, NULL,
			                                                  NULL,
			                                                  &size);
			/*  TODO determine if to create new or not based on the size differences.   */
			Texture *texture = (Texture *) event->object;
			texture->setPixels(Texture::Format::eR8G8B8, 0, texel, size);
			free(texel);
		}
			break;
		case eShader: {
			/*  End of string added.   */
			event->data = realloc(event->data, event->size + 1);
			//TODO determine if text or binary.
			((char *) event->data)[event->size] = '\0';
			event->size++;

			/*  TODO determine which type.  */
			ProgramPipeline::ShaderType shaderType = ProgramPipeline::FRAGMENT_SHADER;

			/*  TODO determine what language.   */
			ShaderLanguage langauge = ShaderUtil::getFileLanguage(event->path);

			/*  Update new shader module.   */
			ProgramPipeline *pipeline = (ProgramPipeline *) event->object;
			Shader *old = pipeline->getShader(shaderType);
			Shader *shader;
			BufferIO bu(event->data, event->size);
			Ref<IO> buf = Ref<IO>(&bu);
			Ref<IRenderer> renderer = Ref<IRenderer>(pipeline->getRenderer());
			//ShaderUtil::loadShader(buf, eFrag, renderer, langauge, ShaderCodeType::eSourceCode, &shader);
			pipeline->setShader(shaderType, shader);

			/*  Delete old shader program.  */
			pipeline->getRenderer()->deleteShader(old);
		}
			break;
		case eGeometry: {


		}
			break;
		case eBuffer: {

		}
			break;
		case eStream: {

		}
			break;
		default:
			break;
	}
}

void AssetHandler::handleAssetDrop(const char *filepath) {
	if (FileSystem::getFileSystem()->isReadable(filepath))
		throw RuntimeException("");
}
