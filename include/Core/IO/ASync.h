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
#ifndef FRAGVIEW_ASYNC_H_
#define FRAGVIEW_ASYNC_H_ 1
#include"../RefPtr.h"
#include"../Ref.h"
#include"../TaskScheduler/IScheduler.h"
#include"IO.h"
#include<taskSch.h>
#include<map>

namespace fragview {

	typedef long ASyncHandle;											/*  */
	typedef void (*AsyncComplete)(ASync* async, ASyncHandle handle);	/*  */

	/**
	 *
	 */
	class FVDECLSPEC ASync : public SmartReference {
	public:
		ASync(void);
		ASync(Ref<IScheduler> &scheduler);
		~ASync(void);

		typedef struct io_status_t {
			unsigned int nbytes;    /*  Number of bytes read.   */
			unsigned int offset;    /*  Current position in bytes from start position.  */
			unsigned int status;    /*  Status of the termination of the IO operation.  */
		} IOStatus;

		//TODO determine if adding support for dynamic sized buffer read and write.
		//TODO add stragety perhaps for how to schedule it.
		virtual ASyncHandle aSyncOpen(Ref<IO> &io);
		virtual void asyncReadFile(ASyncHandle handle, char *buffer, unsigned int size, AsyncComplete complete);
		virtual void asyncReadFile(ASyncHandle handle, Ref<IO>& writeIO, AsyncComplete complete);
		virtual void asyncWriteFile(ASyncHandle handle, char *buffer, unsigned int size, AsyncComplete complete);
		virtual void asyncWriteFile(ASyncHandle handle, Ref<IO>& readIO, AsyncComplete complete);

		/*  */
		virtual void asyncWait(ASyncHandle handle);
		virtual bool asyncWait(ASyncHandle handle, long int timeout);
		virtual void asyncClose(ASyncHandle handle);

		/*  */
		virtual Ref<IO> getIO(ASyncHandle handle) const;
		virtual const IOStatus& getIOStatus(ASyncHandle handle) const;

		/*  */
		virtual Ref<IScheduler> getScheduler(void) const;

	private:
		/*  Static callback functions.  */
		static int async_open(Task* task);
		static int async_read(Task *task);
		static int async_read_io(Task *task);
		static int async_write(Task *task);
		static int async_write_io(Task *task);

	protected:  /*  */

		ASync(const ASync& other);
		virtual void setScheduleReference(Ref<IScheduler>& sch);

		typedef struct async_object {
			schSemaphore* semaphore;    /*  */
			Ref<IO> ref;                /*  */
			AsyncComplete callback;     /*  */
			Ref<IO> target;             /*  */
			char *buffer;               /*  */
			unsigned int size;          /*  */
			IOStatus status;            /*  */
			void *userData;             /*  */
			void *priv;				/*	*/
		} AsyncObject;

		AsyncObject* getObject(ASyncHandle handle);
		const AsyncObject* getObject(ASyncHandle handle) const;
		AsyncObject* createObject(ASyncHandle handle);

		/*  */
		std::map<ASyncHandle, AsyncObject> asyncs;
		UIDGenerator uidGenerator;
		Ref<IScheduler> scheduler;
	};
}

#endif