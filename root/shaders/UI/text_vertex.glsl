#version 460 core
layout (location = 0) in vec4 vPos;
out vec2 UV;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(vPos.xy, 0.0, 1.0);
    UV = vPos.zw;
} 