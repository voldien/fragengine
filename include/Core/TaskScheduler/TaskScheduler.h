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
#ifndef _FRAGVIEW_TASK_SCHEDULER_H_
#define _FRAGVIEW_TASK_SCHEDULER_H_ 1
#include "../RefPtr.h"
#include"IScheduler.h"
#include "../Ref.h"
#include "IO.h"
#include <map>

namespace fragview {
	class FVDECLSPEC TaskScheduler : IScheduler
	{
	public:
		TaskScheduler(void);
		TaskScheduler(int cores, unsigned int maxPackagesPool);
		~TaskScheduler(void);

		virtual void AddTask(Task *task);
		virtual void setUserData(const void *data);
		virtual const void *getUserData(void);
		virtual void run(void);
		virtual void terminate(void);
		private:
			schTaskSch *sch;
	};
}
#endif