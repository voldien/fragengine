FRAGLOCATION(0, vec4, fragColor);

layout(binding = 0) uniform sampler2D hdrBuffer;

smooth in vec2 vUV;

uniform float exposure;

void main(void){
    const float gamma = 2.2;
    vec3 hdrColor = texture(hdrBuffer, vUV).rgb;

    // Exposure tone mapping
    vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);

    // Gamma correction
    //mapped = pow(mapped, vec3(1.0 / gamma));

    fragColor = vec4(mapped, 1.0);
}
