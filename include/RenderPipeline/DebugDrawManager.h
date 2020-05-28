
#ifndef _FRAGVIEW_DEBUGMANAGER_H_
#define _FRAGVIEW_DEBUGMANAGER_H_ 1
#include <RenderPipeline/IRenderPipelineBase.h>
#include <Core/dataStructure/Queue.h>
#include <Font.h>
#include <Scene/SubGraph/Transform.h>

namespace fragview {
	/**
	 *
	 */
	class FVDECLSPEC DebugDrawManager : public IRenderPipelineBase {
	public:
		DebugDrawManager(Ref<Font>& font);

		//TODO reduce argument.
		void draw(Scene *scene, FrameBuffer *frame, IRenderer *render) override;

		void setViewport(int width, int height, IRenderer *render) override;

		RenderQueue getSupportedQueue(void) const override; /*  Render as overlay only. */

		virtual void addLine(const PVVector3 &start,
		                     const PVVector3 &end, const PVColor &color, float lineWidth = 1.0f,
		                     float duration = 0.0f, bool depthEnabled = true);

		virtual void addCross(const PVVector3 &position,
		                      const PVColor &color,
		                      float size, float duration = 0.0f, bool depthEnabled = true);

		virtual void addSphere(const PVColor &position,
		                       float radius,
		                       const PVColor &color, float duration = 0.0f, bool depthEnabled = true);

		virtual void addCircle(const PVVector3 &centerPosition,
		                       const PVVector3 &planeNormal, float radius,
		                       const PVColor &color, float duration = 0.0f, bool depthEnabled = true);

		virtual void addAxes(const Transform &xfm,
		                     const PVColor &color,
		                     float size, float duration = 0.0f, bool depthEnabled = true);

		virtual void addTriangle(const PVVector3 &a, const PVVector3 &b, const PVVector3 &c, float duration = 0.0f,
		                         bool depthEnabled = true);

		virtual void addAABB(const PVAABB& aabb, const PVColor& color, float duration = 0.0f, bool depthEnabled = true);

		virtual void addOBB(const PVOBB &obb, const PVColor &color, float duration = 0.0f, bool depthEnabled = true);
		virtual void
		addString(const PVVector3 &a, const std::string &text, float duration = 0.0f, bool depthEnabled = true);

	private:

		enum DrawType {
			LINE,
			CROSS,
			SPHERE,
			CIRCLE,
			AXES,
			TRIANGLE,
			AABB,
			OBB,
			STRING
		};


		typedef struct DebugDrawCommand_t {
			DrawType type;          /*  */
			bool depthEnabled;      /*  */
			float timeRemaining;    /*  */
			float invokeTime;       /*  */
			hpmvec4f color;
			union Command {

				struct {
					hpmvec3f start;
					hpmvec3f end;
				} line;

				struct {
					hpmvec3f pos;
				} cross;

				struct {
					hpmvec3f pos;
				} sphere;

				struct {
					hpmvec3f pos;
				} cirlcle;

				struct {
					hpmvec3f pos;
				} axes;

				struct {
					hpmvec3f a, b, c;
				} triangle;

				struct {
					hpmvec3f pos;
				} aabb;

				struct {
					hpmvec3f a, b, c;
				} obb;

				struct {
					hpmvec3f pos;
					int textIndex;
					//std::string text;
				} string;
			};

			Command command;
		} DebugDrawCommand;

		/*  TODO perhaps multiple queus based on the command such as depth for creating sorted command list.    */
		std::map<int, Queue<DebugDrawCommand>> commands;  /*  */

		Ref<Mesh> debugGeometry;            /*  Geometry of the debug objects. - multiple sub geometries.   */
		Ref<Font> font;                     /*  */
	};
}

#endif