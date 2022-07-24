#version 410 core

/*
struct RectangleVertex
{
	Vector3 ModelPosition;
	Vector2 Translation;
	float Rotation;
	Color4 Color;
	int TexSlot;
	Vector2 TexCoord;
};
*/

layout (location = 0) in vec3 modelPosition;
layout (location = 1) in vec2 translation;
layout (location = 2) in float rotation;
layout (location = 3) in vec4 color;
layout (location = 4) in int texSlot;
layout (location = 5) in vec2 texCoord;

uniform mat4 ViewProjection;

out vec4 v_Color;
out vec2 v_TexCoord;

flat out int v_TexSlot;

void main()
{
   v_Color = color;
   v_TexCoord = texCoord;
   v_TexSlot = texSlot;

   mat3 rotationMatrix;
   rotationMatrix[0][0] = cos(rotation);
   rotationMatrix[0][1] = sin(rotation);
   rotationMatrix[1][0] = -sin(rotation);
   rotationMatrix[1][1] = cos(rotation);
   rotationMatrix[2][2] = 1.0;
   
   vec4 position = vec4(rotationMatrix * modelPosition, 1.0) + vec4(translation, 0.0, 0.0);

   gl_Position = ViewProjection * position;
}