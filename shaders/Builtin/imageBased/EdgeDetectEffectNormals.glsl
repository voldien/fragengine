#include"baseImage.frag"
#include "Packages/com.unity.postprocessing/PostProcessing/Shaders/StdLib.hlsl"
TEXTURE2D_SAMPLER2D(_MainTex, sampler_MainTex);
TEXTURE2D_SAMPLER2D(_CameraNormalsTexture, sampler_CameraNormalsTexture);   //TODO add support if accessiable from the deferred shader.
float _Blend;
vec4 _Color;
float _EdgeSize;
float _ThresHold;
mat3 _Kernel;
int _Mode;
vec4 _MainTex_TexelSize;

vec4 edgeDetection(){
    return float4(0,0,0,0);
}

vec4 Frag(VaryingsDefault i) : SV_Target
{
    // Compute sample coordinate.
    float2 TexDiff = (1.0 / _ScreenParams.xy) * _EdgeSize;
    float2 sampleTexCoord = i.texcoord;

    //TODO add recompute of the sample kernel coordinates.
    float2 lb = float2(-1.0 * TexDiff.x, -1.0 * TexDiff.y);
    float4 p00 = SAMPLE_TEXTURE2D(_MainTex, sampler_MainTex, sampleTexCoord + lb);
    float2 b = float2(0.0 * TexDiff.x, -1.0 * TexDiff.y);
    float4 p10 = SAMPLE_TEXTURE2D(_MainTex,sampler_MainTex, sampleTexCoord + b);
    float2 rb = float2(1.0 * TexDiff.x, -1.0 * TexDiff.y);
    float4 p20 = SAMPLE_TEXTURE2D(_MainTex, sampler_MainTex,sampleTexCoord + rb);

    float2 l = float2(-1.0 * TexDiff.x, 0.0 * TexDiff.y);
    float4 p01 = SAMPLE_TEXTURE2D(_MainTex,sampler_MainTex, sampleTexCoord + l);
    float2 r = float2(1.0 * TexDiff.x, 0.0 * TexDiff.y);
    float4 p21 = SAMPLE_TEXTURE2D(_MainTex,sampler_MainTex, sampleTexCoord + r);

    float2 lt = float2(-1.0 * TexDiff.x, 1.0 * TexDiff.y);
    float4 p02 = SAMPLE_TEXTURE2D(_MainTex,sampler_MainTex, sampleTexCoord + lt);
    float2 t = float2(-1.0 * TexDiff.x, 1.0 * TexDiff.y);
    float4 p12 = SAMPLE_TEXTURE2D(_MainTex, sampler_MainTex, sampleTexCoord + t);
    float2 rt = float2(1.0 * TexDiff.x, 1.0 * TexDiff.y);
    float4 p22 = SAMPLE_TEXTURE2D(_MainTex, sampler_MainTex, sampleTexCoord + rt);

    //TODO add support for additional kernels.
    // Compute Matrix X and Y.
    float3 gx = -p00.xyz + p20.xyz + 2.0f * (p21.xyz - p01.xyz) - p02.xyz + p22.xyz;
    float3 gy = -p00.xyz - p20.xyz + 2.0f * (p12.xyz - p10.xyz) + p02.xyz + p22.xyz;

    // Compute the final.
    float3 g = sqrt(gx * gx + gy * gy);
    float4 color = SAMPLE_TEXTURE2D(_MainTex, sampler_MainTex, sampleTexCoord);

    /*  Mode of computation.    */
    switch(_Mode){
        default:
        case 0:
        color.rgb = lerp(color.rgb, g.rgb, _Blend.xxx) * _Color.rgb;
        break;
        case 1:
        float prop = step(_ThresHold, length(round(g.rgb)));
        float4 edge = lerp(color.rgba, _Color.rgba, prop);
        color.rgba = lerp(color.rgba, edge, _Blend.xxxx);
        break;
    }
    //color.rgb = lerp(color.rgb, g.rgb, _Blend.xxx) * _Color;
    return color;
}