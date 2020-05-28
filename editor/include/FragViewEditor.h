#ifndef FRAGVIEW_FRAGVIEWEDITOR_H_
#define FRAGVIEW_FRAGVIEWEDITOR_H_ 1
#include <Def.h>
#include<Core/Ref.h>
#include<Scene/Scene.h>
#include<FragViewCore.h>
#include "Windows/EditorWindow.h"

/**
 *
 */
class FVDECLSPEC FragViewEditor {
public:
	FragViewEditor(SplashWindow* splashWindow, int argc, const char** argv);
	void run(void);

protected:
	void init(void);
private:
	EditorWindow* root;
	//GTKRendererWindow* rendererWindow;  //TODO improve and etc.
	fragview::IConfig* config;
	fragview::Ref<fragview::IRenderer> renderer;
	fragview::Ref<fragview::Scene> scene;
};

#endif