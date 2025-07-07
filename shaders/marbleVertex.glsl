#version 430

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec2 tc;
out vec3 fragNormal;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
layout (binding=0) uniform sampler2D samp; 

void main() {
    gl_Position = proj_matrix * mv_matrix * vec4(pos, 1.0);
    tc = texCoord;

    fragNormal = normal;
}