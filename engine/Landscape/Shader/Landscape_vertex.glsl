#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertices_position_modelspace;
layout(location = 1) in vec2 vertices_uv_modelspace;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 o_uv;
out float o_height_in_model;

//TODO create uniform transformations matrices Model View Projection
// Values that stay constant for the whole mesh.

void main(){

        // TODO : Output position of the vertex, in clip space : MVP * position
        gl_Position = projection * view * model * vec4(vertices_position_modelspace,1);
        o_uv = vertices_uv_modelspace*20;
        o_height_in_model = vertices_position_modelspace.y;
}

