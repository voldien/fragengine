#ifndef _FRAG_EDITOR_RENDERERWINDOW_H_
#define _FRAG_EDITOR_RENDERERWINDOW_H_ 1
#include <Renderer/RendererWindow.h>
#include "EditorWindow.h"

namespace frageditor {
	/**
	 *
	 */
	class FVDECLSPEC EditorRendererWindow : public fragcore::RendererWindow, public EditorWindow
	{
	public:
		void showWindow(void) override;

		void hideWindow(void) override;

		void swapBuffer(void) override;

		void getPosition(int *x, int *y) const override;

		void setPosition(int x, int y) override;

		void setSize(int width, int height) override;

		void getSize(int *width, int *height) const override;

		void vsync(bool state) override;

		fragcore::Display *getCurrentDisplay(void) const override;

		float getGamma(void) const override;

		void setGamma(float gamma) override;

		void closeWindow(void) override;

		void setTitle(const char *title) override;

		void resizable(bool resizable) override;

		const char *getTitle(void) const override;

	protected:
		void createWindow(int x, int y, int width, int height, const char *api) override;

		void useWindow(void *data) override;

	protected:
		bool assertConfigAttributes(const fragcore::IConfig *iConfig) override;
	};
}


#endif