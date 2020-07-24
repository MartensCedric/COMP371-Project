#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 light_proj_view_matrix;

void main()
{
    mat4 scale_bias_matrix = mat4(vec4(0.5, 0.0, 0.0, 0.0),
                                    vec4(0.0, 0.5, 0.0, 0.0),
                                    vec4(0.0, 0.0, 0.5, 0.0),
                                    vec4(0.5, 0.5, 0.5, 1.0));
    gl_Position = 
                    //scale_bias_matrix * // bias the depth map coordinates
                    light_proj_view_matrix * vec4(position, 1.0);
}
