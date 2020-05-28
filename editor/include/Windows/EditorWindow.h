#ifndef FRAGVIEW_EDITOR_EDITORWINDOW_H_
#define FRAGVIEW_EDITOR_EDITORWINDOW_H_ 1
#include <Core/SmartReference.h>
#include <Core/Window.h>
#include"Core/gtkconfig.h"

/**
 *
 */
class FVDECLSPEC EditorWindow : public fragview::Window {
public:
	void showWindow(void) override;

	void hideWindow(void) override;

	void closeWindow(void) override;

	void focus(void) override;

	void restore(void) override;

	void maximize(void) override;

	void minimize(void) override;

	void setTitle(const char *title) override;

	void resizable(bool resizable) override;

	const char *getTitle(void) const override;

	void getPosition(int *x, int *y) const override;

	void setPosition(int x, int y) override;

	void setSize(int width, int height) override;

	void getSize(int *width, int *height) const override;

	void setIcon(void *pVoid) override;

	void *getIcon(void) const override;

	fragview::Display* getCurrentDisplay(void) const override;

	void setFullScreen(bool fullscreen) override;

	void setBordered(bool borded) override;

	void setMinimumSize(int width, int height) override;

	void setMaximumSize(int width, int height) override;

	float getGamma(void) const override;

	void setGamma(float gamma) override;

	intptr_t getNativePtr(void) const override;

private:
	FragViewEditorAppWindow* window;
};

#endif