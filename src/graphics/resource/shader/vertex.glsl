#version 330 core
layout (location = 0) in vec3 apos;
layout (location = 1) in vec3 acolor;
layout (location = 2) in vec2 atexCoord;

out vec3 color;
out vec2 texCoord;

void main()
{
  gl_Position = vec4(apos,1.0);
  color = acolor;
  texCoord = atexCoord;
}
