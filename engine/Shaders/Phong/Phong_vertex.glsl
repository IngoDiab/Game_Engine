#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normale;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 o_uv;
out vec3 o_normale;

void main()
{
        gl_Position = projection * view * model * vec4(position,1);
        o_uv = uv;
        o_normale = normalize(mat3(transpose(inverse(model))) * normale);
}

