#version 330

in vec3 Color;
in bool toggle;

uniform vec3 SolidColor = vec3(-1,-1,-1);

out vec4 Fragment;

void main()
{
	if(toggle){
		Fragment = vec4(1.0 - Color.r, 1.0 - Color.g, 1.0 - Color.b, 1);
	
		if(SolidColor.r != -1.0 && SolidColor.g != -1.0 && SolidColor.b != -1.0){
			Fragment = vec4(1.0 - SolidColor.r, 1.0 - SolidColor.g, 1.0 - SolidColor.b, 1);
		
		}
	
		return;
	}
	
	else{
		Fragment = vec4(Color, 1);
		
		if(SolidColor.r != -1.0 && SolidColor.g != -1.0 && SolidColor.b != -1.0){
			Fragment = vec4(SolidColor.r, SolidColor.g, SolidColor.b, 1);
		
		}
	
		return;
	}
}