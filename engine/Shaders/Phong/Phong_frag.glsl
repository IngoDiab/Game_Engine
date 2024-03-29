#version 330 core

uniform sampler2D mAlbedo;

in vec2 o_uv;
in vec3 o_normale;

out vec4 FragColor;

void main()
{
        vec4 _texelAlbedo = texture(mAlbedo, o_uv);
        FragColor = _texelAlbedo;
}