#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 view;

uniform mat4 projection;

void main()
{
   mat4 mvp = projection * view;
   gl_Position = mvp * vec4(aPos.x, aPos.y, aPos.z, 1.0);
 
   //gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}