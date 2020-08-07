#ifndef _FRAG_CORE_EVENT_H_
#define _FRAG_CORE_EVENT_H_ 1
//TODO improve for adding event based model for the engine

///**
// *	Event base class.
// */
//class VDDECLSPEC VDEvent{
//		public:
//
//		VDEvent(void);
//		VDEvent(const VDEvent& event);
//		virtual ~VDEvent(void);
//
//		/**
//		 *	On resize event.
//		 */
//		virtual void VDAPIENTRY onResize(int width, int height);
//
//		/**
//		 *	on mouse move or clicks a button.
//		 */
//		virtual void VDAPIENTRY onMouse(int x, int y, int button);
//
//		/**
//		 *	on mouse motion.
//		 */
//		virtual void VDAPIENTRY onMouseMotion(int xmotion, int ymotion, VDInput::Button button);
//
//		/**
//		 *	On mouse pressed event.
//		 */
//		virtual void VDAPIENTRY onMousePressed(VDInput::Button pressed);
//
//		/**
//		 *	On mouse button release.
//		 */
//		virtual void VDAPIENTRY onMouseReleased(VDInput::Button released);
//
//		/**
//		 *	On mouse wheel event.
//		 */
//		virtual void VDAPIENTRY onMouseWheel(int direction);
//
//		/**
//		 *	On key pressed event.
//		 */
//		virtual void VDAPIENTRY onKeyPressed(Uint32 keycode);
//
//		/**
//		 *	On key release event.
//		 */
//		virtual void VDAPIENTRY onKeyRelease(Uint32 keycode);
//
//		/**
//		 *	On key event.
//		 */
//		virtual void VDAPIENTRY onKey(Uint32 keycode);
//
//
//		public:	/*	Static methods.	*/
//
//		/**
//		 *	Get number of registered event handler.
//		 */
//		static unsigned int VDAPIENTRY getNumEvents(void);
//
//		/**
//		 *	Get list of all event handlers.
//		 */
//		static VDVector<VDEvent*>* VDAPIENTRY getEvents(void);
//
//		/**
//		 *	Get event by index.
//		 */
//		static VDEvent* VDAPIENTRY getEvent(unsigned int index);
//};

#endif //FRAGVIEW_EVENT_H
