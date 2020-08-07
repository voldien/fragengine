#include "Core/Math.h"
#include <hpm/hpm.h>
#include <float.h>
#include <math.h>
#include<open-simplex-noise.h>
using namespace fragview;

const float Math::Epsilon = FLT_EPSILON;
const float Math::PI = HPM_PI;
const float Math::Infinite = 0;
const float Math::Deg2Rad = Math::PI / 180.0f;
const float Math::Rad2Deg = 180 / Math::PI;
const float Math::NegativeInfinity = 0;
static struct osn_context *ctx = NULL;


static void
guassian1Df(float *guassian, int width, double theta)
{
	
}

static void guassian2Df(float *guassian, int height, float theta)
{

}

float Math::linearToGammaSpace(float linear)
{
	// 	double corrected = (double)rgbRamp[i] / 65535.0;
	// 	double linear = double(i) * 1.0 / 255u;
	// 	gamma += log(linear) / log(corrected);
	return 0;
}

float Math::GameSpaceToLinear(float gamma, float exp)
{
	return 0;
}

PVColor Math::CorrelatedColorTemperatureToRGB(float kelvin)
{
	float temp = kelvin / 100;

	float red, green, blue;

	if (temp <= 66)
	{

		red = 255;

		green = temp;
		green = 99.4708025861 * log(green) - 161.1195681661;

		if (temp <= 19)
		{

			blue = 0;
		}
		else
		{

			blue = temp - 10;
			blue = 138.5177312231 * log(blue) - 305.0447927307;
		}
	}
	else
	{

		red = temp - 60;
		red = 329.698727446 * pow(red, -0.1332047592);

		green = temp - 60;
		green = 288.1221695283 * pow(green, -0.0755148492);

		blue = 255;
	}

	return PVColor(clamp(red, 0, 255) / 255.0f,
				   clamp(green, 0, 255) / 255.0f,
				   clamp(blue, 0, 255) / 255.0f, 1);
}

float Math::PerlinNoise(const PVVector2 &point){
	return Math::PerlinNoise(point.x(), point.y());
}

float Math::PerlinNoise(float x, float y)
{
	if (unlikely(ctx == NULL))
		open_simplex_noise(0, &ctx);
	return open_simplex_noise2(ctx, x, y);
}

float Math::PerlinNoise(float x, float y, float z)
{
	if (unlikely(ctx == NULL))
		open_simplex_noise(0, &ctx);
	
	return open_simplex_noise3(ctx, x, y, z);
}

float Math::PerlinNoise(const PVVector3 &point)
{
	return Math::PerlinNoise(point.x(), point.y(), point.z());
}