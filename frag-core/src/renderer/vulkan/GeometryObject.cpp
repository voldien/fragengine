#include"Renderer/IRenderer.h"
#include"Renderer/Geometry.h"
#include"Renderer/Buffer.h"
#include"Renderer/vulkan/internal_object_type.h"
using namespace fragcore;



unsigned int GeometryObject::getVertexCount() {
	VKGeometryObject *geobj = (VKGeometryObject *) this->pdata;

	return geobj->desc.numVerticecs;
}

unsigned int GeometryObject::getIndicesCount(void) {
	VKGeometryObject *geobj = (VKGeometryObject *) this->pdata;

	return geobj->desc.numIndices;
}


intptr_t GeometryObject::getNativePtr(void) const {
	return 0;
}