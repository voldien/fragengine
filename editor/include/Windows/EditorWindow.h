#ifndef _FRAG_EDITOR_EDITORWINDOW_H_
#define _FRAG_EDITOR_EDITORWINDOW_H_ 1
#include "Windows/Widget.h"
#include <Core/SmartReference.h>
#include <Window/Window.h>
#if defined(FRAG_GTK_WINDOW_MANAGER)
#include "Core/gtkconfig.h"
#elif defined(FRAG_EDITOR_QT_WINDOW_MANAGER)
//#include <QWindow>
#else
#endif

// TODO add namespace for the editor.
namespace frageditor {

	/**
	 *
	 */
	class FVDECLSPEC EditorWindow : public fragcore::Window {
	  public:
		EditorWindow();

		void show() override;

		void hide() override;

		void close() override;

		void focus() override;

		void restore() override;

		void maximize() override;

		void minimize() override;
		void setParent();

		void setTitle(const std::string &title) override;

		void resizable(bool resizable) override;

		std::string getTitle() const override;

		void getPosition(int *x, int *y) const override;

		void setPosition(int x, int y) override;

		void setSize(int width, int height) override;

		void getSize(int *width, int *height) const override;

		void setIcon(void *pVoid) override;

		void *getIcon() const override;

		fragcore::Display *getCurrentDisplay() const override;

		void AddWidget(Widget *widget);

		void setFullScreen(bool fullscreen) override;
		virtual void setFullScreen(fragcore::Display &display);

		bool isFullScreen() const;

		void setBordered(bool borded) override;

		void setMinimumSize(int width, int height) override;
		virtual void getMinimumSize(int *width, int *height);

		void setMaximumSize(int width, int height) override;
		virtual void getMaximumSize(int *width, int *height);

		float getGamma() const override;

		void setGamma(float gamma) override;

		intptr_t getNativePtr() const override;

	  private:
#if defined(FRAG_GTK_WINDOW_MANAGER)
		FragViewEditorAppWindow *window;
#elif defined(FRAG_EDITOR_QT_WINDOW_MANAGER)
		void *window;
#else
#endif
	};

} // namespace frageditor

#endif
