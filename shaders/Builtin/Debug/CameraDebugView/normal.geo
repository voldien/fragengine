
layout(triangles) in;
layout(line_strip, max_vertices = 20) out;

uniform float normalSize;


in vec2 UV[];
in vec3 normal[];
in vec3 tangent[];

void main(void){

	gl_Position = ModelViewProjection * gl_in[0].gl_Position;
	Color = vec4(vec3(0,1,0), 1.0);
	EmitVertex();
	
	gl_Position = ModelViewProjection * vec4(gl_in[0].gl_Position.xyz + normal[0] * normalSize,1.0);
	Color = vec4(vec3(0,1,0), 1.0);
	EmitVertex();
	EndPrimitive();
}