

struct v2f
{
	vec4 pos;
	vec3 worldNormal;
	vec2 uv;
	vec3 viewDir;
	#if defined(FRAG_LIGHTMAP_ON)
		vec2 uv1 : TEXCOORD4;
	#endif
	#if defined(FRAG_VERTEXLIGHT_ON)
		vec2 vertexLightColor : COLOR;
	#endif
	#if defined(FRAG_LIGHT_PROBE_PROXY_VOLUME)
		vec3 worldPos : TEXCOORD5;
	#endif
	#if defined(FRAG_LIGHTPROBE_SH)
	vec4 ambient : COLOR;
	#endif
	FRAG_FOG_COORDS(3)
	FRAG_SHADOW_COORDS(2)
	FRAG_VERTEX_INPUT_INSTANCE_ID
};

vec4 GetAmbient(v2f i){
	#if defined(UNITY_PASS_FORWARDBASE) || defined(UNITY_PASS_DEFERRED)
		#if defined(UNITY_LIGHT_PROBE_PROXY_VOLUME)
			return half4(ShadeSHPerPixel(i.worldNormal, _AmbientColor, i.worldPos), 1.0);
		#elif defined(LIGHTPROBE_SH)
			return i.ambient;
		#else
			return _AmbientColor;
		#endif
	#else
		return 0;
	#endif
}

vec4 GetEmission (v2f i) {
	#if defined(UNITY_PASS_FORWARDBASE) || defined(UNITY_PASS_DEFERRED)
		#if defined(_EMISSION_MAP)
			return tex2D(_EmissionMap, i.uv.xy) * _Emission;
		#else
			return 0;
		#endif
	#else
		return 0;
	#endif
}

vec4 ComputeLight(v2f i){
	#ifdef UNITY_PASS_FORWARDADD
		#if defined(POINT)
		return float4(Shade4PointLights(
			unity_4LightPosX0, unity_4LightPosY0, unity_4LightPosZ0,
			unity_LightColor[0].rgb, unity_LightColor[1].rgb,
			unity_LightColor[2].rgb, unity_LightColor[3].rgb,
			unity_4LightAtten0, i.pos, i.worldNormal), 1.0);
		#else
			return 0;
		#endif
	#else
		return 0;
	#endif
}

vec4 ComputeLightMap(v2f i){
	#if defined(UNITY_PASS_FORWARDBASE)
		#if defined(LIGHTMAP_ON)
			#if defined(SHADOWS_SHADOWMASK)
			#endif
			fixed4 lightdata = fixed4(DecodeLightmap(UNITY_SAMPLE_TEX2D(unity_Lightmap, i.uv1)), 1.0);
			fixed4 totalLightAcc = lightdata;
			return totalLightAcc;
			#if defined(DIRLIGHTMAP_COMBINED)
			return 0;
			#endif
		#else
			return 0;
		#endif
	#else
	fixed lightdata = 0 ;
	fixed4 totalLightAcc = 0;
	return totalLightAcc;
	#endif
}

vec4 ComputeDirectionLight(v2f i) {
	#if defined(UNITY_PASS_FORWARDBASE) || defined(UNITY_PASS_DEFERRED)
		#if defined(DIRECTIONAL) || defined(DIRECTIONAL_COOKIE)
		/*	Compute directional light.	*/
		float3 normal = normalize(i.worldNormal);//half3(i.worldNormal, 1);
		//float NdotL = dot(_WorldSpaceLightPos0, normal);
		float NdotL = max(dot(_WorldSpaceLightPos0, normal), 0);
		float shadow = SHADOW_ATTENUATION(i);
		float lightIntensity = smoothstep(0, 0.01, NdotL * shadow);
		return lightIntensity * _LightColor0;
		#else
			return 0;
		#endif
	#else
		return 0;
	#endif
}

vec4 frag (v2f i) : SV_Target
{
	UNITY_SETUP_INSTANCE_ID(i);

	/*	*/
	vec4 ambient = GetAmbient(i);
	vec4 totalLightAcc = ComputeDirectionLight(i) + ComputeLightMap(i) + ComputeLight(i);
	#if defined(VERTEXLIGHT_ON)
		totalLightAcc += i.vertexLightColor;
	#endif
	totalLightAcc.a = 1;

	#if defined(UNITY_PASS_FORWARDBASE) || defined(UNITY_PASS_DEFERRED)

	/*	Directional Light*/
	#if defined(DIRECTIONAL)
	vec3 normal = normalize(i.worldNormal);
	float NdotL = dot(_WorldSpaceLightPos0, normal);

	/*	Compute directional light.	*/
	vec3 viewDir = normalize(i.viewDir);
	vec3 halfVector = normalize(_WorldSpaceLightPos0 + viewDir);
	float NdotH = dot(normal, halfVector);

	/*	Compute specular.	*/
	float shadow = SHADOW_ATTENUATION(i);
	float lightIntensity = smoothstep(0, 0.01, NdotL * shadow);

	//float TotalLightIntensity = length(totalLightAcc) * 0.29;
	float specularIntensity = pow(NdotH * lightIntensity, _Glossiness * _Glossiness);
	half specularIntensitySmooth = smoothstep(0.005, 0.01, specularIntensity);
	vec4 specular = specularIntensitySmooth * _SpecularColor;

	/*	Compute rim light.	*/	
	vec4 rim = getRimColor(_RimColor, normal, NdotL, viewDir, _RimAmount, _RimThreshold);
	#else
		vec4 rim = 0;
		vec4 specular = 0;	
	#endif
	#else
		vec4 rim = 0;
		vec4 specular = 0;
	#endif
	
	/*	*/
	vec4 col = tex2D(_MainTex, i.uv) * UNITY_ACCESS_INSTANCED_PROP(Props, _Color) * ( ambient + totalLightAcc + specular + rim);
	col += GetEmission(i);
	
	FRAG_APPLY_FOG(i.fogCoord, col);
	return col;
}
