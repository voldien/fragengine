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

const int XMAX = 16;
const int YMAX = 16;
static const int octave = 6;
static float amplitude = 2.0f;
static const float persistance = 0.50f;
static const float gradiant[][2] = {
	{1.0f, 1.0f},
	{-1.0f, 1.0f},
	{1.0f, -1.0f},
	{-1.0f, -1.0f}};
static uint8_t *grad = NULL;
const int numGradVectors = sizeof(gradiant) / sizeof(gradiant[0]);

uint8_t *generateGradient(int width, int height)
{
	int x, y;

	/*  Allocate.   */
	uint8_t *gradient = (uint8_t *)malloc(width * height * 2 * sizeof(uint8_t));
	assert(gradient);

	srand(time(NULL));

	/*	Create indices map.	*/
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			gradient[y * height + x] = rand() % numGradVectors;
		}
	}
	return gradient;
}

static float dotGridGradient(int ix, int iy,
							 float x,
							 float y)
{

	float dx = x - (float)ix;
	float dy = y - (float)iy;

	/*	Wrap index.	*/
	iy %= YMAX;
	ix %= XMAX;

	/*	Fetch gradient vector.	*/
	assert(iy >= 0 && ix >= 0);
	const float v0 = gradiant[grad[(iy * YMAX * 2) + (2 * ix)]][0];
	const float v1 = gradiant[grad[(iy * YMAX * 2) + (2 * ix)]][1];

	/*	*/
	return (dx * v0 + dy * v1);
}

static float dotGridGradient3D(int ix, int iy, int iz, float x, float y, float z)
{
	return 0;
}

static float perlinDifferentail2D(float x, float y)
{
	/* Determine grid cell coordinates	*/
	int x0 = (int)floor(x);
	int x1 = (x0 + 1);
	int y0 = (int)floor(y);
	int y1 = (y0 + 1);

	// Determine interpolation weights
	// Could also use higher order polynomial/s-curve here
	float sx = x - (float)x0;
	float sy = y - (float)y0;

	/*	Interpolate between grid point gradients	*/
	float n0, n1, n2, n3, ix0, ix1;

	/*	Top.	*/
	n0 = dotGridGradient(x0, y0, x, y);
	n1 = dotGridGradient(x1, y0, x, y);
	ix0 = Math::lerp(n0, n1, sx);

	/*	Bottom.	*/
	n0 = dotGridGradient(x0, y1, x, y);
	n1 = dotGridGradient(x1, y1, x, y);
	ix1 = Math::lerp(n0, n1, sx);

	/*	d/dt [lerp(lerp(a,b,t),lerp(c,d,t),t)]*/
	/*	The Bézier curve deriviate won't really work, because the lines are not connected.	*/
	return sx * (-2.0 * n2 + 2.0f * n3 - 2.0 * n1 + 2.0f * n0) + n2 - n0 * 3.0f * n0;
}

static float perlin(float x, float y)
{

	/* Determine grid cell coordinates	*/
	int x0 = (int)floor(x);
	int x1 = (x0 + 1);
	int y0 = (int)floor(y);
	int y1 = (y0 + 1);

	// Determine interpolation weights
	// Could also use higher order polynomial/s-curve here
	float sx = x - (float)x0;
	float sy = y - (float)y0;

	/*	Interpolate between grid point gradients	*/
	float n0, n1, ix0, ix1;

	/*	Top.	*/
	n0 = dotGridGradient(x0, y0, x, y);
	n1 = dotGridGradient(x1, y0, x, y);
	ix0 = Math::lerp(n0, n1, sx);

	/*	Bottom.	*/
	n0 = dotGridGradient(x0, y1, x, y);
	n1 = dotGridGradient(x1, y1, x, y);
	ix1 = Math::lerp(n0, n1, sx);

	return Math::lerp(ix0, ix1, sy);
}

float Math::PerlinNoise(float x, float y)
{
	if (ctx == NULL)
		open_simplex_noise(0, &ctx);
	
	return open_simplex_noise2(ctx, x, y);

	int z;
	float totalAmplitude = 0;
	float noise = 0;

	/*  Generate gradiant.  */
	if (grad == NULL)
		grad = generateGradient(XMAX, YMAX);

	for (z = 0; z < octave; z++)
	{
		amplitude *= persistance;
		totalAmplitude += amplitude;

		/*	*/
		const unsigned int samplePeriod = (1 << z);
		const float sampleFrquency = 1.0f / (float)samplePeriod;

		/*	*/
		const float xpos = ((float)x / (float)samplePeriod) * sampleFrquency;
		const float ypos = ((float)y / (float)samplePeriod) * sampleFrquency;
		noise += perlin(x, y) * totalAmplitude;
	}

	return noise;
}

float Math::PerlinNoiseDifferential(float x, float y)
{

	int z;
	float totalAmplitude = 0;
	float noise = 0;

	/*  Generate gradiant.  */
	if (grad == NULL)
		grad = generateGradient(XMAX, YMAX);

	for (z = 0; z < octave; z++)
	{
		amplitude *= persistance;
		totalAmplitude += amplitude;

		/*	*/
		const unsigned int samplePeriod = (1 << z);
		const float sampleFrquency = 1.0f / (float)samplePeriod;

		/*	*/
		const float xpos = ((float)x / (float)samplePeriod) * sampleFrquency;
		const float ypos = ((float)y / (float)samplePeriod) * sampleFrquency;
		noise += perlinDifferentail2D(x, y) * totalAmplitude;
	}

	return noise;
}

float Math::PerlinNoise(float x, float y, float z)
{
	if (ctx == NULL)
		open_simplex_noise(0, &ctx);
	
	return open_simplex_noise3(ctx, x, y, z);
	float totalAmplitude = 0;
	float noise = 0;

	/*  Generate gradiant.  */
	if (grad == NULL)
		grad = generateGradient(XMAX, YMAX);

	for (int i = 0; i < octave; i++)
	{
		amplitude *= persistance;
		totalAmplitude += amplitude;

		/*	*/
		const unsigned int samplePeriod = (1 << i);
		const float sampleFrquency = 1.0f / (float)samplePeriod;

		/*	*/
		const float xpos = ((float)x / (float)samplePeriod) * sampleFrquency;
		const float ypos = ((float)y / (float)samplePeriod) * sampleFrquency;
		noise += perlin(x, y) * totalAmplitude;
	}
}

float Math::PerlinNoiseDifferential(float x, float y, float z)
{
	float totalAmplitude = 0;
	float noise = 0;

	/*  Generate gradiant.  */
	if (grad == NULL)
		grad = generateGradient(XMAX, YMAX);

	for (int i = 0; i < octave; i++)
	{
		amplitude *= persistance;
		totalAmplitude += amplitude;

		/*	*/
		const unsigned int samplePeriod = (1 << i);
		const float sampleFrquency = 1.0f / (float)samplePeriod;

		/*	*/
		const float xpos = ((float)x / (float)samplePeriod) * sampleFrquency;
		const float ypos = ((float)y / (float)samplePeriod) * sampleFrquency;
		noise += perlinDifferentail2D(x, y) * totalAmplitude;
	}

	return noise;
}