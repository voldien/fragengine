FRAGLOCATION(0, vec4, fragcolor);
#ifdef FRAG_PIPELINE_DEFERRED
#endif


struct structureVS 
{
	vec4 screen_vertex;
	vec4 world_vertex;
	vec3 normal;
	vec2 uv;
	vec3 viewDir;
	FRAG_VERTEX_INPUT_INSTANCE_ID
};

IN block {
	vec4 Vertex;
	vec4 WorldVertex;
    vec4 Normal;
    vec4 Tangent;
    vec2 UV0;
    vec2 UV1;
} In ;


void main(){
	structureVS data;
	FragmentMain(data);

	fragcolor = data.world_vertex;
}