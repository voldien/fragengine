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
#ifndef _KEY_FRAME_H_ 
#define _KEY_FRAME_H_ 1

class KeyFrame{
public:
	KeyFrame(void);
	KeyFrame(const KeyFrame& keyframe);
	KeyFrame(float value,float time);
	KeyFrame(float value,float time,float tangentIn,float tangentOut);
	~KeyFrame(void);

private:
	float tangentIn;
	float tangentOut;
	float time;
	float value;
};

#endif
