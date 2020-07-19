FRAGLOCATION(0, vec4, fragColor);
uniform sampler2D DiffuseTexture;
uniform int BlurAmount;
uniform float BlurScale;
uniform float BlurStrength;
smooth in vec2 UV;

uniform float blurs[];
uniform int blurSample;

const float blur[9] = float[9](
	0.05,0.09, 0.11, 0.15,
	0.2,0.15,0.11,0.09, 0.05
);

vec3 BlurColor(void){
	vec2 blurPos  = vec2(UV.x - 0.0045, UV.y);
	vec3 color = vec3(0,0,0);
	for(int x = 0; x < 9; x++){
		color += texture2D(DiffuseTexture,blurPos).xyz * blur[x] * 0.5;
		blurPos.x += 0.001;
	}


	blurPos = vec2(UV.x, UV.y -  0.0045);
	for(int x = 0; x < 9; x++){
		color += texture2D(DiffuseTexture,blurPos).xyz * blur[x] * 0.5;
		blurPos.y += 0.001;
	}
	return color;
}


void main(void){
	fragColor = vec4(BlurColor(),1.0);

}

in vec2 UV;
uniform sampler2D DiffuseTexture;
uniform vec2 Screen = vec2(1920.0f,1080.0f);
uniform float BlurAmount = 10.0f;
uniform float BlurScale = 1.0f;
uniform float radius = 1.0f;
uniform float exposure = 1.25f;
uniform float downSampleTexture = 4.0f;
uniform float bloomFactor = 1.0f;

#define Additive 0x1
#define ScreenBlend  0x2
#define HorizontalBlur 0x4
#define VerticalBlur 0x8

vec3 BlurColor(void){
	vec3 color = vec3(0,0,0);
	float deviation = (float(BlurAmount) * 0.5f) * 0.35;
	deviation *= deviation;
	for(int x = 0; x < 10; x++){
		float offset = float(x) - float(BlurAmount) * 0.5f;
		vec3 _color = texture2D(DiffuseTexture, UV + vec2(offset * (5.0f / Screen.x) * BlurScale, 0.0f), 5.0f).xyz *  GaussianFilter( offset , deviation ) * 0.5;
		color += _color;
		continue;
	}
	for(int x = 0; x < 10; x++){
		float offset = float(x) - float(BlurAmount) * 0.5f;
		vec3 _color = texture2D(DiffuseTexture, UV + vec2(0, offset * (5.0f / Screen.y) * BlurScale), 5.0f).xyz *  GaussianFilter( offset , deviation ) * 0.5;
		color += _color;
		continue;
	}
	return clamp(color,0.0f, 1.0f);
}