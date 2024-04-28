#version 430
in vec2 tc; // interpolated incoming texture coordinate
out	vec4	color;
uniform	mat4	mv_matrix;
uniform	mat4	proj_matrix;
layout (binding=0) uniform sampler2D samp;

uniform int isRenderedOnScreen;
uniform int x, y;

void main(void)
{ 
	if (isRenderedOnScreen == 1) color = texture(samp, tc);
	else color = vec4(x/255.0, y/255.0, 0.0, 0.0);
}