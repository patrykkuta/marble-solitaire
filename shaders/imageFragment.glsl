#version 430
in vec2 vTexCoord; // Input variable for receiving texture coordinates from the vertex shader
out vec4 fragColor; // Output variable for the fragment color
uniform sampler2D uTexture; // Uniform variable for the texture

void main() {
    // Sample the texture using the texture coordinates
    vec4 texColor = texture(uTexture, vTexCoord);
    
    // Output the texture color as the fragment color
    fragColor = texColor;
}