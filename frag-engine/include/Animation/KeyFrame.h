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
#ifndef _FRAG_CORE_KEY_FRAME_H_
#define _FRAG_CORE_KEY_FRAME_H_ 1

namespace fragcore{
    /**
     *
     */
    class FVDECLSPEC KeyFrame {
    public:
        KeyFrame();
        KeyFrame(const KeyFrame& keyframe);
        KeyFrame(float value,float time);
        KeyFrame(float value, float time, float tangentIn, float tangentOut);
        ~KeyFrame();

        float getValue(float time);
    private:
        float tangentIn;
        float tangentOut;
        float value;
        float time;

    };
}
#endif
