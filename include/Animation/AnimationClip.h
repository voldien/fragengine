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
#ifndef _ANIMATION_CLIP_H_
#define _ANIMATION_CLIP_H_ 1
#include"Object.h"
#include"KeyFrame.h"
#include"Curve.h"
#include"Vector3.h"
#include"Quaternion.h"
#include"Vector.h"
#include"Stack.h"
#include<string>

enum eAnimationState {
	eDefault = 0x1,
	eOnce = 0x2,
	eLoop = 0x4,
	ePingPong = 0x8
};

class AnimationClip : public Object{
public:
	AnimationClip(void);
	AnimationClip(const AnimationClip& clip);
	~AnimationClip(void);

	void setPosition(const Vector3& position);
	Vector3 getPosition(void)const;

	void setRotation(const Quaternion& rotation);
	Quaternion getRotation(void)const;

	void setScale(const Vector3& scale);
	Vector3 getScale(void)const;

	void  reIndex(void);

	void release(void);

private:
	Vector<Curve> curves;
	float duration;
	float frameTicks;
	eAnimationState animationState;
	void findNodeDataPointer(Transform* transform);

	void releaseCurveData(void);

};

#endif
