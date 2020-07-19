FRAGLOCATION(0, vec4, fragcolor);
#ifdef FRAG_PIPELINE_DEFERRED
#endif

/*  */
IN vec2 vUV;
IN vec3 vNormal;
IN vec3 vTangent;
IN vec3 vVertex;
IN vec3 vWVVertex;


struct structureVS 
{
	vec4 screen_vertex;
	vec4 world_vertex;
	vec3 normal;
	vec2 uv;
	vec3 viewDir;
	FRAG_VERTEX_INPUT_INSTANCE_ID
};


void main(){
	structureVS data;
	FragmentMain(data);

	fragcolor = data.world_vertex;
}