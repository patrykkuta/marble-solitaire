#version 430

in vec2 tc; // interpolated incoming texture coordinate
in vec3 fragNormal; // incoming interpolated vertex normal

out	vec4	color;

uniform	mat4	mv_matrix;
uniform	mat4	proj_matrix;
uniform vec3 lightDirection; // direction of the light source

layout (binding=0) uniform sampler2D samp;

void main(void)
{ 
	// Sample texture color
    vec4 texColor = texture(samp, tc);
    
    // Normalize the interpolated normal
    vec3 normal = normalize(fragNormal);
    
    // Calculate the dot product between the normal and light direction
    float diffuseFactor = max(dot(normal, normalize(lightDirection)), 0.0);
    
    // Apply diffuse lighting
    vec3 diffuseColor = vec3(1.0, 1.0, 1.0); // white light
    vec3 finalColor = diffuseColor * diffuseFactor;
    
    // Combine the texture color with the lighting result
    color = texColor * vec4(finalColor, 1.0);
}