#include "Scene/SceneFactory.h"
#include "Renderer/RenderDesc.h"
#include "Renderer/IRenderer.h"
using namespace fragcore;
using namespace fragengine;

Scene *SceneFactory::createScene(IRenderer *rendering, SceneFactory::WorldScene world) {
	Scene *scene = new Scene();

	if (world & eSandBox) {
// 		scene->createGLSLSandBoxScene();
// 		SandBoxSubScene *sandbox = scene->getGLSLSandBoxScene();
// 		FragGraphicUniform *fragGraphicUniform = sandbox->getFragUniform();

// 		const int nrInDispatch = 256;
// 		BufferDesc computeDesc = {};
// 		computeDesc.type = BufferDesc::eIndirectDispatch;
// 		computeDesc.data = NULL;
// 		computeDesc.size = sizeof(IndirectDispatch) * nrInDispatch;
// 		computeDesc.hint = (BufferDesc::BufferHint)(BufferDesc::eRead | BufferDesc::eStream);
// 		computeDesc.marker.markerName = "Compute indirect dispatch";
// 		scene->getGLSLSandBoxScene()->setDisptchBuffer(Ref<Buffer>(rendering->createBuffer(&computeDesc)));

// 		/*  Initialize the fragment.  */
// 		fragGraphicUniform->inputs.x = 0.0f;
// 		fragGraphicUniform->inputs.y = 0.0f;
// 		fragGraphicUniform->inputs.ax = 0.0f;
// 		fragGraphicUniform->inputs.ay = 0.0f;
// 		fragGraphicUniform->inputs.wheel = 0.0f;
// 		fragGraphicUniform->inputs.wheelacc = 0.0f;

// 		int view[2];
// //		rendering->getView(0)-> NULL, NULL, &view[0], &view[1]);
// //		fragGraphicUniform->window.width = view[0];
// //		fragGraphicUniform->window.height = view[1];
// //		fragGraphicUniform->window.x = 0.0f;
// //		fragGraphicUniform->window.y = 0.0f;

// 		fragGraphicUniform->time.time = 0.0f;
// 		fragGraphicUniform->time.deltaTime = 0.0f;

	}
	if (world & eWorldSpace) {
		/*  Create world objects.   */


	}
	scene->time = new Time();

	return scene;
}
