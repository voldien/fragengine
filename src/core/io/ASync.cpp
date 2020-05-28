#include <Utils/StringUtil.h>
#include <Core/IO/IFileSystem.h>
#include <Exception/RuntimeExecption.h>
#include <Exception/InvalidArgumentException.h>
#include"Core/IO/ASync.h"

using namespace fragview;

ASyncHandle ASync::aSyncOpen(Ref<IO> &io) {

	if (*sch == NULL)
		throw RuntimeException("Async not initialized with scheduler");
	/*  Check parameters.   */
	if (!*io)
		throw InvalidArgumentException("Invalid IO reference.");

	/*  Increment reference.    */
	io->increment();

	/*  Create async object.*/
	ASyncHandle handle = this->uidGenerator.getNextLUID();
	AsyncObject *asyncObject = createObject(handle);
	asyncObject->ref = io;
	asyncObject->semaphore = NULL;
	asyncObject->buffer = NULL;
	asyncObject->size = 0;
	asyncObject->userData = NULL;
	asyncObject->callback = NULL;

	return handle;
}

void ASync::asyncReadFile(ASyncHandle handle, char *buffer, unsigned int size,
                          AsyncComplete complete) {
	int error;
	/*  Get object and check if exists. */
	AsyncObject *ao = getObject(handle);

	if (!ao->ref->isReadable())
		throw RuntimeException(fvformatf("IO object is not readable %d", ao->ref->getUID()));

	/*  Assign variables.   */
	error = schCreateSemaphore((schSemaphore **) &ao->semaphore);
	if (error != SCH_OK)
		throw RuntimeException(fvformatf("Failed to create semaphore %s", schErrorMsg(error)));
	ao->buffer = buffer;
	ao->size = size;
	ao->callback = complete;
	ao->userData = NULL;

	/*  Reset status counter.   */
	ao->status.nbytes = 0;
	ao->status.offset = 0;

	schTaskPackage readTask = {};
	readTask.callback = async_read;
	readTask.size = handle;
	readTask.begin = this;
	readTask.puser = ao;

	error = schSubmitTask(*this->getScheduler(), &readTask, 0);
	if (error != SCH_OK)
		throw RuntimeException(fvformatf("failed %s", schErrorMsg(error)));
}

void ASync::asyncReadFile(ASyncHandle handle, Ref<IO>& writeIO, AsyncComplete complete){
	AsyncObject *ao = getObject(handle);

	/*  Check that open file is readable.   */
	if (!ao->ref->isReadable())
		throw RuntimeException(fvformatf("IO object is not writable %d", ao->ref->getUID()));
	/*  Check if IO object is writeable.    */
	if (!writeIO->isWriteable())
		throw RuntimeException(fvformatf("IO object is not writable %d", writeIO->getUID()));
}

void ASync::asyncWriteFile(ASyncHandle handle, char *buffer, unsigned int size,
                           AsyncComplete complete) {
	int error;
	AsyncObject *ao = getObject(handle);
	//TODO perhaps can to use the IOBuffer has a interface object for reduced coupling and higher cohesion.
	if (!ao->ref->isWriteable())
		throw RuntimeException(fvformatf("IO object is not writable %d", ao->ref->getUID()));

	/*  Assign variables.   */
	error = schCreateSemaphore((schSemaphore **) &ao->semaphore);
	if (error != SCH_OK)
		throw RuntimeException(fvformatf("Failed to create semaphore %s", schErrorMsg(error)));

	ao->buffer = buffer;
	ao->size = size;
	ao->callback = complete;
	ao->userData = NULL;

	/*  Reset status counter.   */
	ao->status.nbytes = 0;
	ao->status.offset = 0;

	schTaskPackage readTask;
	readTask.callback = async_write;
	readTask.size = handle;
	readTask.begin = this;
	readTask.puser = ao;

	error = schSubmitTask(*this->getScheduler(), &readTask, 0);
	if (error != SCH_OK)
		throw RuntimeException(fvformatf("failed %s", schErrorMsg(9)));
}

void ASync::asyncWriteFile(ASyncHandle handle, Ref<IO>& io, AsyncComplete complete){

}

Ref<IO> ASync::getIO(ASyncHandle handle) const {
	return getObject(handle)->ref;
}

const ASync::IOStatus& ASync::getIOStatus(ASyncHandle handle) const {
	return this->getObject(handle)->status;
}

RefPtr<schTaskSch> ASync::getScheduler(void) const {
	return this->sch;
}

void ASync::asyncWait(fragview::ASyncHandle handle) {
	AsyncObject *ao = getObject(handle);

	schSemaphoreWait((schSemaphore *) ao->semaphore);
	//schCreateSemaphore(ao->semaphore);
//	schSemaphorePost((schSemaphore *) ao->semaphore);
	/*  Set as finished.    */
	//ao->status.
}

bool ASync::asyncWait(ASyncHandle handle, long int timeout){
	AsyncObject *ao = getObject(handle);

	return true;//schSemaphoreTimedWait((schSemaphore *)ao->semaphore, timeout) == SCH_OK;
}

void ASync::asyncClose(ASyncHandle handle) {
	AsyncObject *ao = this->getObject(handle);

	/*  Check status of the scheduler.  */
	//TODO determine.

	asyncWait(handle);

	/*  If not used by scheduler anymore, delete all references.    */
	schDeleteSemaphore(ao->semaphore);
	if (ao->ref->deincreemnt())
		ao->ref->close();

	this->asyncs.erase(this->asyncs.find(handle));
}

int ASync::async_open(schTaskPackage *package) {

	const char *path = (const char *) package->begin;
	ASync *async = (ASync *) package->puser;
	IFileSystem *fileSystem;

	Ref<IO> refIO = Ref<IO>(fileSystem->openFile(path, IO::READ));

	/*  Create the task in succession.  */
	return 0;
}

int ASync::async_read(schTaskPackage *package) {
	AsyncObject *ao = (AsyncObject *) package->puser;
	const size_t block_size = 512;

	Ref<IO> &io = ao->ref;
	long int nread;
	while (ao->status.nbytes < ao->size) {
		long int nread = io->read(block_size, &ao->buffer[ao->status.nbytes]);
		if (nread <= 0)
			break;
		ao->status.nbytes += nread;
	}

	/*  Finished.   */
	if(ao->callback)
		ao->callback(NULL, NULL);
	/*  Finish and posted for the data is available.  */
	schSemaphorePost((schSemaphore *) ao->semaphore);
	return nread;
}

int ASync::async_read_io(schTaskPackage *package) {
	AsyncObject *ao = (AsyncObject *) package->puser;
	const size_t block_size = 512;
	//TODO update for the IO based..
	Ref<IO> &io = ao->ref;
	long int nread;
	while (ao->status.nbytes < ao->size) {
		long int nread = io->read(block_size, &ao->buffer[ao->status.nbytes]);
		if (nread <= 0)
			break;
		ao->status.nbytes += nread;
	}

	/*  Finished.   */
	if(ao->callback)
		ao->callback(NULL, NULL);
	/*  Finish and posted for the data is available.  */
	schSemaphorePost((schSemaphore *) ao->semaphore);
	return nread;
}

int ASync::async_write(schTaskPackage *package) {
	AsyncObject *ao = (AsyncObject *) package->puser;
	const size_t block_size = 512;

	Ref<IO> &io = ao->ref;
	long int nwritten;
	while (ao->status.nbytes < ao->size) {
		long int nwritten = io->write(block_size, &ao->buffer[ao->status.nbytes]);
		if (nwritten <= 0)
			break;
		ao->status.nbytes += nwritten;
	}

	io->flush();
	if(ao->callback)
		ao->callback(NULL, NULL);
	/*  Finish and posted for the data is available.  */
	schSemaphorePost((schSemaphore *) ao->semaphore);
	return nwritten;
}


int ASync::async_write_io(schTaskPackage *package) {
	return 0;
}


ASync::AsyncObject *ASync::getObject(ASyncHandle handle) {

	if (this->asyncs.find(handle) != this->asyncs.end())
		return &this->asyncs[handle];

	throw RuntimeException(fvformatf("Invalid Async object %d", handle));
}

const ASync::AsyncObject* ASync::getObject(ASyncHandle handle) const{
	std::map<ASyncHandle, AsyncObject>::const_iterator it = this->asyncs.find(handle);
	if (it != this->asyncs.cend())
		return &it->second;

	throw RuntimeException(fvformatf("Invalid Async object %d", handle));
}

ASync::AsyncObject *ASync::createObject(ASyncHandle handle) {
	return &this->asyncs[handle];
}

ASync::ASync(RefPtr<schTaskSch> refPtr) {
	this->sch = refPtr;
	this->uidGenerator = UIDGenerator();
	/*  Take out the 0 UID that is invalid for the async handle
	 * for allowing checking if it is a valid handle.*/
	this->uidGenerator.getNextLUID();
}

void ASync::setScheduleReference(RefPtr<schTaskSch> sch) {
	this->sch = sch;
}

ASync::~ASync(void) {
	this->getScheduler();
}

ASync::ASync(void) {
	//this->sch = NULL;
}

ASync::ASync(const ASync &other) {
	this->sch = other.sch;
	this->uidGenerator = other.uidGenerator;
}



