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

/*	*/
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
#extension GL_AMD_texture_gather_bias_lod : enable

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

#if defined(GL_ARB_explicit_uniform_location)
	//layout(location = 1) in vec2 uv;
	#define IN_EXPL(x) layout(location = x) in 
	#define OUT_EXPL(x) layout(location = x) out
#else

#endif

/*  Storage buffer. */
#if __VERSION__ >= 450 || defined(GL_ARB_enhanced_layouts)
    #define STORAGEBUFFER(x) layout(std140, binding = x, shared)
#elif __VERSION__ > 130 || defined(GL_ARB_uniform_buffer_object)
    #define STORAGEBUFFER(x) layout(std140, shared)
#else
    #define STORAGEBUFFER(x)
#endif

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

#if __VERSION__ >= 450 || defined(GL_ARB_enhanced_layouts)
    #define UNIFORMBUFFER(x) layout(std140, binding = x, shared)
#elif __VERSION__ > 130 || defined(GL_ARB_uniform_buffer_object)
    #define UNIFORMBUFFER(x) layout(std140, shared)
#else
    #define UNIFORMBUFFER(x)
#endif
