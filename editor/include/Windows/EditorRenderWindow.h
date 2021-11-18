#ifndef _FRAG_EDITOR_RENDERERWINDOW_H_
#define _FRAG_EDITOR_RENDERERWINDOW_H_ 1
#include "EditorWindow.h"
#include <RendererWindow.h>

namespace frageditor {
	/**
	 *
	 */
	class FVDECLSPEC EditorRendererWindow : public fragcore::RendererWindow, public EditorWindow {
	  public:
		void show() override;

		void hide() override;

		void swapBuffer() override;

		void getPosition(int *x, int *y) const override;

		void setPosition(int x, int y) override;

		void setSize(int width, int height) override;

		void getSize(int *width, int *height) const override;

		void vsync(bool state) override;

		fragcore::Display *getCurrentDisplay() const override;

		float getGamma() const override;

		void setGamma(float gamma) override;

		void close() override;

		void setTitle(const std::string& title) override;

		void resizable(bool resizable) override;

		std::string getTitle() const override;

	  protected:
		void createWindow(int x, int y, int width, int height, const char *api) override;

		void useWindow(void *data) override;

	  protected:
		bool assertConfigAttributes(const fragcore::IConfig *iConfig) override;
	};
} // namespace frageditor

#endif
