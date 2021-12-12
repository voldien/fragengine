/*
 *	FragEngine - Fragment Engine
 *	Copyright (C) 2016  Valdemar Lindberg
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef _FRAG_ENGINE_ANIMATION_H_
#define _FRAG_ENGINE_ANIMATION_H_ 1
#include"Behavior.h"
#include"AnimationClip.h"
#include"Vector.h"

namespace fragengine {

	/**
	 *
	 */
	class FVDECLSPEC AnimationController : public Behavior {
	public:
		AnimationController();
		AnimationController(const AnimationController& animation);
		~AnimationController();

		virtual void instanceInitilize();
		virtual void onEnable();
		virtual void onDisable();
		virtual void initializeComponent();
		virtual void onDestroy();
		virtual Behavior* copyComponent(unsigned int& dataSize);

		int isPlay()const;
		int blend(AnimationClip* animationClip, float blendWeight = 1.0f);
		int blend(std::string& animationClip);
		void play(unsigned int clipIndex = 0);
		void play(const char* animationClip);
		void stop();
		void addClip(AnimationClip* animationClip);
		AnimationClip* getClip(unsigned int index);
		void removeClip(unsigned int Index);
		void removeClip(const char* Name);


		void internalUpdate();

	private:
		float Time;
		unsigned int animationState;
		Vector<AnimationClip*> clip;
	};
}
#endif
