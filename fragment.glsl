
#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D texture;

void main(){
	vec4 tex_color = texture(texture,texCoord);
	FragColor = tex_color;
}

