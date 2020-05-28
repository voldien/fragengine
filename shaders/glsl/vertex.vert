/**
    Internal common glsl declaration for the PVEngine.
    Copyright (C) 2017  Valdemar Lindberg

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

//#version 330
/*	Extension used.	*/
#extension GL_ARB_explicit_uniform_location : enable
#extension GL_ARB_uniform_buffer_object : enable
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_enhanced_layouts : enable
#extension GL_ARB_shader_precision : enable

/*	*/
#extension GL_ARB_shader_image_size : enable
#extension GL_ARB_bindless_texture : enable
#extension GL_ARB_explicit_attrib_location : enable
/*	*/
#extension GL_ARB_shading_language_420pack : enable

/*	Check if mobile OpenGL is used.	*/
#ifdef GL_ES
precision mediump float;
precision mediump int;
#endif

/*	Translate fragment location decleration based on what version.	*/
#if defined(GL_ARB_explicit_attrib_location) || GL_ARB_enhanced_layouts == 1
	#define FRAGLOCATION(x, vtype, name) layout(location = x) out vtype name
#elif __VERSION__ == 130
	#define FRAGLOCATION(x, vtype, name) out vtype name
#else
	#define FRAGLOCATION(x) x
#endif

/*	Translate based on glsl version.	*/
#if defined(GL_ARB_explicit_attrib_location) || GL_ARB_enhanced_layouts == 1
	#define ATTRIBUTE_IN(x) layout(location = x) in
	#define ATTRIBUTE_OUT(x) layout(location = x) out
#else
	#define ATTRIBUTE_IN(x) attribute
	#define ATTRIBUTE_OUT(x) attribute
#endif

#if __VERSION__ >= 450 ||  || GL_ARB_enhanced_layouts == 1
    #define UNIFORMBUFFER(x) layout(std140, binding = x, shared)
#elif __VERSION__ > 130 || defined(GL_ARB_uniform_buffer_object)
    #define UNIFORMBUFFER(x) layout(std140, shared)
#else
    #define UNIFORMBUFFER(x)
#endif

/*  Storage buffer. */
#if __VERSION__ >= 450 || defined(GL_ARB_enhanced_layouts)
    #define STORAGEBUFFER(x) layout(std140, binding = x, shared)
#elif __VERSION__ > 130 || defined(GL_ARB_uniform_buffer_object)
    #define STORAGEBUFFER(x) layout(std140, shared)
#else
    #define STORAGEBUFFER(x)
#endif

ATTRIBUTE_IN(0) vec3 vertex;	/*	*/
ATTRIBUTE_IN(1) vec2 uv;        /*	*/
ATTRIBUTE_IN(2) vec3 normal;    /*	*/
ATTRIBUTE_IN(3) vec3 tangent;	/*	*/

///*  Sprite textures.    */
//#ifdef gl_MaxTextureImageUnits
//uniform sampler2D textures[gl_MaxTextureImageUnits];
//#else
//uniform sampler2D textures[16];
//#endif

layout(std140, binding=2) uniform matrixBuffer {
    uniform mat4 MVP;
    uniform mat4 Model;
};

/*  */
layout(location = 0) out vec2 vUV;
layout(location = 1) out vec3 vNormal;
layout(location = 2) out vec3 vTangent;
layout(location = 3) out vec3 vVertex;
layout(location = 4) out vec3 vWVVertex;

out gl_PerVertex
{
	vec4 gl_Position;
};

void main(void){

	gl_Position = MVP * vec4(vertex, 1.0);
	vVertex = (Model * vec4(vertex, 0.0)).xyz;
	//vWVVertex = (getViewMatrix() * Model * vec4(vertex, 1.0)).xyz;

	vUV = uv;
	vNormal = (Model * vec4(normal, 0.0)).xyz;
	vTangent = (Model * vec4(tangent, 0.0)).xyz;
}

