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
#ifndef _FV_SCENE_DEF_H_
#define _FV_SCENE_DEF_H_ 1
//#include"System.h"
//
///**
// *	Contain global scene state.
// */
//typedef struct global_scene_state_t{
//
//	PVMatrix4x4 projection;			/**/
//	PVMatrix4x4 viewMatrix;			/**/
//	PVMatrix4x4 viewProjection;		/**/
//	PVMatrix4x4 viewRotMatrix;		/**/
//	PVColor ambientColor;			/**/
//	PVVector2 resolution;			/**/
//
//	PVVector3 cameraPosition;		/*	*/
//	PVVector3 cameraDir;			/*	*/
//
//	float time;						/*	*/
//	float deltatime;				/*	*/
//	float timescale;				/*	*/
//
//	float cameraNear;				/*	*/
//	float cameraFar;				/*	*/
//	float deltaTime;				/*	*/
//	int numLights;					/*	*/
//	int maxLights;					/*	*/
//	int xpos;						/*	*/
//	int ypos;						/*	*/
//
//	int ambientType;				/*	*/
//	float ambientIntensity;			/*	*/
//
//	float fogStart;					/*	*/
//	float fogEnd;					/*	*/
//	float fogHeight;				/*	*/
//	int fogType;					/*	*/
//	int fogDepthType;
//	float fogDensity;				/*	*/
//	PVColor fogColor;				/*	*/
//	PVVector4 fogplane;				/*	*/
//
//	/*  TODO fix aliasing packaging.*/
//} GlobalSceneState;
//
//typedef struct uniform_light_t{
//	unsigned int numShadows;		/*	*/
//	unsigned int shadow;			/*	*/
//
//	int numDirection;				/*	*/
//	int numSpot;					/*	*/
//	int numPoint;					/*	*/
//	int numShadowDirection;			/*	*/
//	int numShadowSpot;				/*	*/
//	int numShadowPoint;				/*	*/
//
//	/**/
//	PVVector3 direction;
//	PVColor color;
//	PVVector3 position;
//	float angle;
//	/*	*/
//	float intensity;
//	float range;
//	float shadowStrength;
//	float shadowBias;
//	int type;
//
//	/*	*/
//	int shadowIndex;
//} UniformLight;
//
//typedef struct global_scene_light_state_t{
//	std::vector<UniformLight> lights;
//} GlobalSceneLightState;

#endif
