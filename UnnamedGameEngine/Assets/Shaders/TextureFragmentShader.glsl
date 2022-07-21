#version 410 core

out vec4 FragColor;

in vec4 v_Color;
in vec2 v_TexCoord;

uniform sampler2D m_textureSampler;

void main()
{
	FragColor = texture(m_textureSampler, v_TexCoord);
	//vec4 someColor = texture(m_textureSampler, v_TexCoord);
	//FragColor = vec4(0, 0, 0, 1);
}