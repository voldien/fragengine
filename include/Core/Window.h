
#ifndef FRAGVIEW_WINDOW_H_
#define FRAGVIEW_WINDOW_H_ 1

#include "SmartReference.h"
#include "Display.h"

namespace fragview {
	/**
	 *
	 */
	class FVDECLSPEC Window : public SmartReference {
	public:
		virtual void showWindow(void) = 0;

		virtual void hideWindow(void) = 0;

		virtual void closeWindow(void) = 0;

		virtual void focus(void) = 0;

		virtual void restore(void) = 0;

		virtual void maximize(void) = 0;

		virtual void minimize(void) = 0;

		virtual void setTitle(const char *title) = 0;

		virtual const char *getTitle(void) const = 0;

		//TODO change the type
		virtual void setIcon(void*) = 0;

		virtual void* getIcon(void) const = 0;

		virtual void getPosition(int *x, int *y) const = 0;

		virtual void setPosition(int x, int y) = 0;

		virtual void setSize(int width, int height) = 0;

		virtual void getSize(int *width, int *height) const = 0;

		virtual Display *getCurrentDisplay(void) const = 0;

		virtual float getGamma(void) const = 0;

		virtual void setGamma(float gamma) = 0;

		virtual void resizable(bool resizable) = 0;

		virtual void setFullScreen(bool fullscreen) = 0;

		virtual void setBordered(bool borded) = 0;

		virtual void setMinimumSize(int width, int height) = 0;

		virtual void setMaximumSize(int width, int height) = 0;

		FV_ALWAYS_INLINE void setUserData(void *userData) {
			this->userData = userData;
		}

		FV_ALWAYS_INLINE virtual void *getUserData(void) const {
			return this->userData;
		}

		virtual intptr_t getNativePtr(void) const = 0;  /*  Get native window reference object. */

	protected:  /*  Internal utility methods.   */

		virtual void calculateGammaLookupTable(float gamma, ushort* rgbRamp) const; /*  */
		virtual float computeGammaExponent(const ushort* rgbRamp) const;            /*  */

	protected:
		void *userData = NULL;
	};
}

#endif