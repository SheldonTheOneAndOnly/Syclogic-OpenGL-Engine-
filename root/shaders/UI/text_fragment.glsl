#version 460 core
in vec2 UV;
out vec4 fCol;

uniform sampler2D char;
uniform vec3 textCol;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(char, UV).r);
    fCol = vec4(textCol, 1.0) * sampled;
}  