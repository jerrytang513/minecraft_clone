#version 320 es

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D texture;

void main(){
  FragColor = texture(texture,texCoord);
}
