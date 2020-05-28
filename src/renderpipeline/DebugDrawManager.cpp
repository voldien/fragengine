#include"RenderPipeline/DebugDrawManager.h"
#include"RenderPipeline/Mesh.h"

using namespace fragview;

void DebugDrawManager::draw(Scene *scene, FrameBuffer *frame, IRenderer *render) {
	/*  */
}

void DebugDrawManager::setViewport(int width, int height, IRenderer *render) {

}

RenderQueue DebugDrawManager::getSupportedQueue(void) const {
	return Overlay;
}

void
DebugDrawManager::addLine(const PVVector3 &start, const PVVector3 &end, const PVColor &color, float lineWidth,
                          float duration, bool depthEnabled) {
	DebugDrawCommand debugDrawCommand;

	debugDrawCommand.type = LINE;
//	debugDrawCommand.command.line.start = *(hpmvec3f*)((float*)end);
//	debugDrawCommand.command.line.end =  *(hpmvec3f*)((float*)end);
	this->commands[LINE].enqueue(debugDrawCommand);
}

void DebugDrawManager::addCross(const PVVector3 &position, const PVColor &color, float size, float duration,
                                bool depthEnabled) {

}

void DebugDrawManager::addSphere(const PVColor &position, float radius, const PVColor &color, float duration,
                                 bool depthEnabled) {

}

void DebugDrawManager::addCircle(const PVVector3 &centerPosition, const PVVector3 &planeNormal, float radius,
                                 const PVColor &color, float duration, bool depthEnabled) {

}

void
DebugDrawManager::addAxes(const Transform &xfm, const PVColor &color, float size, float duration, bool depthEnabled) {

}

void DebugDrawManager::addTriangle(const PVVector3 &a, const PVVector3 &b, const PVVector3 &c, float duration,
                                   bool depthEnabled) {

}

void DebugDrawManager::addAABB(const PVAABB &aabb, const PVColor &color, float duration, bool depthEnabled) {

}

void DebugDrawManager::addOBB(const PVOBB &obb, const PVColor &color, float duration, bool depthEnabled) {

}

void DebugDrawManager::addString(const PVVector3 &a, const std::string &text, float duration, bool depthEnabled) {

}

DebugDrawManager::DebugDrawManager(Ref<Font> &font) {
	this->font = font;
	/*  Generate the mesh object.   */
	// AABB bounding box
	// Line circle
	// Sphere
	// Line Cross
	// Axis
	/*  Line, Triangle generated on the fly.    */

	/*  Setup queue.    */
	//this->commands.resize(4096);
}
