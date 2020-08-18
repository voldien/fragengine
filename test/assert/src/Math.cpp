#include<gtest/gtest.h>
#include<Core/Math.h>

using namespace fragcore;

TEST(Math, MathFunctions)
{
	/*	Clamp.	*/
	ASSERT_EQ(Math::clamp(5, 3, 4), 4);
	ASSERT_EQ(Math::clamp(1, 3, 4), 3);

	/*	min.	*/
	ASSERT_EQ(Math::min(5, 3), 3);
	ASSERT_EQ(Math::min(1, 3), 1);

	/*	max.	*/
	ASSERT_EQ(Math::max(5, 3), 5);
	ASSERT_EQ(Math::max(1, 3), 3);

	/*	Mod.	*/

	/*	Power of 2.	*/
	for (int i = 0; i < 32; i++)
		ASSERT_TRUE(Math::IsPowerOfTwo(1 << i));
	for (int i = 0; i < 31; i++){
		unsigned int p2 = Math::NextPowerOfTwo(1 << i);
		ASSERT_TRUE(Math::IsPowerOfTwo(p2));
		ASSERT_TRUE(p2 == (1 << (i + 1)));
	}
}

TEST(Math, Distrubtion){

	/*	Gamma space */
	const int sample_space = 2048;
	float pre_gamma = 0.0f;
	for (int i = 0; i < sample_space; i++)
	{
		float linear = (float)i / (float)sample_space;
		float gamma = Math::gammaCorrection(linear, 2.2f);
		ASSERT_TRUE(gamma > pre_gamma);
		pre_gamma = gamma;
	}

	/*	Guassian distribution.	*/
}