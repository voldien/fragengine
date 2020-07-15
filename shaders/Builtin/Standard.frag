#ifdef FV_PIPELINE_DEFERRED
#endif
FRAGLOCATION(0, vec4, diffuse);

/*  */
IN vec2 vUV;
IN vec3 vNormal;
IN vec3 vTangent;
IN vec3 vVertex;
IN vec3 vWVVertex;

//TODO use texture template.
layout(location = 16) uniform Texture2D texture0 = {TEXTURE_DIFFUSE, vec2(1.0, 1.0), vec2(0.0,0.0)};
layout(location = 20) uniform Texture2D texture1 = {TEXTURE_SPECULAR, vec2(1.0, 1.0), vec2(0.0,0.0)};
layout(location = 24) uniform Texture2D texture2 = {TEXTURE_AMBIENT, vec2(1.0, 1.0), vec2(0.0,0.0)};
layout(location = 28) uniform Texture2D texture4 = {TEXTURE_NORMAL, vec2(1.0, 1.0), vec2(0.0,0.0)};

//material parameters
//uniform vec3  albedo;
//const  float metallic = 0.9;
const float roughness = 0.4;
//const float ao = 0.4;

/*  TODO resolve.   */
const vec3 lightPositions[4] ={
    vec3(0,10,0),
    vec3(0,500,0),
    vec3(0,50,0),
    vec3(50,50,0)
};
const vec3 lightColors[4] = {
    vec3(100,0,0),
    vec3(0,100,0),
    vec3(0,0,100),
    vec3(100,100,0)
};

void main(void) {

    /*  */
    vec4 albedo = getTextureSample(texture0, vUV).rgba;
    vec3 ao = vec3(0.3);//getTextureSample(texture2, vUV).rgb;

    /*  */
    vec3 N = normalize(getTBN( vNormal, vTangent, getGlobalTextureSample(texture4.index, vUV).rgb ));
    vec3 V = normalize(getCameraPosition() - vVertex);

    float metallic = getTextureSample(texture1, vUV).r;

    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo.rgb, metallic);

    vec3 Lo = vec3(0.0);

    for(int i = 0; i < 4; ++i)
        {
            // calculate per-light radiance
            vec3 L = normalize(lightPositions[i] - vVertex);
            vec3 H = normalize(V + L);
            float distance    = length(lightPositions[i] - vVertex);
            float attenuation = 1.0 / (distance * distance);
            vec3 radiance     = lightColors[i] * attenuation;

            // cook-torrance brdf
            float NDF = DistributionGGX(N, H, roughness);
            float G   = GeometrySmith(N, V, L, roughness);
            vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);

            vec3 kS = F;
            vec3 kD = vec3(1.0) - kS;
            kD *= 1.0 - metallic;

            vec3 numerator    = NDF * G * F;
            float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
            vec3 specular     = numerator / max(denominator, 0.001);

            // add to outgoing radiance Lo
            float NdotL = max(dot(N, L), 0.0);
            Lo += (kD * albedo.rgb / PI + specular) * radiance * NdotL;
        }   


    /*  Compute ambient color.  */
    vec3 ambient = vec3(0.03) * albedo.rgb * ao * getAmbient(vNormal).rgb;
    /*  Compute.    */
    vec3 color = ambient + Lo;

    /*  */
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));

    /*  Compute final color.    */
    diffuse = internalFog(vWVVertex, vec4(color, albedo.a) );
    diffuse.a = albedo.a;
}
