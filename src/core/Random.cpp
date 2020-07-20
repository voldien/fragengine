#include"Core/Random.h"
#include<pcg_basic.h>

using namespace fragview;

void Random::setSeed(unsigned long long seed){

}

unsigned int Random::rand(void){
	return pcg32_random();
}

float Random::randfNormalize(void){

}

float Random::randf(void) const{

}