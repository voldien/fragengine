#include"Renderer/FrameBuffer.h"
using namespace fragcore;

void FrameBuffer::bind(void) {

}

void FrameBuffer::unBind(void) {

}

void FrameBuffer::write(void) {

}

void FrameBuffer::read(void) {

}

Texture *FrameBuffer::getAttachment(unsigned int index) {

}

Texture *FrameBuffer::getDepthAttachment(void) {

}

Texture *FrameBuffer::getStencilAttachment(void) {

}


int FrameBuffer::width(void) {}

int FrameBuffer::height(void) {}

int FrameBuffer::nrSamples(void) {}

void FrameBuffer::blend(BlendEqu equ, BlendFunc sfactor, BlendFunc dfactor, BufferAttachment bufferAttachment) {

}
//virtual void blendSeperate(BlendFunc func, BlendEqu equ, BufferAttachment bufferAttachment);


void FrameBuffer::setDraws(unsigned int nr, BufferAttachment *attachment){}
void FrameBuffer::setDraw(BufferAttachment attachment){}

void FrameBuffer::setName(const std::string &name) {
	Object::setName(name);
}

intptr_t FrameBuffer::getNativePtr(void) const {
	return 0;
}
