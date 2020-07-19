FRAGLOCATION(0, vec4, fragColor);

uniform vec4 color;

void main(void){
	fragColor = vec4(color, 1.0);
}