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

/*	Extension used.*/
#extension GL_ARB_explicit_uniform_location : enable
#extension GL_ARB_uniform_buffer_object : enable
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_enhanced_layouts : enable

#extension GL_ARB_shader_image_size : enable
#extension GL_ARB_bindless_texture : enable
#extension GL_ARB_explicit_attrib_location : enable

#extension GL_ARB_shading_language_420pack : enable

#extension GL_ARB_draw_instanced : enable
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shader_texture_lod : enable
#extension GL_ARB_shader_storage_buffer_object : enable
#extension GL_ARB_gpu_shader_int64 : enable
#extension GL_ARB_explicit_attrib_location : enable
#extension GL_ARB_shading_language_include : enable
#extension GL_ARB_conservative_depth : enable
#extension GL_ARB_shader_viewport_layer_array : enable
#extension GL_ARB_gpu_shader5 : enable
#extension GL_ARB_fragment_coord_conventions : enable
#extension GL_ARB_ES3_1_compatibility : enable
#extension GL_ARB_shader_draw_parameters : enable
#extension GL_ARB_fragment_layer_viewport : enable
#extension GL_ARB_texture_cube_map_array : enable
#extension GL_ARB_cull_distance : enable
#extension GL_ARB_bindless_texture : enable
#extension GL_ARB_vertex_attrib_64bit : enable
#extension GL_ARB_geometry_shader4 : enable
#extension GL_ARB_gpu_shader_fp64 : enable
#extension GL_ARB_shader_precision : enable
#extension GL_ARB_compute_variable_group_size : enable
#extension GL_ARB_texture_multisample : enable
#extension GL_ARB_shader_subroutine : enable
#extension GL_ARB_uniform_buffer_object : enable
#extension GL_ARB_ES3_2_compatibility : enable
#extension GL_ARB_sparse_texture_clamp : enable
#extension GL_ARB_derivative_control : enable
#extension GL_ARB_shader_clock : enable
#extension GL_ARB_shader_group_vote : enable
#extension GL_ARB_shader_atomic_counters : enable
#extension GL_ARB_shader_ballot : enable
#extension GL_ARB_sparse_texture2 : enable
#extension GL_ARB_fragment_shader_interlock : enable
#extension GL_ARB_post_depth_coverage : enable
#extension GL_ARB_shading_language_packing : enable
#extension GL_ARB_explicit_uniform_location : enable
#extension GL_ARB_tessellation_shader : enable
#extension GL_ARB_enhanced_layouts : enable
#extension GL_ARB_shader_image_load_store : enable
#extension GL_EXT_tessellation_shader : enable
#extension GL_EXT_bindable_uniform : enable
#extension GL_INTEL_conservative_rasterization : enable
#extension GL_EXT_shader_framebuffer_fetch : enable
#extension GL_EXT_texture_shadow_lod : enable
#extension GL_EXT_clip_distance : enable
#extension GL_EXT_clip_cull_distance : enable
#extension GL_NV_image_formats : enable
#extension GL_INTEL_fragment_shader_ordering : enable
#extension GL_EXT_post_depth_coverage : enable
#extension GL_NV_bindless_texture : enable

/*	Check if mobile OpenGL is used.	*/
#if defined(GL_ES) && defined(GL_ARB_shader_precision)
precision mediump float;
precision mediump int;
#endif

/*	Translate fragment location decleration based on what version.	*/
#if __VERSION__ > 130 || defined(GL_ARB_separate_shader_objects)
	#define FRAGLOCATION(x, vtype, name) layout(location = x) out vtype name
#elif __VERSION__ == 130
	#define FRAGLOCATION(x, vtype, name) out vtype name
#else
	#define FRAGLOCATION(x) 
#endif

/*	Translate based on glsl version.	*/
#if __VERSION__ > 130 || defined(GL_ARB_separate_shader_objects)
	#define ATTRIBUTE_IN(x) layout(location = x) in 
	#define ATTRIBUTE_OUT(x) layout(location = x) out
#else
	#define ATTRIBUTE_IN(x) attribute
	#define ATTRIBUTE_OUT(x) attribute
#endif

#if __VERSION__ >= 450 || defined(GL_ARB_enhanced_layouts)
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


//in
//in
//in
//in
//in
//in
//in
//in
//in
//in
//in
//in
//vec4 gl_FragCoord;
//bool gl_FrontFacing;
//float gl_ClipDistance[];
//float gl_CullDistance[];
//vec2 gl_PointCoord;
//int gl_PrimitiveID;
//int gl_SampleID;
//vec2 gl_SamplePosition;
//int gl_SampleMaskIn[];
//int gl_Layer;
//int gl_ViewportIndex;
//bool gl_HelperInvocation;
//out float gl_FragDepth;
//out int gl_SampleMask[];

//const
//const
//const
//const
//const
//const
//const
//const
//const
//const
//int
//int
//int
//int
//int
//int
//int
//int
//int
//int
//gl_MaxVertexAttribs = 16;
//gl_MaxVertexUniformVectors = 256;
//gl_MaxVertexUniformComponents = 1024;
//gl_MaxVertexOutputComponents = 64;
//gl_MaxVaryingComponents = 60;
//gl_MaxVaryingVectors = 15;
//gl_MaxVertexTextureImageUnits = 16;
//gl_MaxVertexImageUniforms = 0;
//gl_MaxVertexAtomicCounters = 0;
//gl_MaxVertexAtomicCounterBuffers = 0;
//const int gl_MaxTessPatchComponents = 120;
//const int gl_MaxPatchVertices = 32;
//const int gl_MaxTessGenLevel = 64;
//const
//const
//const
//const
//const
//const
//const
//const int
//int
//int
//int
//int
//int
//int
//int gl_MaxTessControlInputComponents = 128;
//gl_MaxTessControlOutputComponents = 128;
//gl_MaxTessControlTextureImageUnits = 16;
//gl_MaxTessControlUniformComponents = 1024;
//gl_MaxTessControlTotalOutputComponents = 4096;
//gl_MaxTessControlImageUniforms = 0;
//gl_MaxTessControlAtomicCounters = 0;
//gl_MaxTessControlAtomicCounterBuffers = 0;
//const
//const
//const
//const
//const
//const
//const int
//int
//int
//int
//int
//int
//int gl_MaxTessEvaluationInputComponents = 128;
//gl_MaxTessEvaluationOutputComponents = 128;
//gl_MaxTessEvaluationTextureImageUnits = 16;
//gl_MaxTessEvaluationUniformComponents = 1024;
//gl_MaxTessEvaluationImageUniforms = 0;
//gl_MaxTessEvaluationAtomicCounters = 0;
//gl_MaxTessEvaluationAtomicCounterBuffers = 0;
//const
//const
//const
//const
//const
//const
//const
//const
//const
//const int
//int
//int
//int
//int
//int
//int
//int
//int
//int gl_MaxGeometryInputComponents = 64;
//gl_MaxGeometryOutputComponents = 128;
//gl_MaxGeometryImageUniforms = 0;
//gl_MaxGeometryTextureImageUnits = 16;
//gl_MaxGeometryOutputVertices = 256;
//gl_MaxGeometryTotalOutputComponents = 1024;
//gl_MaxGeometryUniformComponents = 1024;
//gl_MaxGeometryVaryingComponents = 64;
//gl_MaxGeometryAtomicCounters = 0;
//gl_MaxGeometryAtomicCounterBuffers = 0;
//146
//// deprecatedconst
//const
//const
//const
//const
//const int
//int
//int
//int
//int
//int
//gl_MaxFragmentImageUniforms = 8;
//gl_MaxFragmentInputComponents = 128;
//gl_MaxFragmentUniformVectors = 256;
//gl_MaxFragmentUniformComponents = 1024;
//gl_MaxFragmentAtomicCounters = 8;
//gl_MaxFragmentAtomicCounterBuffers = 1;
//const
//const
//const
//const
//const
//const
//const
//const
//const
//const int
//int
//int
//int
//int
//int
//int
//int
//int
//int
//gl_MaxDrawBuffers = 8;
//gl_MaxTextureImageUnits = 16;
//gl_MinProgramTexelOffset = -8;
//gl_MaxProgramTexelOffset = 7;
//gl_MaxImageUnits = 8;
//gl_MaxSamples = 4;
//gl_MaxImageSamples = 0;
//gl_MaxClipDistances = 8;
//gl_MaxCullDistances = 8;
//gl_MaxViewports = 16;
//const
//const
//const
//const
//const
//const
//const int gl_MaxComputeImageUniforms = 8;
//ivec3 gl_MaxComputeWorkGroupCount = { 65535, 65535, 65535 };
//ivec3 gl_MaxComputeWorkGroupSize = { 1024, 1024, 64 };
//int gl_MaxComputeUniformComponents = 1024;
//int gl_MaxComputeTextureImageUnits = 16;
//int gl_MaxComputeAtomicCounters = 8;
//int gl_MaxComputeAtomicCounterBuffers = 8;
//const
//const
//const
//const
//const
//const
//const
//const
//const int
//int
//int
//int
//int
//int
//int
//int
//int
//gl_MaxCombinedTextureImageUnits = 96;
//gl_MaxCombinedImageUniforms = 48;
//gl_MaxCombinedImageUnitsAndFragmentOutputs = 8;
//gl_MaxCombinedShaderOutputResources = 16;
//gl_MaxCombinedAtomicCounters = 8;
//gl_MaxCombinedAtomicCounterBuffers = 1;
//gl_MaxCombinedClipAndCullDistances = 8;
//gl_MaxAtomicCounterBindings = 1;
//gl_MaxAtomicCounterBufferSize = 32;
//// deprecated
//const int gl_MaxTransformFeedbackBuffers = 4;
//const int gl_MaxTransformFeedbackInterleavedComponents = 64;




/*	Translate based on glsl version.	*/
#if __VERSION__ > 120
	#define OUT out
	#define SMOOTH_OUT smooth out
	#define FLAT_OUT flat out
	#define IN in
	#define SMOOTH_IN smooth in
	#define FLAT_IN flat in
#else
	#define OUT varying
	#define SMOOTH_OUT smooth varying
	#define FLAT_IN flat varying
	#define IN varying
	#define SMOOTH_IN smooth varying
	#define FLAT_IN flat varying
#endif

/**
 *	Responsible for common 
 *	global variable shared across
 *	all shaders.
 */
struct global_uniform {

	mat4 projection;
	mat4 viewMatrix;
	mat4 viewProjection;
	mat4 viewRotMatrix;
	vec4 ambientColor;
	vec2 resolution;
	/*	*/
	vec4 cameraPosition;
	vec4 cameraDir;
	/*	*/	
	float time;
	float deltatime;
	float timescale;
	/*	*/
	float cameraNear;
	float cameraFar;
	float deltaTime;
	int numLights;
	int maxLights;
	int xpos;
	int ypos;
	
	int ambientType;
	float ambientIntensity;

	/*	*/
	float fogStart;
	float fogEnd;
	float fogHeight;
	int fogType;
	int fogDepthType;
	float fogDensity;
	vec4 fogColor;
	vec4 fogplane;
};

/**
 *	Shared uniform buffer.
 */
UNIFORMBUFFER(0) uniform globaluniform {
	global_uniform global;
};


#define eAmbientConstant    0x1     /**/
#define eAmbientImageBased  0x2     /**/
uniform samplerCube ambientCube;    /*	Image based ambient lightning*/

/**
 *	Get ambient color.
 */
vec4 getAmbientColor(void){
	return global.ambientColor;
}

/**
 *	Get ambient cubemap color.
 */
vec4 getAmbientCubeMapColor(const in vec3 inputNormal){
	return texture(ambientCube, inputNormal) * getAmbientColor() * vec4(global.ambientIntensity);
}

/**
 *	Get ambient constant color.
 */
vec4 getAmbientConstantColor(const in vec3 inputNormal){
	return getAmbientColor();
}

/**
 *	Compute ambient color.
 */
vec4 getAmbient(const in vec3 inputNormal){
	switch(global.ambientType){
		case eAmbientConstant:
			return getAmbientConstantColor(inputNormal);
		//case eAmbientImageBased:
		//	return getAmbientCubeMapColor(inputNormal);
		default:
			return vec4(0.0);
	}
}

/**
 *	Get current time in high precision in 
 *	seconds.
 */
float getTime(void){
        return global.time;
}

/**
 *	Get delta time since previous frame.
 */
float getDeltaTime(void){
        return global.deltaTime;
}

/**
 * Get screen resolution in pixels.
 */
vec2 getScreen(void){
        return global.resolution;
}

/**
 *	Get UV coordination of current pixel in
 *	fragment shader.
 */
vec2 getScreenUV(void){
#ifdef PV_FRAGMENT
       return gl_FragCoord.xy / getScreen();
#else
        return vec2(0); 
#endif
}

/**
 *	Get camera position in model space.
 */
vec3 getCameraPosition(void){
        return global.cameraPosition.xyz;
}

/**
 *	Get camera orientation direction.
 */
vec3 getCameraDirection(void){
        return global.cameraDir.xyz;
}

/**
 *	Get camera near frustum.
 */
float getCameraNear(void){
        return global.cameraNear;
}

/**
 *	Get camera far frustum.
 */
float getCameraFar(void){
        return global.cameraFar;
}

/**
 *	Get current view matrix.
 */
mat4 getViewMatrix(void){
        return global.viewMatrix;
}

/**
 *	Get projection matrix.
 */
mat4 getProjectionMatrix(void){
        return global.projection;
}

/**
 *	Get current project view matrix.
 */
mat4 getViewProjectionMatrix(void){
        return global.viewProjection;
}

/**
 *	Get view rotation matrix.
 *	Used with skybox.
 */
mat4 getViewRotationMatrix(void){
	return global.viewRotMatrix;
}

/**
 * Fog types.
 */
#define FOGNONE         0x0	/*	*/
#define FOGLINEAR       0x1	/*	Get linear fog.	*/
#define FOGEXP          0x2	/*	*/
#define FOGEXP2         0x3	/*	*/
#define FOGHEIGHT       0x4	/*	*/

/**
 *	Compute fog intensity factor.
 */
vec2 getFogFactor(const vec3 viewVertex) {

    int fogtype = global.fogType;
    int fogDepthType = global.fogDepthType;
    float ext = 1.0;
    float insc = 1.0;

	/*	Prevent unnecessary computation.	*/
	if(fogtype == 0)
		return vec2(1.0,0);

    const float near = getCameraNear();
    const float far = getCameraFar();

    /*  Compute start and end.  */
    const float endFog = global.fogEnd;
    const float startFog = global.fogStart;
    const float densityFog =  global.fogDensity;

    /*      z normalized.   */
    #ifdef PV_FRAGMENT
    float dist;
    if(fogDepthType == 1)
        dist = length(viewVertex);
    else
        dist = abs(viewVertex);
        
    #else
    const float dist = 1.0;
    #endif
    
    switch(fogtype){
    case 1:
        ext = clamp( (endFog - dist) / (endFog - startFog), 0.0, 1.0 );
        break;
    case 2:
        ext = clamp( exp( -(densityFog * dist) ), 0.0, 1.0);
        break;
    case 3:
            ext = clamp( exp( - ( densityFog * dist * densityFog * dist) ) , 0.0, 1.0);
            break;
    case 4:
        float be = (getCameraPosition().y - viewVertex.y) * 0.004;//0.004 is just a factor; change it if you want
        float bi = (getCameraPosition().y - viewVertex.y) * 0.001;//0.001 is just a factor; change it if you want
        ext = exp(-dist * be);
        insc = exp(-dist * bi);
        break;
    default:
        break;
    }

    return vec2(ext, insc);
}

/**
 *	Compute fog color and blend it with current 
 *	init color.
 */
vec4 internalFog(const in vec3 viewVertex, const in vec4 initColor){
    vec4 fogColor = global.fogColor;
    const vec2 factor = getFogFactor(viewVertex);

    /*  Compute final color.    */
    if(global.fogType == FOGHEIGHT)
        return initColor * factor.x + fogColor * (1 - factor.y);
    else
        return mix(fogColor, initColor, factor.x);
}

/**
 * Default texture position.
 */
#define TEXTURE_DIFFUSE 0
#define TEXTURE_SPECULAR  1
#define TEXTURE_AMBIENT  2
#define TEXTURE_EMISSIVE  3
#define TEXTURE_HEIGHT  4
#define TEXTURE_NORMAL  5


//
//  /** The texture is combined with the result of the diffuse
//     *  lighting equation.
//     */
//    aiTextureType_DIFFUSE = 0x1,
//
//    /** The texture is combined with the result of the specular
//     *  lighting equation.
//     */
//    aiTextureType_SPECULAR = 0x2,
//
//    /** The texture is combined with the result of the ambient
//     *  lighting equation.
//     */
//    aiTextureType_AMBIENT = 0x3,
//
//    /** The texture is added to the result of the lighting
//     *  calculation. It isn't influenced by incoming light.
//     */
//    aiTextureType_EMISSIVE = 0x4,
//
//    /** The texture is a height map.
//     *
//     *  By convention, higher gray-scale values stand for
//     *  higher elevations from the base height.
//     */
//    aiTextureType_HEIGHT = 0x5,
//
//    /** The texture is a (tangent space) normal-map.
//     *
//     *  Again, there are several conventions for tangent-space
//     *  normal maps. Assimp does (intentionally) not
//     *  distinguish here.
//     */
//    aiTextureType_NORMALS = 0x6,
//
//    /** The texture defines the glossiness of the material.
//     *
//     *  The glossiness is in fact the exponent of the specular
//     *  (phong) lighting equation. Usually there is a conversion
//     *  function defined to map the linear color values in the
//     *  texture to a suitable exponent. Have fun.
//    */
//    aiTextureType_SHININESS = 0x7,
//
//    /** The texture defines per-pixel opacity.
//     *
//     *  Usually 'white' means opaque and 'black' means
//     *  'transparency'. Or quite the opposite. Have fun.
//    */
//    aiTextureType_OPACITY = 0x8,
//
//    /** Displacement texture
//     *
//     *  The exact purpose and format is application-dependent.
//     *  Higher color values stand for higher vertex displacements.
//    */
//    aiTextureType_DISPLACEMENT = 0x9,
//
//    /** Lightmap texture (aka Ambient Occlusion)
//     *
//     *  Both 'Lightmaps' and dedicated 'ambient occlusion maps' are
//     *  covered by this material property. The texture contains a
//     *  scaling value for the final color value of a pixel. Its
//     *  intensity is not affected by incoming light.
//    */
//    aiTextureType_LIGHTMAP = 0xA,
//
//    /** Reflection texture
//     *
//     * Contains the color of a perfect mirror reflection.
//     * Rarely used, almost never for real-time applications.
//    */
//    aiTextureType_REFLECTION = 0xB,


layout(binding = 0) uniform sampler2D diffuseTexture;
layout(binding = 1) uniform sampler2D specularTexture;
layout(binding = TEXTURE_NORMAL) uniform sampler2D normalTexture;

struct Texture2D {
	int index;
	vec2 scale;     /*  Texture scale.  */
	vec2 offset;    /*  Texture Offset. */
};

/**
 *
 */
struct Texture3D {
	sampler3D tex;
	vec3 scale;
	vec3 offset;
};

vec4 getGlobalTextureSample(const in int index, const in vec2 uv){

//#if __VERSION__ < 410
	switch(index) {
		case 0:
		    return texture(diffuseTexture, uv);
		case 1:
		    return texture(specularTexture, uv);
//		case 2:
//		    return texture(textures[2], uv);
//		case 3:
//		    return texture(textures[3], uv);
//		case 4:
//		    return texture(textures[4], uv);
		case 5:
		    return texture(normalTexture, uv);
//		case 6:
//		    return texture(textures[6], uv);
//		case 7:
//		    return texture(textures[7], uv);
//		case 8:
//		    return texture(textures[8], uv);
//		case 9:
//		    return texture(textures[9], uv);
//		case 10:
//		    return texture(textures[10], uv);
//		case 11:
//		    return texture(textures[11], uv);
//		case 12:
//		    return texture(textures[12], uv);
//		case 13:
//		    return texture(textures[13], uv);
//		case 14:
//		    return texture(textures[14], uv);
//		case 15:
//		    return texture(textures[15], uv);
//		case 16:
//		    return texture(textures[16], uv);
//		case 17:
//		    return texture(textures[17], uv);
//		case 18:
//		    return texture(textures[18], uv);
//		case 19:
//		    return texture(textures[19], uv);
//		case 20:
//		    return texture(textures[20], uv);
//		case 21:
//		    return texture(textures[21], uv);
//		case 22:
//		    return texture(textures[22], uv);
//		case 23:
//		    return texture(textures[23], uv);
//		case 24:
//		    return texture(textures[24], uv);
//		case 25:
//		    return texture(textures[25], uv);
//		case 26:
//		    return texture(textures[26], uv);
//		case 27:
//		    return texture(textures[27], uv);
//		case 28:
//		    return texture(textures[28], uv);
//		case 29:
//		    return texture(textures[29], uv);
//		case 30:
//		    return texture(textures[30], uv);
/*
		case 31:
		    return texture(textures[31], uv);
		case 32:
		    return texture(textures[32], uv);
		case 33:
		    return texture(textures[33], uv);*/
		default:
		    return vec4(0.0);
	}
//#else
//    //TODO find extension for this feature
//	return texture2D(textures[index], uv);
//#endif
}


/*
 *
 */
vec4 getTextureSample(const in Texture2D tex, const in vec2 uv){
	return getGlobalTextureSample(tex.index, uv * tex.scale + tex.offset).rgba;
}

/*
 *
 */
vec4 getTextureSample(const in Texture3D tex, const in vec3 uv){
	return vec4(1.0);//texture(tex.tex, uv * tex.scale).rgba;
}

//#line 0


#ifndef E
	#define E 2.7182818284F
#endif

#ifndef PI
	#define PI 3.14159265
#endif

#ifndef PI2
	#define PI2 6.2831853
#endif

/**
 *
 */
float calculateAttenuation(const in float constAttenuation, const in float linearAttenuation, const in float quadraticAttenuation, const in float distance){
	return (1.0f / (constAttenuation + (linearAttenuation * distance) + (quadraticAttenuation * distance * distance) ) );
}

/**
 *
 */
float calculateAttenuationEx(const in float distance, const in float range){
	float denom = (distance / range) + 0.05 ;
	float attenuation = 1.0 / (denom * denom);
	attenuation = (attenuation - 0.05) / (1.0 - 0.05);
	return max(attenuation,0);
}


/**
 *
 */
mat4 quadToMat4(vec4 quad){
	return mat4(0.0);
}

/**
 *
 */
mat4 scaleToMat4(const in vec3 scale){
	return mat4(1.0);
}

/**
 *
 */
mat4 posToMat4(const in vec4 pos){
	return mat4( vec4(1.0,0.0,0.0,pos.x),
	 			 vec4(0.0,1.0,0.0,pos.y),
	  			 vec4(0.0,0.0,1.0,pos.z),
	   			 vec4(0.0,0.0,0.0,1.0) );
/*
	return mat4( vec4(1.0,0.0,0.0,0),
	 			 vec4(0.0,1.0,0.0,0),
	  			 vec4(0.0,0.0,1.0,0),
	   			 vec4(pos.x,pos.y,pos.z,1.0  ) );
*/
}



/**
 *
 */
float getAnitShadowVSM(const in sampler2D depthTexture, const in vec4 s){
	return 0.0;
}





























//
//
//struct light_index{
//	ivec4 shadowLight[32];
//	ivec4 shadowDirectionLight[32];
//	ivec4 shadowSpotLight[32];
//	ivec4 shadowPointLight[32];
//	ivec4 direction[256];
//	ivec4 pointLight[256];
//	ivec4 spotLight[256];
//};
//
//
//struct light_shadow{
//	mat4 shadowMatrix;
//};
//
struct list_item{
	vec4 direction;
	vec4 color;
	vec4 position;
	float angle;
	float intensity;
	float range;
	float shadowStrength;
	float shadowBias;
	int type;
	int shadowIndex;

};
//
//
///*	*/
//#define eLightDisable     0x2
//#define ePointLight       0x4
//#define eSpotLight        0x8
//#define eDirectionLight   0x10
//
//
UNIFORMBUFFER(1) uniform lightuniform {
	list_item light[1];
};


//
//
//layout(std140, shared) uniform shadowstructure{
//	light_shadow lightShadow[64];
//};
//
//layout( std140, shared) uniform lightIndices{
//	light_index lightIndex;
//};
//
//
//
//int getShadowDirectionIndex(const in int index){
//	return lightIndex.shadowDirectionLight[index / 4][index % 4];
//}
//int getShadowPointIndex(const in int index){
//	return lightIndex.shadowPointLight[index / 4][index % 4];
//}
//int getShadowSpotIndex(const in int index){
//	return lightIndex.shadowSpotLight[index / 4][index % 4];
//}
//
//
//int getDirectionIndex(const in int index){
//	return lightIndex.direction[index / 4][index % 4];
//}
//int getPointIndex(const in int index){
//	return lightIndex.pointLight[index / 4][index % 4];
//}
//int getSpotIndex(const in int index){
//	return lightIndex.spotLight[index / 4][index % 4];
//}
//
//
//float getLightContributionFactor(const in list_item light, in vec3 normalInput){
//	float contribution = max(0.0, dot(-normalInput, light.direction.xyz) );
//	return contribution;
//}
//
//
//float getSpotLightContributionFactor(const in list_item light, const in vec3 normalInput, const in vec3 vertexInput){
//	vec3 deltaSpace = (light.position.xyz - vertexInput);	//TODO resolve this later in the!
//	float SpotFactor = dot( normalize(deltaSpace), -normalize(light.direction.xyz) );
//	float SpotEffect;
//	if(SpotFactor > light.angle ){
//		float dist = length(deltaSpace);
//		float attenuation = clamp(1.0 - (dist*dist)/(light.range*light.range), 0.0, 1.0);
//		float contribution = max(0.0, dot(normalInput, normalize(deltaSpace))) * SpotFactor;
//		SpotEffect = 1.0;//smoothstep(0.1 , 0.0f, 1.0f - SpotFactor);
//		return contribution * SpotEffect * attenuation;
//	}
//	return 0.0f;
//}
//
//vec4 getDirectionLightColor(const in list_item light, const in vec3 normalInput){
//	float contribution = getLightContributionFactor(light, normalInput);
//	return (contribution * light.color * light.intensity);
//}
//
//vec4 getPointLightColor(const in list_item light, const in vec3 normalInput, const in vec3 vertexInput){
//	vec3 deltaSpace = (light.position.xyz - vertexInput);
//	float dist = length(deltaSpace);
//	float contribution = max(0.0, dot(normalInput, normalize(deltaSpace) ) ) ;
//	float attenuation = clamp(1.0 - (dist*dist)/(light.range*light.range), 0.0, 1.0);
//	attenuation *= attenuation;
//	return light.color * contribution  * attenuation * light.intensity;
//}
//
//float getPointLightFactor(const in list_item light, const in vec3 normalInput, const in vec3 vertexInput){
//	vec3 deltaSpace = (light.position.xyz - vertexInput);
//	float dist = length(deltaSpace);
//	float contribution = max(0.0, dot(normalInput, normalize(deltaSpace) ) ) ;
//	float attenuation = clamp(1.0 - (dist*dist)/(light.range*light.range), 0.0, 1.0);
//	attenuation *= attenuation;
//	return contribution  * attenuation * light.intensity;
//}
//
//
//float getIsotropicFactor(in list_item light, const in vec3 normalInput, const in vec3 vertexInput, const float shininessInput){
//	float contri;
//	contri = dot(reflect(-light.direction.xyz, normalInput) , normalize(vertexInput - getCameraPosition().xyz) );
//	contri = max(0.0, contri);
//	contri = pow( contri , shininessInput);
//	return contri;
//}
//
//float getAnsistropicFactor(list_item light, const in vec3 normalInput){
//	return 1.0;
//}
//
//
//vec4 getLight(const in vec3 normalInput, const in vec3 vertexInput){
//	int x;
//	vec4 color = vec4(0);
//	float contribution;
//	vec3 deltaSpace;
//	float dist;
//	float attenuation;
//	float demon;
//	float contri;
//	float sha;
//	vec4 shadowPos;
//
//	for(x = 0; x < info.numShadows; x++){
//		int shadowIndex = 0;
//		switch(light[shadowIndex].type){
//			/*	Direction Light.	*/
//			case eDirectionLight:
//			/*	shadow factor.	*/
//			shadowPos = lightShadow[shadowIndex].shadowMatrix * vec4(vertexInput, 1.0);
//			sha = getShadowFactor(shadowPos, shadowIndex, dot(normalInput, -light[shadowIndex].direction.xyz), light[shadowIndex].shadowBias, light[shadowIndex].shadowStrength );
//			/*	final color.	*/
//			color += (getDirectionLightColor(light[shadowIndex], normalInput).xyzw * sha);
//			break;
//		}
//	}
//
//
//
//	return color;
//}
//
//
//vec4 getLightIsotropicSpecular(const in vec3 normalInput, const in vec3 vertexInput, const in float InputShininess, const in vec3 InputSpecularColor){
//	int x;
//	vec4 color = vec4(0);
//	float contribution;
//	float contri;
//	float sha;
//	vec4 shadowPos;
//	int matrixindex = 0;
//
//	/*	Compute light sources with shadow attached to them.*/
//	for(x = 0; x < getNumShadowDirectionLight(); x++){
//		int shadowIndex = getShadowDirectionIndex(x);
//
//		contri = getIsotropicFactor(light[shadowIndex], normalInput, vertexInput,  InputShininess);
//
//		/*	shadow factor.	*/
//		matrixindex = light[shadowIndex].shadowIndex;
//		shadowPos = lightShadow[matrixindex].shadowMatrix * vec4(vertexInput, 1.0);
//		sha = getShadow(shadowPos, matrixindex, dot(normalInput, -light[shadowIndex].direction.xyz), light[shadowIndex].shadowBias, light[shadowIndex].shadowStrength );
//
//		/*	final color.	*/
//		color += (getDirectionLightColor(light[shadowIndex], normalInput).xyzw * sha)  + (vec4(InputSpecularColor.rgb  * contri, 0.0) * sha);
//
//	}
//
//
//	for(x = 0; x < getNumShadowSpotLight(); x++){
//		int shadowIndex = getShadowSpotIndex(x);
//		contribution = getSpotLightContributionFactor(light[shadowIndex], normalInput, vertexInput);
//
//		matrixindex = light[shadowIndex].shadowIndex;
//		shadowPos = lightShadow[matrixindex].shadowMatrix * vec4(vertexInput, 1.0);
//		sha = getShadow(shadowPos, matrixindex, dot(normalInput, -light[shadowIndex].direction.xyz), light[shadowIndex].shadowBias, light[shadowIndex].shadowStrength );
//
//		color += sha * contribution * (light[shadowIndex].color);
//	}
//
//	for(x = 0; x < getNumShadowPointLight(); x++){
//		int shadowIndex = getShadowPointIndex(x);
//
//		shadowPos = lightShadow[matrixindex].shadowMatrix * vec4(vertexInput, 1.0);
//		sha = getCubeShadow(shadowPos, light[shadowIndex].position.xyz, matrixindex, dot(normalInput, -light[shadowIndex].direction.xyz), light[shadowIndex].shadowBias, light[shadowIndex].shadowStrength );
//
//		contribution = getPointLightFactor(light[shadowIndex], normalInput, vertexInput);
//		contri = getIsotropicFactor(light[shadowIndex], normalInput, vertexInput,  InputShininess);
//
//		color += contribution * sha * ( light[shadowIndex].color + vec4(InputSpecularColor * contri, 0.0) );
//	}
//
//
//
//	/*	*/
//	for(x = 0; x < getNumDirectionLight(); x++){
//		int ind = getDirectionIndex(x);
//		/*	specular.	*/
//		contri = getIsotropicFactor(light[ind], normalInput, vertexInput,  InputShininess);
//		/*	final color.	*/
//		color += (getDirectionLightColor(light[ind], normalInput).xyzw)  + (vec4(InputSpecularColor.rgb  * contri, 0.0));
//	}
//
//	for(x = 0; x < getNumPointLight(); x++){
//		int ind = getPointIndex(x);
//		contribution = getPointLightFactor(light[ind], normalInput, vertexInput);
//		contri = getIsotropicFactor(light[ind], normalInput, vertexInput,  InputShininess);
//		color += contribution * ( light[ind].color + vec4(InputSpecularColor * contri, 0.0) );
//	}
//
//	for(x = 0; x < getNumSpotLight(); x++){
//		int ind = getSpotIndex(x);
//
//		contribution = getSpotLightContributionFactor(light[ind], normalInput, vertexInput);
//
//		color += contribution * light[ind].color;
//
//		/*
//		deltaSpace = (light[ind].position.xyz - vertexInput);	//TODO resolve this later in the!
//		float SpotFactor = dot( normalize(deltaSpace), -normalize(light[x].direction.xyz) );
//		float SpotEffect;
//		if(SpotFactor > light[ind].angle ){
//			dist = length(deltaSpace);
//			demon = (dist / light[ind].range) + 0.05;
//			attenuation = 1.0 / (demon * demon);
//			attenuation = max((attenuation - 0.05) / (1 - 0.05),0.0);
//			contribution = max(0.0, dot(normalInput, normalize(deltaSpace))) * SpotFactor;
//			contri = dot(reflect(-light[ind].direction.xyz, normalInput) , normalize(vertexInput - info.cameraPos.xyz) );
//			contri = clamp(contri, 0.0, 1.0);
//			contri = pow( contri , InputShininess);
//			SpotEffect = smoothstep(0.1 , 0.0f, 1.0f - SpotFactor);
//			color += contribution * light[ind].intensity * light[ind].color * SpotEffect * sha + (vec4(InputSpecularColor.rgb  * contri, 0.0) * sha * SpotEffect);
//		}
//	*/
//	}
//	return color;
//}
//
//
//
///*	ansistropic specular	*/
//float getAnsistropicSpecular(in vec3 normalIn, vec3 tangentIN, in vec3 ViewIn, in vec3 LightDirection, in float shininess){
//
///*
//			"	vec3 biNormal = cross(normalize(tangent), Mnormal);\n"
//			"	vec3 halfVector = normalize((VertexPosition - CameraPos) + HDirectionLight[x].Direction);\n"
//			"	float dotHN = dot(halfVector, HDirectionLight[x].Direction);\n"
//			"	float dotVN = dot(normalize(VertexPosition - CameraPos), Mnormal);\n"
//			"	float dotHTalphaX = dot(halfVector, normalize(tangent)) / AlphaX;\n"
//			"	float dotHTalphaY = dot(halfVector, Mnormal) / AlphaY;	\n";
//			switch(lightFunctioName){	// refered to the type of light function.
//				case LightFunctioName::eLightSpecularMapped:lightSource += "	EndColor += SpecularColor * sqrt(max(0.0, contribution / dotVN)) * exp(-2.0 *(dotHTalphaX * dotHTalphaX + dotHTalphaY *dotHTalphaY) /(1.0 + dotHN)) * texture2D(SpecularMap, UV).r;\n";break;
//				default:lightSource += "	EndColor += SpecularColor * sqrt(max(0.0, contribution / dotVN)) * exp(-2.0 *(dotHTalphaX * dotHTalphaX + dotHTalphaY *dotHTalphaY) /(1.0 + dotHN));\n";break;
//			}
//*/
//
//
///*
//	vec3 biNormal = cross(normalIn, tangentIN);
//	vec3 halfVector = normalize(ViewIn + LightDirection);
//	float dotHN = dot(halfVector, LightDirection);
//	float dotVN = dot(ViewIn, normalIn);
//	float dotLN = dot(LightDirection, normalIn);
//	float dotHTalphaX = dot(halfVector, tangentIn) / AlphaX;
//	float dotHTalphaY = dot(halfVector, biNormal) / AlphaY;
//	return (sqrt(max(0.0, dotLN / dotVN)) * exp(-2.0 *(dotHTalphaX * dotHTalphaX + dotHTalphaY *dotHTalphaY) ) ) /(1.0 + dotHN);
//	*/
//	return 0.0f;
//}
//
//vec4 getLightSubSurface(const in vec3 normalInput, const in vec3 vertexInput, const in float InputShininess, const in vec3 InputSpecularColor){
//	return vec4(1.0);
//}
//
//
