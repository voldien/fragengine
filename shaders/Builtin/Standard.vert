ATTRIBUTE_IN(0) vec3 vertex;	/*	*/
ATTRIBUTE_IN(1) vec2 uv;        /*	*/
ATTRIBUTE_IN(2) vec3 normal;    /*	*/
ATTRIBUTE_IN(3) vec3 tangent;	/*	*/


/*	Automatically populated TODO*/
//uniform mat4 MVP;
//uniform mat4 Model;

//layout(std140,binding=2) uniform matrixBuffer {
    uniform mat4 MVP;
    uniform mat4 Model;
//};

/*  Binding Standard Frag*/
OUT vec2 vUV;
OUT vec3 vNormal;
OUT vec3 vTangent;
OUT vec3 vVertex;
OUT vec3 vWVVertex;

void main(void){

	/*	*/
	gl_Position = MVP * vec4(vertex, 1.0);
	vVertex = (Model * vec4(vertex, 0.0)).xyz;
	vWVVertex = (getViewMatrix() * Model * vec4(vertex, 1.0)).xyz;

	/*	*/
	vUV = uv;
	vNormal = (Model * vec4(normal, 0.0)).xyz;
	vTangent = (Model * vec4(tangent, 0.0)).xyz;
}
