/**
    VDEngine common built-in shader functions.
    Copyright (C) 2015  Valdemar Lindberg

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
ATTRIBUTE_IN(0) vec3 vertex;	/*	*/
ATTRIBUTE_IN(1) vec2 uv;        /*	*/
ATTRIBUTE_IN(2) vec3 normal;    /*	*/
ATTRIBUTE_IN(3) vec3 tangent;	/*	*/


out gl_PerVertex{
    vec4 gl_Position;
    float gl_PointSize;
    float gl_ClipDistance[];
};


out block {
    vec4 Normal;
    vec4 Tangent;
    vec2 UV0;
    vec2 UV1;
} Out ;

void main(void){
	VertexShader();
}