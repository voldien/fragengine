
#ifndef _FRAGVIEW_INTERNAL_OBJECT_TYPE_H_
#define _FRAGVIEW_INTERNAL_OBJECT_TYPE_H_ 1
#include"Renderer/RenderDesc.h"
#include"Renderer/Buffer.h"
#include"Renderer/IRenderer.h"
#include<SDL2/SDL.h>
#include <Renderer/RendererWindow.h>

namespace fragview {

	/**
	 *
	 */
	typedef struct OpenGLCore_t {
		void *openglcontext;
		SDL_Window *tpmwindow;
		fragview::RendererWindow *drawwindow;

		bool useCoreProfile;
		bool useCompatibility;

		/*  */
		//TODO determine if to use pool or something .
		Buffer *pboUnPack;
		Buffer *pboPack;

		/*  Cached internal capabilities.   */
		Capability capability;
		TextureDesc::Compression compression;

		/*  Context version.    */
		int majorVersion;
		int minorVersion;
		int profile;
		int cflag;

		bool debug;
		bool alpha;

		ViewPort *defaultViewport;
		std::vector<ViewPort *> viewports;   //TODO remove pointer.
		FrameBuffer *defaultFrameBuffer;
		/*  Texture gamma corrections.  */
		bool gamma;
		ShaderLanguage supportedLanguages;
	} OpenGLCore;

	typedef struct opengl_viewport_t {
		unsigned int viewport;
	} GLViewPort;

	/**
	 *
	 */
	typedef struct opengl_texture_object_t {
		TextureDesc desc;
		unsigned int target;
		unsigned int texture;
		unsigned int pbo;   /*  TODO resolve if to relocate.    */
		Sampler *sampler;
	} GLTextureObject;

	typedef struct opengl_sampler_object_t {
		unsigned int sampler;
	} GLSamplerObject;

	/**
	 *
	 */
	typedef struct opengl_buffer_object_t {
		BufferDesc desc;
		unsigned int target;
		unsigned int buffer;
		unsigned int base;
	} GLBufferObject;

	typedef struct opengl_program_pipeline_t {
		unsigned int program;

		Shader *v, *f, *g, *tc, *te, *c;
	} GLProgramPipeline;

	/**
	 *
	 */
	typedef struct opengl_shader_object_t {
		unsigned int program;
		unsigned int shader;
	} GLShaderObject;

	/**
	 *
	 */
	typedef struct opengl_geometry_object_t {
		GeometryDesc desc;
		unsigned int mode;
		unsigned int vao;
		unsigned int indicesType;
		Buffer *indicesbuffer;
		Buffer *vertexbuffer;
	} GLGeometryObject;

	/**
	 *
	 */
	typedef struct opengl_framebuffer_t {
		FrameBufferDesc desc;
		Texture *textures;
		unsigned int numtextures;
		unsigned int framebuffer;

	} GLFrameBufferObject;

	typedef struct opengl_query_t {
		unsigned int query[8];
	} GLQuery;

	typedef struct opengl_sync_t {
		void *sync;
	} GLSync;

}

//TODO change name to resolve potential symbol name conflict.
/**
 * Helper functions.
 */
extern void addMarkerLabel(const fragview::OpenGLCore *glcore, unsigned int identifier,
		unsigned int object, const fragview::MarkerDebug *debug);

extern void resetErrorFlag(void);
extern unsigned int getWrapMode(fragview::SamplerDesc::AddressMode mode);

extern unsigned int getFilterMode(fragview::SamplerDesc::FilterMode mode, fragview::SamplerDesc::FilterMode mips);

extern unsigned int getCompareMode(fragview::SamplerDesc::CompareFunc mode);

extern unsigned int getGraphicFormat(fragview::GraphicFormat graphicFormat);
extern unsigned int getTextureFormat(fragview::TextureFormat textureFormat, unsigned int* pixelType);

extern unsigned int getTextureFormat(fragview::TextureDesc::Format format);
extern unsigned int getInternalTextureFormat(fragview::TextureDesc::Format format, bool sRGB,
                                             fragview::TextureDesc::Compression compression, fragview::TextureDesc::Type type);

extern unsigned int getTextureTarget(fragview::TextureDesc::Target target, int nrSamples);

extern unsigned int getTextureType(fragview::TextureDesc::Type type);

extern unsigned int getTextureSwizzle(fragview::TextureDesc::Swizzle swizzle);

extern unsigned int getBufferType(fragview::BufferDesc::BufferType type);

extern unsigned int getBufferHint(fragview::BufferDesc::BufferHint hint);

extern unsigned int getPrimitive(fragview::GeometryDesc::Primitive primitive);

extern unsigned int getAttributeDataType(fragview::GeometryDesc::AttributeType type);

extern unsigned int getState(fragview::IRenderer::State state);

extern unsigned int getTextureFilterModeNoMip(fragview::Texture::FilterMode format);

// FrameBuffer
extern unsigned int getBlendEqu(fragview::FrameBuffer::BlendEqu equ);

extern unsigned int getBlendFunc(fragview::FrameBuffer::BlendFunc func);

extern unsigned int getClearBitMask(fragview::CLEARBITMASK clearbitmask);

// Texture.
extern unsigned int getTextureWrapMode(fragview::Texture::WrapMode mode);

extern unsigned int getTextureFilterMode(fragview::Texture::FilterMode mode);

extern unsigned int getTextureCompareMode(fragview::Texture::CompareFunc compareFunc);

extern unsigned getImageInternalFormat(fragview::Texture::Format format);

extern unsigned int getAccess(fragview::Texture::MapTarget target);

extern unsigned int getTextureGLFormat(fragview::Texture::Format format);

extern fragview::Texture::Format getTextureFormatUserSpace(unsigned int format);


#endif
