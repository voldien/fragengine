#include"RenderPipeline/DebugDrawManager.h"
#include"RenderPipeline/Mesh.h"
#include<Font.h>
#include<Renderer/Buffer.h>
#include<Renderer/ViewPort.h>
#include<Renderer/FrameBuffer.h>
#include<Renderer/Query.h>
//#include <Renderer/ProgramPipeline.h>
#include <Renderer/Sync.h>

using namespace fragcore;
using namespace fragengine;

void DebugDrawManager::draw(Scene *scene, FrameBuffer *frame, IRenderer *render) {
	/*  */
}

void DebugDrawManager::setViewport(int width, int height, IRenderer *render) {

}

RenderQueue DebugDrawManager::getSupportedQueue(void) const {
	return (RenderQueue)(Geometry | Overlay);
}

void
DebugDrawManager::addLine(const Vector3 &start, const Vector3 &end, const Color &color, float lineWidth,
                          float duration, bool depthEnabled) {
	DebugDrawCommand debugDrawCommand;

	debugDrawCommand.type = LINE;
	debugDrawCommand.depthEnabled = depthEnabled;
	//	debugDrawCommand.command.line.start = *(hpmvec3f*)((float*)end);
	//	debugDrawCommand.command.line.end =  *(hpmvec3f*)((float*)end);
	this->commands[LINE].enqueue(debugDrawCommand);
}

void DebugDrawManager::addCross(const Vector3 &position, const Color &color, float size, float duration,
                                bool depthEnabled) {
	DebugDrawCommand debugDrawCommand;

	debugDrawCommand.type = CROSS;
	debugDrawCommand.depthEnabled = depthEnabled;
}

void DebugDrawManager::addSphere(const Color &position, float radius, const Color &color, float duration,
                                 bool depthEnabled) {
	DebugDrawCommand debugDrawCommand;
	debugDrawCommand.type = SPHERE;
	debugDrawCommand.depthEnabled = depthEnabled;
}

void DebugDrawManager::addCircle(const Vector3 &centerPosition, const Vector3 &planeNormal, float radius,
                                 const Color &color, float duration, bool depthEnabled) {
	DebugDrawCommand debugDrawCommand;
	debugDrawCommand.type = CIRCLE;
	debugDrawCommand.depthEnabled = depthEnabled;
}

void
DebugDrawManager::addAxes(const Transform &xfm, const Color &color, float size, float duration, bool depthEnabled) {
	DebugDrawCommand debugDrawCommand;
	debugDrawCommand.type = AXES;
	debugDrawCommand.depthEnabled = depthEnabled;
}

void DebugDrawManager::addTriangle(const Vector3 &a, const Vector3 &b, const Vector3 &c, float duration,
                                   bool depthEnabled) {
	DebugDrawCommand debugDrawCommand;
	debugDrawCommand.type = TRIANGLE;
	debugDrawCommand.depthEnabled = depthEnabled;
}

void DebugDrawManager::addAABB(const PVAABB &aabb, const Color &color, float duration, bool depthEnabled) {
	DebugDrawCommand debugDrawCommand;
	debugDrawCommand.type = AABB;
	debugDrawCommand.depthEnabled = depthEnabled;
}

void DebugDrawManager::addOBB(const PVOBB &obb, const Color &color, float duration, bool depthEnabled) {
	DebugDrawCommand debugDrawCommand;
	debugDrawCommand.type = OBB;
	debugDrawCommand.depthEnabled = depthEnabled;
}

void DebugDrawManager::addString(const Vector3 &a, const std::string &text, float duration, bool depthEnabled) {
	DebugDrawCommand debugDrawCommand;
	debugDrawCommand.type = STRING;
	debugDrawCommand.depthEnabled = depthEnabled;
}

DebugDrawManager::DebugDrawManager(Ref<Font> &font, Ref<IRenderer>& renderer) {
	this->font = font;
	//setRenderer(renderer);
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
