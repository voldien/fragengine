#include "Packages/com.unity.postprocessing/PostProcessing/Shaders/StdLib.hlsl"
FRAGLOCATION(0, vec4, fragColor);
TEXTURE2D_SAMPLER2D(_MainTex, sampler_MainTex);

float _Blend;
int _Mode;

vec2 Frag(VaryingsDefault i)
{
	vec4 color = SAMPLE_TEXTURE2D(_MainTex, sampler_MainTex, i.texcoord);
	vec3 luminance = dot(color.rgb, vec3(0.299, 0.587, 0.114));
	switch(_Mode){
		default:
		case 0:
			luminance *= vec4(1.0, 0.95, 0.82);
		break;
		case 1:
			luminance *= vec4(1.2, 1.0, 0.8);
		break;
	}

	color.rgb = lerp(color.rgb, luminance, _Blend.xxx);
	return color * float4(color.rgb, 1.0);
}