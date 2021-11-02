
#ifndef _FRAG_ENGINE_DEBUGMANAGER_H_
#define _FRAG_ENGINE_DEBUGMANAGER_H_ 1
#include "../Prerequisites.h"
#include "../Scene/SubGraph/Transform.h"
#include "IRenderPipelineBase.h"
#include <Core/dataStructure/Queue.h>
#include <FragCore.h>
#include <Renderer/Prerequisites.h>
#include <fragcore/Def.h>

namespace fragengine {
	using namespace fragcore;
	/**
	 *
	 */
	class FVDECLSPEC DebugDrawManager
		: public IRenderPipelineBase { // TODO determine if shall be changed to virtual class.
	  public:
		DebugDrawManager(Ref<Font> &font, Ref<IRenderer> &render);

		// TODO reduce argument.
		void draw(Scene *scene, FrameBuffer *frame, IRenderer *render) override;

		void setViewport(int width, int height, IRenderer *render) override;

		RenderQueue getSupportedQueue() const override; /*  Render as overlay only. */

		virtual void addLine(const Vector3 &start, const Vector3 &end, const Color &color, float lineWidth = 1.0f,
							 float duration = 0.0f, bool depthEnabled = true);

		virtual void addCross(const Vector3 &position, const Color &color, float size, float duration = 0.0f,
							  bool depthEnabled = true);

		virtual void addSphere(const Color &position, float radius, const Color &color, float duration = 0.0f,
							   bool depthEnabled = true);

		virtual void addCircle(const Vector3 &centerPosition, const Vector3 &planeNormal, float radius,
							   const Color &color, float duration = 0.0f, bool depthEnabled = true);

		virtual void addAxes(const Transform &xfm, const Color &color, float size, float duration = 0.0f,
							 bool depthEnabled = true);

		virtual void addTriangle(const Vector3 &a, const Vector3 &b, const Vector3 &c, float duration = 0.0f,
								 bool depthEnabled = true);

		virtual void addAABB(const PVAABB &aabb, const Color &color, float duration = 0.0f, bool depthEnabled = true);

		virtual void addOBB(const PVOBB &obb, const Color &color, float duration = 0.0f, bool depthEnabled = true);
		virtual void addString(const Vector3 &a, const std::string &text, float duration = 0.0f,
							   bool depthEnabled = true);

	  private:
		enum DrawType { LINE, CROSS, SPHERE, CIRCLE, AXES, TRIANGLE, AABB, OBB, STRING };

		typedef struct DebugDrawCommand_t {
			DrawType type;		 /*  */
			bool depthEnabled;	 /*  */
			float timeRemaining; /*  */
			float invokeTime;	 /*  */
			hpmvec4f color;		 /*	Common Color attribute.	*/
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
				} string;
			};

			Command command;
		} DebugDrawCommand;

		/*  TODO perhaps multiple queus based on the command such as depth for creating sorted command list.    */
		std::map<int, Queue<DebugDrawCommand>> commands; /*  */
		Ref<Mesh> debugGeometry;	   /*  Geometry of the debug objects. - multiple sub geometries.   */
		std::vector<int> geomtryIndex; /*	*/
		Ref<Shader> debug;
		Ref<Shader> line;
		Ref<Font> font; /*  */
		Ref<Mesh> debugFont;
	};
} // namespace fragengine

#endif
