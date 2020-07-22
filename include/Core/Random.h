#ifndef _FRAGVIEW_RANDOM_H_
#define _FRAGVIEW_RANDOM_H_ 1
#include"../Def.h"

namespace fragview {
	class FVDECLSPEC Random {
	public:

		/**
		 *	Override the seed.
		 */
		void setSeed(unsigned long long seed);

		/**
		 *	Get next random value.
		 */
		unsigned int rand(void);

		/**
		 *	Get next normalized random value.
		 */
		float randfNormalize(void);

		/**
		 *	Get next random float value.
		 */
		float randf(void)const;

		float range(float min, float max);

	private:	/*	Attributes.	*/
//
//		unsigned long long seed;	/*	*/
//		unsigned long long mult;	/*	*/
//		unsigned long long llong_max;	/*	*/
//		float float_max;		/*	*/
	};
}

#endif