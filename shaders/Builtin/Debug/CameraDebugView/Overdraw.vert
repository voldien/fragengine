ATTRIBUTE_IN(0) vec3 vertex;

void main (void){
	vec4 viewpos  = getViewRotationMatrix() * vec4(vertex, 1.0);
	gl_Position = viewpos.xyw;
}

