

FRAGLOCATION(0, vec4, fragColor);

uniform sampler2D DiffuseTexture;
uniform sampler2D DepthTexture;
uniform sampler2D VelocityTexture;
uniform vec3 CameraVelocity;

void main(void){
	fragColor = vec4(1,1,1,0);
}