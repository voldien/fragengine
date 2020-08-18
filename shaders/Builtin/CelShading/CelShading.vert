



struct appdata
{
	vec4 vertex : POSITION;
	vec2 uv : TEXCOORD0;
	vec3 normal : NORMAL;
	#if defined(FRAG_LIGHTMAP_ON)
		vec2 uv1 : TEXCOORD1;
	#endif
	FRAG_VERTEX_INPUT_INSTANCE_ID
};

v2f vert (appdata v)
{
	v2f o;
	FRAG_SETUP_INSTANCE_ID(v);
	FRAG_TRANSFER_INSTANCE_ID(v, o);
	#if defined(FRAG_VERTEXLIGHT_ON)
		
	#endif

	vec4 ObjectCVertex = curveTransformationWorldVertex(v.vertex);
	/*	Compute world vertex coordiante for light probs.	*/
	#if defined(FRAG_LIGHT_PROBE_PROXY_VOLUME)
		o.worldPos = mul(unity_ObjectToWorld, v.vertex);
	#endif
	/*	*/
	o.pos = UnityObjectToClipPos(v.vertex);
	o.uv = TRANSFORM_TEX(v.uv, _MainTex);
	o.worldNormal = UnityObjectToWorldNormal(v.normal);//TODO change to the curve version later.
	o.viewDir = WorldSpaceViewDir(ObjectCVertex);

	/*	Compute the lightmap coordinate.	*/
	#if defined(FRAG_LIGHTMAP_ON)
		o.uv1 = v.uv1.xy * unity_LightmapST.xy + unity_LightmapST.zw;
	#endif

	#if defined(FRAG_VERTEXLIGHT_ON)
		o.vertexLightColor = ShadeVertexLights(v.pos, v.worldNormal);
	#endif
	
	#if defined(FRAG_LIGHTPROBE_SH)
	o.ambient = float4(ShadeSH9(float4(o.worldNormal, 1)), 1);
	#endif

	FRAG_TRANSFER_SHADOW(o);
	FRAG_TRANSFER_FOG(o,o.pos);
	return o;
}