#version 330 core
layout (location = 0) in vec4 vertex;
layout (location = 1) in vec2 texCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 proj;

void main()
{
    gl_Position = proj * model * vec4(vertex.xy, 0.0, 1.0);
	TexCoord = vec2(texCoord.x, texCoord.y);
}