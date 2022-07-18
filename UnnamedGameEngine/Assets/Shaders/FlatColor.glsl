#version 410 core

out vec4 FragColor;

uniform vec4 m_Color;

void main()
{
	FragColor = m_Color;
}