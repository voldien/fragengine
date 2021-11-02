#include"Scene/Time.h"
#include<SDL2/SDL_timer.h>
#include<time.h>
#include <Scene/Time.h>

using namespace fragcore;
using namespace fragengine;

Time *Time::curTime = NULL;

Time::Time() {
	this->_private_level_startup = SDL_GetPerformanceCounter();
	this->ticks = SDL_GetPerformanceCounter();
	this->timeResolution = SDL_GetPerformanceFrequency();
	this->scale = 1.0f;
	this->fixed = 1000.0f / 60.0f;
	this->idelta = 0;
}

void Time::start() {
	this->_private_level_startup = SDL_GetPerformanceCounter();
}

float Time::deltaTime() {
	return gc_fdelta;
}

float Time::smoothDeltaTime() {
	float sumTime = delta_data[0] + delta_data[1] + delta_data[2] + delta_data[3] + delta_data[4];
	return (sumTime / (float) nDeltaTime) * this->getTimeScale();
}

unsigned int Time::time() {
	return SDL_GetTicks();
}

float Time::timef() {
	return ((float)SDL_GetPerformanceCounter() - (float)this->_private_level_startup) / (float)timeResolution;
}

double Time::timed() {
	return (double) SDL_GetPerformanceCounter() / (double) timeResolution;
}

long int Time::getUnixTime() {
	return 0;// ::time(NULL);
}

float Time::getTimeScale() {
	return Time::scale;
}

void Time::setTimeScale(float scale) {
	Time::scale = scale;
	/*	Update fixed update timer	*/
}

long int Time::getTimeResolution() {
	return timeResolution;
}

float Time::fixedTime() {
	return fixed / getTimeScale();
}

float Time::internal_delta_timef() {
	double ttime = (double) (SDL_GetPerformanceCounter() - this->ticks) / (double) timeResolution;
	return (float) ttime * this->getTimeScale();
}

void Time::internalUpdate() {
	gc_fdelta = internal_delta_timef();
	delta_data[idelta] = this->deltaTime();
	++idelta %= nDeltaTime;

	//	update ticks.
	Time::ticks = SDL_GetPerformanceCounter();
}

Time *Time::getCurrentTime() {
	return curTime;
}

void Time::setCurrentTime(Time *time) {
	curTime = time;
}

const char *Time::getDate() {
	time_t current_time = ::time(NULL);
	return ctime(&current_time);
}
