#version 410 core

layout (location = 0) in vec3 aPos;

uniform mat4 Transform;

uniform mat4 ViewProjection;

void main()
{
   gl_Position = (ViewProjection * Transform) * vec4(aPos, 1.0);
}