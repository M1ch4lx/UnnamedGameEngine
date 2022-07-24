#version 410 core

out vec4 FragColor;

in vec4 v_Color;
in vec2 v_TexCoord;

flat in int v_TexSlot;

uniform sampler2D[32] TextureSamplers;

void main()
{
	if(v_TexSlot == 32) // 32 signifies no texture usage
	{
		FragColor = v_Color;
	}
	else
	{
		FragColor = texture(TextureSamplers[v_TexSlot], v_TexCoord) * v_Color;
	}
}