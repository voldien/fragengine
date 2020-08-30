ATTRIBUTE_IN(0) vec3 vertex;	/*	*/
ATTRIBUTE_IN(1) vec2 uv;        /*	*/
ATTRIBUTE_IN(2) vec3 normal;    /*	*/
ATTRIBUTE_IN(3) vec3 tangent;	/*	*/

struct appdata
{
	vec4 vertex;
	vec2 uv;
	vec3 normal;
	FRAG_VERTEX_INPUT_INSTANCE_ID
};

out gl_PerVertex {
    vec4 gl_Position;
    float gl_PointSize;
    float gl_ClipDistance[];
};

OUT block {
	vec4 Vertex;
	vec4 WorldVertex;
    vec4 Normal;
    vec4 Tangent;
    vec2 UV0;
    vec2 UV1;
} Out ;

void main(){
	appdata data;
	VertexMain(data);

	/*	*/
	gl_Position = MVP * vec4(vertex, 1.0);
	Out.Vertex = (Model * vec4(vertex, 0.0)).xyz;
	Out.WorldVertex = (getViewMatrix() * Model * vec4(vertex, 1.0)).xyz;

	/*	*/
	Out.UV0 = uv;
	Out.Normal = (Model * vec4(normal, 0.0)).xyz;
	Out.UV1 = (Model * vec4(tangent, 0.0)).xyz;
}