FRAGLOCATION(0, vec4, fragColor);

IN vec2 UV;
uniform sampler2D diffuse0;
uniform sampler2D normal0;
uniform sampler2D world0;
uniform sampler2D depth0;


void main(void){
	fragColor = texture( diffuse0, getScreenUV());
	fragColor.a = 1.0;
}
