#version 430
layout(location = 0) in vec3 aPosition; // Vertex position
layout(location = 1) in vec2 aTexCoord; // Texture coordinates
out vec2 vTexCoord; // Output variable for passing texture coordinates to the fragment shader

void main() {
    // Pass the texture coordinates to the fragment shader
    vTexCoord = aTexCoord;

    // Set the position of the vertex
    gl_Position = vec4(aPosition, 1.0);
}