#include <RenderPipeline.h>
#include"Renderer/ProgramPipeline.h"
#include <Scene/Scene.h>
#include <Utils/ShaderUtil.h>
#include <stdexcept>
#include <csignal>
#include <FontFactory.h>
#include"RenderPipeline.h"
#include"Utils/RenderTargetFactory.h"
#include"Renderer/Query.h"
#include"Renderer/Sync.h"
#include"Renderer/Query.h"
#include"Renderer/ViewPort.h"
using namespace fragview;
/*	Display quad.	*/
const float gc_quad[4][3] = {
		{-1.0f, -1.0f, 0.0f},
		{-1.0f, 1.0f,  0.0f},
		{1.0f,  -1.0f, 0.0f},
		{1.0f,  1.0f,  0.0f},
};
extern void updateUniforms(Shader* shaderProgram, const UniformLocation* locations, const FragGraphicUniform *uniforms);

RenderPipeline::RenderPipeline(Ref<IRenderer>& renderer, const IConfig* config) {
	this->init(renderer, config);
}

RenderPipeline::~RenderPipeline(void) {
	/*  Display objects.    */
	if (this->quadDisplay->deincreemnt())
		this->renderer->deleteGeometry(*this->quadDisplay);
	if (this->quadDisplayIndirect->deincreemnt())
		this->renderer->deleteBuffer(*this->quadDisplayIndirect);
	if (this->displayShader->deincreemnt())
		this->renderer->deletePipeline(*this->displayShader);

	/*  Compute objects.    */
	if (this->compute->deincreemnt())
		this->renderer->deleteTexture(*this->compute);
	if (this->computeView->deincreemnt())
		this->renderer->deleteTexture(*this->computeView);
	if (this->computeIndirect->deincreemnt())
		this->renderer->deleteBuffer(*this->computeIndirect);

	/*  */
	if(this->frameBuffer->deincreemnt())
		this->renderer->deleteFrameBuffer(*this->frameBuffer);

	/*  Sync object.    */
	if (this->syncObject->deincreemnt())
		this->renderer->deleteSync(*this->syncObject);

	if (this->renderer->deincreemnt())
		delete *this->renderer;
}

void RenderPipeline::createFrameTexture(IRenderer *renderer, unsigned int width, unsigned height, bool ComputeShader) {

	//TODO add support for the configuration to change the size.
	if (*this->frameBuffer) {
		if (this->frameBuffer->deincreemnt())
			this->renderer->deleteFrameBuffer(*this->frameBuffer);
	}

	//TODO get and use the resolution scale.
	this->frameBuffer = Ref<FrameBuffer>(RenderTargetFactory::createColor(*this->renderer, width, height));
	this->frameBuffer->setName("framebuffer");

	if (ComputeShader) {

		/*  Create compute texture. */
		TextureDesc computeTextureDesc = {};
		computeTextureDesc.width = width;
		computeTextureDesc.height = height;
		computeTextureDesc.depth = 1;
		computeTextureDesc.target = TextureDesc::eTexture2D;
		computeTextureDesc.sampler.AddressU = SamplerDesc::eRepeat;
		computeTextureDesc.sampler.AddressV = SamplerDesc::eRepeat;
		computeTextureDesc.sampler.AddressW = SamplerDesc::eRepeat;
		computeTextureDesc.sampler.minFilter = SamplerDesc::eLinear;
		computeTextureDesc.sampler.magFilter = SamplerDesc::eLinear;
		computeTextureDesc.sampler.mipmapFilter = SamplerDesc::eNoFilterMode;
		computeTextureDesc.internalformat = TextureDesc::eRGBA;
		computeTextureDesc.format = TextureDesc::eRGBA;
		computeTextureDesc.type = TextureDesc::eUnsignedByte;
		computeTextureDesc.immutable = true;
		computeTextureDesc.srgb = 1;
		computeTextureDesc.usemipmaps = 0;
		computeTextureDesc.compression = TextureDesc::eNoCompression;
		computeTextureDesc.marker.markerName = "Compute display image texture.";
		if (*this->compute) {
			if (this->compute->deincreemnt())
				this->renderer->deleteTexture(*this->compute);
		}

		this->compute = Ref<Texture>((*this->renderer)->createTexture(&computeTextureDesc));

		computeTextureDesc.originalTexture = *this->compute;
		computeTextureDesc.internalformat = TextureDesc::eRGBA;
		computeTextureDesc.type = TextureDesc::eUnsignedByte;
		computeTextureDesc.srgb = 0;
		computeTextureDesc.marker.markerName = "Compute display image view texture.";

		if (*this->computeView) {
			if (this->computeView->deincreemnt())
				this->renderer->deleteTexture(*this->computeView);
		}
		this->computeView = Ref<Texture>(this->renderer->createTexture(&computeTextureDesc));
	}
}

void RenderPipeline::init(Ref<IRenderer>& renderer, const IConfig* config) {

	if (renderer == NULL)
		throw InvalidArgumentException("Requires non null renderer interface object.");
	this->renderer = renderer;
	this->viewPort = renderer->getView(0);
	Capability capability;

	this->renderer->getCapability(&capability);

	/*  Create the sync object. */
	SyncDesc syncDesc = {};
	this->syncObject = Ref<Sync>(renderer->createSync(&syncDesc));

	/*	Create display quad.    */
	GeometryDesc geopldesc = {0};
	geopldesc.primitive = GeometryDesc::eTriangleStrips;
	geopldesc.buffer = gc_quad;
	geopldesc.numVertexAttributes = 1;
	geopldesc.vertexStride = sizeof(gc_quad[0]);
	geopldesc.numVerticecs = sizeof(gc_quad) / sizeof(gc_quad[0]);
	geopldesc.vertexattribute[0].index = 0;
	geopldesc.vertexattribute[0].offset = 0;
	geopldesc.vertexattribute[0].size = 3;
	geopldesc.vertexattribute[0].datatype = GeometryDesc::eFloat;
	geopldesc.marker.markerName = "Display Quad.";

	BufferDesc indirectDrawBufDesc= {};
	IndirectDrawArray indirectDrawArray = {
			.count = 4,
			.instanceCount = 1,
			.first = 0,
			.baseInstance = 0,
	};
	indirectDrawBufDesc.type = BufferDesc::eIndirectDraw;
	indirectDrawBufDesc.data = &indirectDrawArray;
	indirectDrawBufDesc.size = sizeof(indirectDrawArray);
	indirectDrawBufDesc.hint = (BufferDesc::BufferHint)(BufferDesc::eRead | BufferDesc::eStatic);
	indirectDrawBufDesc.marker.markerName = "Quad indirect buffer";
	this->quadDisplayIndirect = Ref<Buffer>((*this->renderer)->createBuffer(&indirectDrawBufDesc));

	/*  Create display quad.    */
	this->quadDisplay = Ref<Geometry>((*this->renderer)->createGeometry(&geopldesc));

	/*  Create display shader.  */
	ProgramPipeline* programPipeline;
	ShaderUtil::loadDisplayShader(*this->renderer, &programPipeline);
	this->displayShader = Ref<ProgramPipeline>(programPipeline);

	int width, height;
	this->viewPort->getViewPort(0,0, &width, &height);

	//TODO relocate to the sandbox scene object.
	BufferDesc computeDesc = {};
	IndirectDispatch dispatch = {
			.num_groups_x = (width / 16),
			.num_groups_y = (height / 16),
			.num_groups_z = 1,
	};
	computeDesc.type = BufferDesc::eIndirectDispatch;
	computeDesc.data = &dispatch;
	computeDesc.size = sizeof(dispatch) * 64;
	computeDesc.hint = (BufferDesc::BufferHint)(BufferDesc::eRead | BufferDesc::eStream);
	computeDesc.marker.markerName = "Compute indirect dispatch";
	this->computeIndirect = Ref<Buffer>((*this->renderer)->createBuffer(&computeDesc));

	this->supportComputeShader = capability.sComputeShader;
	createFrameTexture(*renderer, width, height, this->supportComputeShader);


	//TODO relocate later!
	//this->font = FontFactory::createFont("ipag.ttf", 10, *this->renderer);
}

void RenderPipeline::draw(Scene *scene) {
	this->renderer = renderer;

	(*this->renderer)->clear(eColor | eDepth);
	(*this->renderer)->clearColor(0.15f, 0.15f, 0.15f, 1.0f);
	/*  Check if sandbox sub scene exists.  */
	SandBoxSubScene *sandbox = scene->getGLSLSandBoxScene();
	if(sandbox)
		drawSandBox(sandbox);
}

void RenderPipeline::drawSandBox(SandBoxSubScene* sandbox){

	/*  TODO add rendering settings for handle the execution.   */
	//TODO add fragment sampling.
	if (sandbox) {
		const FragGraphicUniform *uniforms = sandbox->getFragUniform();
		bool resultInFrameBuffer = false;
		Texture* backTexture;

		/*  Bind all textures.   */
		if(sandbox->getNumTextures() > 0)
			this->renderer->bindTextures(0, sandbox->getTextures());

		/*  Disable unnecessary rasterization functionalities.*/
		this->renderer->enableState(IRenderer::eBlend);
		this->renderer->disableState(IRenderer::eDepthTest);
		this->renderer->disableState(IRenderer::eCullface);
		this->renderer->disableState(IRenderer::eStencilTest);
		this->renderer->disableState(IRenderer::eMultiSampling);
		this->renderer->enableState(IRenderer::eAlphaTest);
		this->renderer->enableState(IRenderer::eSampleShading);

		/*  Draw with all shaders.  */
		unsigned int nthBoundAttachment = 0;
		unsigned int nthPrevBoundAttachment = 1;
		unsigned int nrBoundAttachment = 2;
		for (int i = 0; i < sandbox->getNumShaders(); i++) {
			/*  */
			ProgramPipeline *shader = sandbox->getShader(i);
			if(i == 0){
				//this->frameBuffer->write();
				//this->frameBuffer->clear(CLEARBITMASK::eColor);
			}

			/*  Get next framebuffer.   */
			if (sandbox->getNumShaders() > 1) {
				FrameBuffer *frame = *this->frameBuffer;
				Texture *prevTexture = frame->getAttachment(nthPrevBoundAttachment);
				Texture *currentTexture = frame->getAttachment(nthBoundAttachment);
				FrameBuffer::BufferAttachment attachment = (FrameBuffer::BufferAttachment) (FrameBuffer::eColor0 +
				                                                                            nthBoundAttachment);

				/*  */
				frame->blend(FrameBuffer::BlendEqu::eAddition, FrameBuffer::BlendFunc::eSrcAlpha, FrameBuffer::BlendFunc::eOneMinusSrcAlpha,
				             attachment);
				frame->setDraw(attachment);
				frame->bind();

				/*  Resize. */
				this->viewPort->setDimensions(0, 0, frame->width(), frame->height());
				backTexture = prevTexture;
				resultInFrameBuffer = true;
			}

			/*  */
			Shader* frag = shader->getShader(ProgramPipeline::FRAGMENT_SHADER);
			const UniformLocation *locations = sandbox->getUniformLocation(shader->getUID());
			shader->bind();

			/*  backbuffer. */
			if(locations->backbuffer >= 0)
				backTexture->bind(locations->backbuffer);
			/*  Update dynamic variables. shader uniforms. */
			if (locations->time >= 0)
				frag->setFloat(locations->time, uniforms->time.time);
			if (locations->deltatime >= 0)
				frag->setFloat(locations->deltatime, uniforms->time.deltaTime);
			if (locations->resolution >= 0)
				frag->setVec2v(locations->resolution, 1, &uniforms->window.width);
			if (locations->position >= 0)
				frag->setVec2v(locations->position, 1, &uniforms->window.x);
			if (locations->mouse >= 0)
				frag->setVec2v(locations->mouse, 1, &uniforms->inputs.x);
			if (locations->movement >= 0)
				frag->setVec2v(locations->movement, 1, &uniforms->inputs.ax);
			if (locations->pointer >= 0)
				frag->setVec2v(locations->pointer, 1, &uniforms->inputs.x);
			if (locations->offset >= 0)
				frag->setVec2v(locations->offset, 1, &uniforms->inputs.x);


			/*  Draw the fragment shader.   */
			this->quadDisplayIndirect->bind();
			this->renderer->drawIndirect(*this->quadDisplay);

			/*  Update the texture attachment.  */
			nthBoundAttachment++;
			nthBoundAttachment %= nrBoundAttachment;
			nthPrevBoundAttachment++;
			nthPrevBoundAttachment %= nrBoundAttachment;
		}

		/*  */
		for (int i = 0; i < sandbox->getNumCompute(); i++ && this->supportComputeShader) {
			ProgramPipeline *compute = sandbox->getCompute(i);

			/*  Bind indirect.  */
			compute->bind();
			this->computeIndirect->bind();

			/*  Update the uniforms.    */
			const UniformLocation *locations = sandbox->getUniformLocation(compute->getUID());
			updateUniforms(compute->getShader(ProgramPipeline::COMPUTE_SHADER), locations, uniforms);
			if (locations->backbuffer >= 0)
				backTexture->bind(locations->backbuffer);

			/*  Bind all textures.  */
			for (int i = 0; i < sandbox->getNumTextures(); i++)
				sandbox->getTexture(i)->bindImage(i + 1, 0, Texture::eRead, Texture::eR8G8B8A8);
			this->computeView->bindImage(0, 0, Texture::eWrite, Texture::eR8G8B8A8);

			/*  */
			this->renderer->dispatchCompute(NULL, NULL, i * sizeof(IndirectDispatch));

			resultInFrameBuffer = true;
			/*  If last compute - copy to the output texture.    */
			if (i == sandbox->getNumCompute() - 1) {
				const Texture *source = *this->compute;
				Texture *target = (*this->frameBuffer)->getAttachment(0);

				this->renderer->copyTexture(source, target);
			} else {

			}
		}

		/*  Final display.  */
		if (resultInFrameBuffer) {

			/*  Get default framebuffer.    */
			FrameBuffer *Default = this->renderer->getDefaultFramebuffer(NULL);
			//this->renderer->blit(*this->frameBuffer, Default, Texture::eBilinear);
			//this->renderer->blit(this->frameBuffer, Default);//TODO relocate the responsiblity with the framebuffer blit.
//
			Default->write();

			/*  Get the last texture render too.    */
			Texture *backBuffer = this->frameBuffer->getAttachment(0);

			/*  Set viewport matching the current window.   */
			Texture *defaultTexture = Default->getAttachment(0);
			this->viewPort->setDimensions(0, 0, defaultTexture->width(), defaultTexture->height());

			this->displayShader->bind();
			backBuffer->bind(0);

			this->quadDisplayIndirect->bind();
			this->renderer->drawIndirect(*this->quadDisplay);
		}

		//this->frameBuffer->write();
		/*  Render Font.    */
		//this->font->getCharacter(0);
		//this->font->getTexture()->bind(0);
	}
}



void RenderPipeline::setViewport(int x, int y, int width, int height){
	/*  Initialize synchronization object.*/
	this->syncObject->fence();

	/*  Update the viewport and set default scissor view.   */
	this->viewPort->setDimensions(x, y, width, height);
	this->viewPort->setscissorView(x, y, width, height);

	//TODO add for fetching the local variable size of the local group.
	//TODO see if can be set manually.
	/*  Update the compute dispatch buffer.*/
	IndirectDispatch dispatch = {
			.num_groups_x = (unsigned int) (width / 16),
			.num_groups_y = (unsigned int) (height / 16),
			.num_groups_z = 1
	};
	//TODO relocate to sandbox scene object.
	void *dispatchBuf = this->computeIndirect->mapBuffer(Buffer::MapTarget::eWrite | Buffer::MapTarget::eNoSync, 0,
	                                                     sizeof(IndirectDispatch));
	//IndirectDispatch* dispatch = (IndirectDispatch*)dispatchBuf;
	for(int i = 0; i < 0; i++){

	}
	memcpy(dispatchBuf, &dispatch, sizeof(dispatch));
	this->computeIndirect->unMapBuffer();

	/*  Resize framebuffers. */
	this->createFrameTexture(*this->renderer, width, height, this->supportComputeShader);

	// Wait in till all the resources are ready.
	while(this->syncObject->waitClient(16) != Sync::eComplete);
}
