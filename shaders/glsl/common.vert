/**
    Internal common glsl declaration for the PVEngine.
    Copyright (C) 2019  Valdemar Lindberg

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