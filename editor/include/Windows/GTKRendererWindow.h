#ifndef FRAGVIEW_EDITOR_GTKRENDERERWINDOW_H_
#define FRAGVIEW_EDITOR_GTKRENDERERWINDOW_H_ 1
#include <Renderer/RendererWindow.h>
#include "EditorWindow.h"

/**
 *
 */
class FVDECLSPEC GTKRendererWindow : public fragcore::RendererWindow, public EditorWindow {
public:
	void showWindow() override;

	void hideWindow() override;

	void swapBuffer() override;

	void getPosition(int *x, int *y) const override;

	void setPosition(int x, int y) override;

	void setSize(int width, int height) override;

	void getSize(int *width, int *height) const override;

	void vsync(bool state) override;

	fragcore::Display* getCurrentDisplay() const override;

	float getGamma() const override;

	void setGamma(float gamma) override;

	void closeWindow() override;

	void setTitle(const char *title) override;

	void resizable(bool resizable) override;

	const char *getTitle() const override;

protected:
	void createWindow(int x, int y, int width, int height, const char *api) override;

	void useWindow(void *data) override;

protected:
	bool assertConfigAttributes(const fragcore::IConfig *iConfig) override;
};

#endif