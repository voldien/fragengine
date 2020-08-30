
FRAGLOCATION(0, vec4, fragColor);

uniform sampler2D u_texture;
uniform vec4 u_color;
uniform float u_buffer;
uniform float u_gamma;


smooth in vec2 UV;

void main(void){
    float dist  = texture2D(u_texture, UV).r;
    float alpha = smoothstep(u_buffer - u_gamma, u_buffer + u_gamma, dist);
    
    fragColor = vec4(u_color.rgb, alpha * u_color.a);
}