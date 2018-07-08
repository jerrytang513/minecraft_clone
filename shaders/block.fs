#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D Texture1;

void main(){
  FragColor = texture(Texture1, TexCoords);
//FragColor = vec4(0.5f,0.5f,0.5f,1.0f);
}
