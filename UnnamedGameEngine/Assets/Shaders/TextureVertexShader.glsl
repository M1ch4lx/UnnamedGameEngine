#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec4 color;

uniform mat4 Transform;

uniform mat4 ViewProjection;

out vec4 v_Color;
out vec2 v_TexCoord;

void main()
{
   v_Color = color;
   v_TexCoord = texCoord;
   gl_Position = ViewProjection * Transform * vec4(position, 1.0);
}