#ifndef FRAGVIEW_MATH_H_
#define FRAGVIEW_MATH_H_ 1
#include"../Def.h"
#include<math.h>
#include<hpm/hpm.h>

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
			return (deg * (T)HPM_PI) / 180.0f;
		}

		/**
		 *	Convert radian to degree.
		 */
		template<class T>
		inline static T radToDeg(T deg) {
			return (deg * (T)180) / (T)HPM_PI;
		}

		/**
		 * Linear interpolation.
		 */
		template<typename T>
		inline static float lerp(T a, T b, T t) {
			return a + (b - a) * t;
		}

		/**
		 *	Generate 1D guassian.
		 */
		static void guassian1Df(float* guassian, int width, double theta);

		/**
		 *	Generate 2D guassian.
		 */
		static void guassian2Df(float* guassian, int height, float theta);
	};
}

#endif