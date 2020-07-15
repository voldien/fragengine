ATTRIBUTE_IN(0) vec3 vertex;
OUT vec2 UV;

void main(void){
	UV = ( vertex.xy +  vec2(1.0)) / 2.0;
	gl_Position = vec4(vertex, 1.0);
}

