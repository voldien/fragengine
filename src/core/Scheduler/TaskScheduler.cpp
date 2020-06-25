#include "Core/TaskScheduler/TaskScheduler.h"
#include "Exception/RuntimeExecption.h"
#include <taskSch.h>

using namespace fragview;
TaskScheduler::TaskScheduler(void)
{
	schTaskSch *taskSch = (schTaskSch *)malloc(sizeof(schTaskSch));
	int sch = schCreateTaskPool(taskSch, 2, SCH_FLAG_NO_AFM, 48);
	if (sch != SCH_OK)
		throw RuntimeException(schErrorMsg(sch));

	this->sch = taskSch;
}

TaskScheduler::TaskScheduler(int cores, unsigned int maxPackagesPool)
{
	schTaskSch *taskSch = (schTaskSch *)malloc(sizeof(schTaskSch));
	int sch = schCreateTaskPool(taskSch, cores, SCH_FLAG_NO_AFM, maxPackagesPool);
	if (sch != SCH_OK)
		throw RuntimeException(schErrorMsg(sch));

	this->sch = taskSch;
}

TaskScheduler::~TaskScheduler(void)
{
	this->terminate();
	/*	Release.	*/
	delete this->sch;
}

static int internal_schCallback(struct sch_task_package_t *package)
{
	Task *task = (Task *)package->begin;
	IScheduler *scheduler = (IScheduler *)package->end;
	Task::TaskCallBack callback = task->callback;
	callback(task);
}
void TaskScheduler::AddTask(Task *task)
{
	schTaskPackage packageTask;
	packageTask.callback = internal_schCallback;
	packageTask.begin = task;
	packageTask.end = this;
	packageTask.puser = NULL;

	int status = schSubmitTask(this->sch, &packageTask, NULL);
	if (status != SCH_OK)
		throw RuntimeException(schErrorMsg(status));
}

void TaskScheduler::setUserData(const void *data)
{
	return schSetSchUserData(this->sch, data);
}
const void *TaskScheduler::getUserData(void)
{
	return schGetPoolUserData(this->sch, 0);
}
void TaskScheduler::run(void)
{
	int status = schRunTaskSch(this->sch);
	if (status != SCH_OK)
		throw RuntimeException(schErrorMsg(status));
}

void TaskScheduler::terminate(void)
{
	int status = schTerminateTaskSch(this->sch);
	if (status != SCH_OK)
		throw RuntimeException(schErrorMsg(status));
}