



/**
 *
 */
float random(vec4 seed) {
	float dot_product = dot(seed, vec4(12.9898,78.233, 45.164,
	94.673));
	return fract(sin(dot_product) * 43758.5453);
}

/**
 *
 */
vec4 slerp(const in vec4 p0, const in vec4 p1, const in float t){
	float dotp = dot(normalize(p0), normalize(p1));
	if((dotp > 0.99999) || (dotp < -0.9999)){
		if(t <= 0.5)
			return p0;
		return p1;
	}
	float theta = acos(dotp * PI/180.0);
	vec4 P = ((p0*sin((1-t)*theta) + p1*sin(t*theta)) / sin(theta));
	P.w = 1;
	return P;
}

/**
 *
 */
vec3 slerp(const in vec3 p0, const in vec3 p1, const in float t){
	float dotp = dot(normalize(p0), normalize(p1));
	if((dotp > 0.99999) || (dotp < -0.9999)){
		if(t <= 0.5)
			return p0;
		return p1;
	}
	float theta = acos(dotp * PI/180.0);
	vec3 P = ((p0*sin((1-t)*theta) + p1*sin(t*theta)) / sin(theta));
	//P.w = 1;
	return P;
}

/**
 *
 */
vec4 lerp(const in vec4 p0, const in vec4 p1, const in float t){
	return p0 + (p1 - p0) * t;
}

/**
 *
 */
vec3 lerp(const in vec3 p0, const in vec3 p1, const in float t){
	return p0 + (p1 - p0) * t;
}

/**
 *
 */
vec3 projectOnPlane(const in vec3 point, const in vec3 pointcenter, const in vec3 pointnormal){
	return point -(dot(pointnormal, point - pointcenter)) * pointnormal;
}

/**
 *
 */
int sideOfPlane(const in vec3 point, const in vec3 pointcenter, const in vec3 pointnormal){
	if(dot(point-pointcenter, pointnormal) >= 0.0) return 1;else return 0;
}

/**
 *
 */
vec3 linePlaneIntersect(const in vec3 linepoint, const in vec3 linevector, const in vec3 pointcenter, const in vec3 pointnormal){
	return linepoint + linevector *(dot(pointnormal, pointcenter - linepoint) /dot(pointnormal, linevector));
}


/**
 *
 */
int hash(in int seed){
	seed += ( seed << 10u);
	seed ^= ( seed << 6u);
	seed += ( seed << 3u);
	seed ^= ( seed << 11u);
	seed += ( seed << 15u);
	return seed;
}



mat3 rotateAroundDir(const in vec3 dir, const in float angle){
	/*	https://www.opengl.org/discussion_boards/showthread.php/159578-Rotate-a-vector-about-a-vector	*/
	float c = cos(angle);
	float s = sin(angle);
	float t = 1.0 - c;

	mat3 rot = mat3( vec3( t * dir.x * dir.x + c, t * dir.x * dir.y - s * dir.z, t * dir.x * dir.z + s * dir.y ),
				vec3(t * dir.x * dir.y + s * dir.z, t * dir.y * dir.y + c , t * dir.y * dir.z - s * dir.x ),
				vec3(t * dir.x * dir.z - s * dir.y, t * dir.y * dir.z + s * dir.x, t * dir.z * dir.z + c) );

	return rot;
}



/**
 *
 */
vec3 getTangentNormal(const in vec3 normalIn, const in vec3 tangent, const in sampler2D textureNormal, const in vec2 uvCoordination){
	vec3 Ttangent = normalize(tangent - dot(tangent, normalIn) * normalIn);
	vec3 bittagnet = cross(Ttangent, normalIn);
	vec3 NormalMapBump = texture2D(textureNormal, uvCoordination).rgb;

	/*	[-1,1]	*/
	NormalMapBump = (2.0 * NormalMapBump) - 1.0f;
	return (mat3(Ttangent,bittagnet, normalIn) * NormalMapBump).xyz;
}



/**
 *
 */
vec3 getTBN(const in vec3 InNormal, const in vec3 InTangent, const in vec3 normalSampler){
	return ((mat3(normalize(InTangent - dot(InTangent, InNormal) * InNormal), cross(InTangent, InNormal), InNormal))  *
   			((2.0f * normalSampler ) - 1.0f)).xyz;
}

/**
 *
 */
vec3 getTBN(const in vec3 InNormal, const in vec3 InTangent, const in sampler2D normalSampler, const in vec2 uv){
    return getTBN(InNormal, InTangent, texture(normalSampler, uv).xyz);

//	return ((mat3(normalize(InTangent - dot(InTangent, InNormal) * InNormal), cross(InTangent, InNormal), InNormal))  *
//   			((2.0f * vec3(texture2D(normalSampler, uv).rg,1.0) ) - 1.0f)).xyz;
}



/**
 *
 */
mat3 rotateAroundDirection(const in vec3 dir, const in float angle){
	float c = cos(angle);
	float s = sin(angle);
	float t = 1.0 - c;
	mat3 rot = mat3( vec3( t * dir.x * dir.x + c, t * dir.x * dir.y - s * dir.z, t * dir.x * dir.z + s * dir.y ),
				vec3(t * dir.x * dir.y + s * dir.z, t * dir.y * dir.y + c , t * dir.y * dir.z - s * dir.x ),
				vec3(t * dir.x * dir.z - s * dir.y, t * dir.y * dir.z + s * dir.x, t * dir.z * dir.z + c) );
	return rot;
}



vec2 getParallax(const in sampler2D heightMap, const in vec2 uv, const in vec3 cameraDir, const in vec2 biasScale){
	float v = texture2D(heightMap, uv).r * biasScale.x - biasScale.y;
	return (uv + (cameraDir.xy * v)).xy;
}

vec2 getParallaxeOcclusion(const in sampler2D heightMap){
	return vec2(0.0);
}

/**
 *
 */
float toneMapping(const in float exposure, const in float brightMax){
	return exposure * (exposure / brightMax + 1.0f) / (exposure + 1.0f);
}


// Instance rapper.
#define FRAG_ACCESS_INSTANCED_PROP(Props, _Color)
#define FRAG_INSTANCING_BUFFER_START(Props)
#define FRAG_INSTANCING_BUFFER_END(Props)


#define FRAG_FOG_COORDS(Props)
#define SHADOW_COORDS(Props)

#define FRAG_SETUP_INSTANCE_ID()
#define FRAG_TRANSFER_INSTANCE_ID()

#define FragObjectToClipPos()

#define FRAG_TRANSFER_SHADOW
#define FRAG_TRANSFER_FOG(o, vertex)

#define FRAG_VERTEX_INPUT_INSTANCE_ID
#define FRAG_TRANSFORM_TEX

#define frag_LightmapST