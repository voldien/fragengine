#include"RenderPipeline/DebugDrawManager.h"
#include"RenderPipeline/Mesh.h"
#include<Font.h>
#include<Buffer.h>
#include<ViewPort.h>
#include<FrameBuffer.h>
#include<Query.h>
//#include <Renderer/ProgramPipeline.h>
#include <Sync.h>

using namespace fragcore;
using namespace fragengine;

void DebugDrawManager::draw(Scene *scene, FrameBuffer *frame, IRenderer *render) {
	/*  */
}

void DebugDrawManager::setViewport(int width, int height, IRenderer *render) {

}

RenderQueue DebugDrawManager::getSupportedQueue() const {
	return (RenderQueue)(Geometry | Overlay);
}

void
DebugDrawManager::addLine(const Vector3 &start, const Vector3 &end, const Color &color, float lineWidth,
                          float duration, bool depthEnabled) {
	DebugDrawCommand debugDrawCommand;

	debugDrawCommand.type = DrawType::LINE;
	debugDrawCommand.depthEnabled = depthEnabled;
	//	debugDrawCommand.command.line.start = *(hpmvec3f*)((float*)end);
	//	debugDrawCommand.command.line.end =  *(hpmvec3f*)((float*)end);
	this->commands[DrawType::LINE].enqueue(debugDrawCommand);
}

void DebugDrawManager::addCross(const Vector3 &position, const Color &color, float size, float duration,
                                bool depthEnabled) {
	DebugDrawCommand debugDrawCommand;

	debugDrawCommand.type = DrawType::CROSS;
	debugDrawCommand.depthEnabled = depthEnabled;
}

void DebugDrawManager::addSphere(const Color &position, float radius, const Color &color, float duration,
                                 bool depthEnabled) {
	DebugDrawCommand debugDrawCommand;
	debugDrawCommand.type = DrawType::SPHERE;
	debugDrawCommand.depthEnabled = depthEnabled;
}

void DebugDrawManager::addCircle(const Vector3 &centerPosition, const Vector3 &planeNormal, float radius,
                                 const Color &color, float duration, bool depthEnabled) {
	DebugDrawCommand debugDrawCommand;
	debugDrawCommand.type = DrawType::CIRCLE;
	debugDrawCommand.depthEnabled = depthEnabled;
}

void
DebugDrawManager::addAxes(const Transform &xfm, const Color &color, float size, float duration, bool depthEnabled) {
	DebugDrawCommand debugDrawCommand;
	debugDrawCommand.type = DrawType::AXES;
	debugDrawCommand.depthEnabled = depthEnabled;
}

void DebugDrawManager::addTriangle(const Vector3 &a, const Vector3 &b, const Vector3 &c, float duration,
                                   bool depthEnabled) {
	DebugDrawCommand debugDrawCommand;
	debugDrawCommand.type = DrawType::TRIANGLE;
	debugDrawCommand.depthEnabled = depthEnabled;
}

void DebugDrawManager::addAABB(const AABB &aabb, const Color &color, float duration, bool depthEnabled) {
	DebugDrawCommand debugDrawCommand;
	debugDrawCommand.type = DrawType::AABB;
	debugDrawCommand.depthEnabled = depthEnabled;
}

void DebugDrawManager::addOBB(const OBB &obb, const Color &color, float duration, bool depthEnabled) {
	DebugDrawCommand debugDrawCommand;
	debugDrawCommand.type = DrawType::OBB;
	debugDrawCommand.depthEnabled = depthEnabled;
}

void DebugDrawManager::addString(const Vector3 &a, const std::string &text, float duration, bool depthEnabled) {
	DebugDrawCommand debugDrawCommand;
	debugDrawCommand.type = DrawType::STRING;
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
