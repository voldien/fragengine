/**
    FrameView for rendering shaders in screen space.
    Copyright (C) 2018  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _FILE_NOTIFY_H_
#define _FILE_NOTIFY_H_ 1
#include"../Prerequisites.h"
#include"FileChangeEvent.h"
#include"../Core/Object.h"
#include"../Core/TaskScheduler/TaskScheduler.h"
#include"../Core/dataStructure/PoolAllocator.h"
#include<libfswatch/c/libfswatch_types.h>
#include<libfswatch/c/cevent.h>
#include<map>

namespace fragview {
	/**
	 *
	 */
	class FVDECLSPEC FileNotify : public SmartReference {	//TOOD determine if shall be change to interface based.
	public:

		/**
		 * Start the file notification process.
		 */
		void start(void);
		void stop(void);

	protected:

		/**
		 *
		 */
		class FVDECLSPEC FileNoticationEntry {
		public:
			int key;                /*  */
			std::string filepath;   /*  */
			Object *assetObject;    /*  */
			AssetType type;         /*  */
		};

	public:

		void registerAsset(const char *filepath, Object *object, AssetType type);

		void unregisterAsset(Object *notify);

		void unRegisterAllAsset(void);

		void eventDone(FileNotificationEvent *event);

	private:

		/**
		 *
		 * @param path
		 */
		void addFilePath(const char *path, Object *object);

		/**
		 *
		 * @param path
		 */
		void removeFilePath(const char *path, Object *object);

		/**
		 *
		 * @param path
		 * @return
		 */
		Object *getObject(const char *path);

		/**
		 *
		 * @param object
		 * @return
		 */
		FileNoticationEntry *getEntry(Object *object);

		/**
		 *
		 * @param events
		 * @param event_num
		 * @param data
		 */
		static void callback(fsw_cevent const *const events,
		                     const unsigned int event_num,
		                     void *data);

		/**
		 *
		 * @param package
		 * @return
		 */
		static int fileFetchTask(Task *package);

		/**
		 * Start fswatch internal process.
		 */
		static void *fswatch(const void *psession);

	private:

		std::map<int, FileNoticationEntry> notify;  /*  List of update-able assets.  */
		std::map<std::string, Object *> objectMap;  /*  */
		FSW_HANDLE session;                         /*  */

		void *pthread;      /*  Thread for async operations. */
		Ref<IScheduler> scheduler;
		PoolAllocator<FileNotificationEvent> fileChangeEvents;

	public: /*  */

		FileNotify(Ref<IScheduler>& sch);

		~FileNotify(void);
	};
}

#endif