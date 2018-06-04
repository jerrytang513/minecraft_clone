#version 330
layout (location = 0) in vec3 pos;
out vec4 vCol;

uniform mat4 scale;
uniform mat4 transform;
uniform mat4 rotation;

void main()
{
    gl_Position = rotation * vec4(pos.x, pos.y, pos.z, 1.0);
    vCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);

}
