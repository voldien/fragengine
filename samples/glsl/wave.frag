#extension GL_ARB_separate_shader_objects : enable
layout(location = 0) out vec4 fragColor;
layout(location = 1) in vec2 uv;

uniform vec2 resolution;
uniform float time;
uniform vec2 mouse;

void main(void) {

    vec2 pos = 1.0- 2.0 * mouse;

    fragColor = vec4(1,1,0,1);
}
