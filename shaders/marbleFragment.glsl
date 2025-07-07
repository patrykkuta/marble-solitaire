#version 430

in vec2 tc;
in vec3 fragNormal;

uniform vec3 lightDirection; // Directional light direction
uniform int isRenderedOnScreen;
uniform int x, y;

layout (binding=0) uniform sampler2D samp;

out vec4 color;

void main() {
    if (isRenderedOnScreen == 1) {
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
    else {
        color = vec4(x/255.0, y/255.0, 0.0, 0.0);
    }
}