#ifndef _FRAG_EDITOR_EDITORWINDOW_H_
#define _FRAG_EDITOR_EDITORWINDOW_H_ 1
#include <Core/SmartReference.h>
#include <Window/Window.h>
#include "Windows/Widget.h"
#if defined(FRAG_GTK_WINDOW_MANAGER)
#include"Core/gtkconfig.h"
#elif defined(FRAG_EDITOR_QT_WINDOW_MANAGER)
//#include <QWindow>
#else
#endif

//TODO add namespace for the editor.
namespace frageditor {

	/**
	 *
	 */
	class FVDECLSPEC EditorWindow : public fragcore::Window {
	public:
		EditorWindow();

		void show(void) override;

		void hide(void) override;

		void close(void) override;

		void focus(void) override;

		void restore(void) override;

		void maximize(void) override;

		void minimize(void) override;
		void setParent(void);

		void setTitle(const char *title) override;

		void resizable(bool resizable) override;

		const char *getTitle(void) const override;

		void getPosition(int *x, int *y) const override;

		void setPosition(int x, int y) override;

		void setSize(int width, int height) override;

		void getSize(int *width, int *height) const override;

		void setIcon(void *pVoid) override;

		void *getIcon(void) const override;

		fragcore::Display* getCurrentDisplay(void) const override;

		void AddWidget(Widget *widget);

		void setFullScreen(bool fullscreen) override;

		bool isFullScreen(void) const;

		void setBordered(bool borded) override;

		void setMinimumSize(int width, int height) override;

		void setMaximumSize(int width, int height) override;

		float getGamma(void) const override;

		void setGamma(float gamma) override;

		intptr_t getNativePtr(void) const override;

	private:
	#if defined(FRAG_GTK_WINDOW_MANAGER)
		FragViewEditorAppWindow* window;
	#elif defined(FRAG_EDITOR_QT_WINDOW_MANAGER)
		void *window;
		#else
	#endif
	};

}

#endif