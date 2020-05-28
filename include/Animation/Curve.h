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
#ifndef _CURVE_H_ 
#define _CURVE_H_ 1 
#include"KeyFrame.h"

class Curve : public Object{
public:
	Curve(void);
	~Curve(void);

	void release(void);
	void addKey(const KeyFrame& keyFrame,int index = -1);
	KeyFrame getKey(unsigned int  index)const;
	int getKeyCount(void)const;
	void removeKey(unsigned int  index);

	inline float linearInterpolation(unsigned int index,float time);
//--------------------------------------------------
/* Get Curve Value based on Tangent Out & In Value.
*/
	inline  float tangentInterpolation(unsigned int index,float time);



private:
	KeyFrame* keysFrame;
	unsigned int length;
	char* NodeName;
	unsigned int* pointer;
	unsigned int curveFlag;

	//--------------------------------------------------
	/**/
	//inline Transform* ELTAPIFASTENTRY transform(void){return CASTP(Transform*,this->pointer);}
	//--------------------------------------------------
	/**/
	//template<class T> INLINE T* ELTAPIFASTENTRY GetPointerType(Void){return CASTP(T*,this->pointer);}

};

#endif
