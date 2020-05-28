/**

    Copyright (C) 2014  Valdemar Lindberg

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
#ifndef _ANIMATION_H_
#define _ANIMATION_H_ 1
#include"Behavior.h"
#include"AnimationClip.h"
#include"Vector.h"

class AnimationController : public Behavior{
public:
	AnimationController(void);
	AnimationController(const AnimationController& animation);
	~AnimationController(void);

	virtual void instanceInitilize(void);
	virtual void onEnable(void);
	virtual void onDisable(void);
	virtual void initializeComponent(void);
	virtual void onDestroy(void);
	virtual Behavior* copyComponent(unsigned int& dataSize);

	int isPlay(void)const;
	int blend(AnimationClip* animationClip, float blendWeight = 1.0f);
	int blend(std::string& animationClip);
	void play(unsigned int clipIndex = 0);
	void play(const char* animationClip);
	void stop(void);
	void addClip(AnimationClip* animationClip);
	AnimationClip* getClip(unsigned int index);
	void removeClip(unsigned int Index);
	void removeClip(const char* Name);


	void internalUpdate(void);

private:
	float Time;
	unsigned int animationState;
	Vector<AnimationClip*> clip;
};

#endif
