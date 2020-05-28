/**
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
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_explicit_attrib_location : enable

#if defined(GL_ARB_explicit_attrib_location)
layout(location = 0) out vec4 fragColor;
#elif __VERSION__ == 130
out vec4 fragColor;
#endif
//layout(binding = 1)
layout(location = 1) in vec2 uv;
uniform sampler2D tex0;

//#if __VERSION__ > 120
//layout(location = 1) in vec2 uv;
//#else
//varying vec2 uv;
//#endif

/*  TODO add extension for checking.    */
void main(void){
	#if defined(GL_ARB_explicit_attrib_location)
	fragColor = texture(tex0, uv);
	#else
	gl_FragColor = texture2D(tex0, uv);
	#endif
}
