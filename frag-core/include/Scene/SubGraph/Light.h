/**
	Simple physic simulation with a server-client model support.
	Copyright (C) 2016  Valdemar Lindberg

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
#ifndef _LIGHT_H_
#define _LIGHT_H_ 1
#include"Frustum.h"

namespace fragview {
	/**
	 *	Light.
	 */
	class FVDECLSPEC Light : public Frustum {
	public:

		/**
		 *
		 */
		enum LightType {
			ePoint      = 0x1,  /*	Point light, aka omni light.	*/
			eSpot       = 0x2,  /*	Spot light.	*/
			eDirection  = 0x3,  /*	Direction light.	*/
			eArea		= 0x4,	/*	*/
		};

		Light(void);

		Light(const Light &other);

		~Light(void);


		void setType(LightType);

		LightType getType(void) const;


//	/**
//	 *	Set light color.
//	 */
//	void setColor(const PVColor &color);
//
//	PVColor getColor(void) const;
//

		void setIntensity(float intensity);

		float getIntensity(void);

		void setShadowStrength(float strength);

		float getShadowStrength(void);

		//shadowBias
		//cullingMask
		//spotAngle
		//range
		//innerSpotAngle
		//colorTemperature
		//LightRenderMode
//
//
//	/**
//	 *
//	 * @return
//	 */
//	PVMatrix4x4 getShadowMatrix(void);

	private:    /*	Attributes.	*/

		//PVColor color;          /*	*/
		float intensity;        /*	*/
		float shadowstrength;   /*	*/
		LightType lightType;
	};
}

#endif
