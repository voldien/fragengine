FRAGLOCATION(0, vec4, fragColor);
FRAGLOCATION(4, vec4, intensity);

IN vec3 vVertex;
uniform samplerCube texture0;

void main(void){
	fragColor = texture(texture0, vVertex);
}
