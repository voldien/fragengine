#ifndef _FRAG_CORE_VIDEO_MANAGER_H_
#define _FRAG_CORE_VIDEO_MANAGER_H_ 1
#include"../Def.h"
#include"VideoTexture.h"
#include"Core/Singleton.h"
#include"Core/TaskScheduler/IScheduler.h"

namespace fragview
{
	/**
	 * 
	 */
	class FVDECLSPEC VideoManager : public Singleton<VideoManager> {
	public:
		static void computeVideoTask(Task* task);

		void registerVideo(VideoTexture* video);
		void unRegisterVideo(VideoTexture* video);

	private: /*	Prevent one from creating an instance of this class.	*/
		VideoManager(void);

		VideoManager(const VideoManager &other);
	};
}
#endif