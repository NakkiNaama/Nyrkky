#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in float texIndex;

out vec2 v_TexCoord;
out float v_TexIndex;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	v_TexCoord = texCoord;
	v_TexIndex = texIndex;
}


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in float v_TexIndex; // Change this to 'in' from 'out'

uniform sampler2DArray u_Textures;

void main()
{
    vec4 texColor = texture(u_Textures, vec3(v_TexCoord, v_TexIndex));
    color = texColor;
}




