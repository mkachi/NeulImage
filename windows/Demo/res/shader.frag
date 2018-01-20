#version 330 core

in vec2 TexCoord;
out vec4 outColor;

uniform sampler2D ML_TEXTURE0;
uniform vec4 ML_COLOR;

void main()
{
   vec4 color = ML_COLOR * texture(ML_TEXTURE0, TexCoord);
   outColor = color;
}