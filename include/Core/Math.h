/**
    FrameView for rendering shaders in screen space.
    Copyright (C) 2018  Valdemar Lindberg

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
#ifndef FRAGVIEW_MATH_H_
#define FRAGVIEW_MATH_H_ 1
#include"../Def.h"
#include<math.h>

namespace fragview {

	/**
	 *
	 */
	class FVDECLSPEC Math {
	public:

		template<class T>
		inline static T clamp(T a, T min, T max){ return Math::max<T>( min , Math::min<T>( max , a ) ); }
		inline static int clamp(int a, int min, int max){ return Math::clamp<int>(a, min ,max);}
		inline static float clampf(float a, float min, float max){ return Math::clamp<float>(a, min ,max); }
		inline static double clampd(double a, double min, double max){ return Math::clamp<double>(a, min ,max); }

		/**
		 *	Get max value of a and b.
		 */
		template<typename T>
		inline static T max(T a, T b){ return ( (a) < (b) ) ? (b) : (a);}
		inline static float maxf(float a, float b){ return ( (a) < (b) ) ? (b) : (a);}
		inline static float maxd(float a, float b){ return ( (a) < (b) ) ? (b) : (a);}
		inline static float maxi(float a, float b){ return ( (a) < (b) ) ? (b) : (a);}

		/**
		 *	Get min value of a and b.
		 */
		template<typename T>
		inline static T min(T a, T b){ return ( (a) > (b) ) ? (b) : (a);}
		inline static float minf(float a, float b){ return ( (a) > (b) ) ? (b) : (a);}
		inline static float mind(float a, float b){ return ( (a) > (b) ) ? (b) : (a);}
		inline static float mini(float a, float b){ return ( (a) > (b) ) ? (b) : (a);}

		/**
		 *	Get float modular.
		 */
		inline static float modf(float a){double part; return ::modf(a, &part);}
		inline static float modd(double a){ double part; return ::modf(a, &part);}
		inline static float modi(float a, float b){ return ( (a) < (b) ) ? (a) : (b);}

		/**
		 *	Convert degree to radian.
		 */
		template<class T>
		inline static T deg2Rad(T deg) {
			return (deg * (T)Math::PI) / 180.0f;
		}

		/**
		 *	Convert radian to degree.
		 */
		template<class T>
		inline static T radToDeg(T deg) {
			return (deg * (T)180) / (T)Math::PI;
		}

		/**
		 * Linear interpolation.
		 */
		template <typename T, typename U>
		inline static T lerp(T a, T b, U t)
		{
			return a + (b - a) * t;
		}

		template<typename T, typename U>
		inline static T lerpUnclamped(T a, T b, U t){
			return a + (b - a) * t;
		}

		static float LerpAngle(float a, float b, float t);

		/*	*/
		static const float Epsilon;
		static const float PI;
		static const float Infinite;
		static const float Deg2Rad;
		static const float Rad2Deg;
		static const float NegativeInfinity;

		/*	*/
		template <typename T>
		static T NextPowerOfTwo(T v){
			return 0;
		}
		template <typename T>
		static T ClosestPowerOfTwo(T v)
		{
			return 0;
		}
		template<typename T>
		static bool IsPowerOfTwo(T v){
			return false;
		}
		static int CorrelatedColorTemperatureToRGB();

		/**
		 *	Generate 1D guassian.
		 */
		static void guassian1Df(float *guassian, int width, double theta);

		/**
		 *	Generate 2D guassian.
		 */
		static void guassian2Df(float* guassian, int height, float theta);

		/**
		 * 
		 */
		static float linearToGammaSpace(float linear);
		static float GameSpaceToLinear(float gamma, float exp);

		/**
		 * 
		 */
		static float PerlinNoise(float x, float y);
		static float PerlinNoiseDifferential(float x, float y);
		static float PerlinNoise(float x, float y, float z);
		static float PerlinNoiseDifferential(float x, float y, float z);
	};
}

#endif