#version 330 core
layout (location = 0) in vec4 vertex;
layout (location = 1) in vec2 texCoord;

out vec2 TexCoord;

uniform mat4 ML_PV;

void main()
{
	TexCoord = vec2(texCoord.x, texCoord.y);
    gl_Position = ML_PV * vec4(vertex.xyz, 1.0);
}