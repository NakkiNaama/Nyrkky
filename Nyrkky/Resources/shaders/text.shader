#shader vertex
#version 330 core

layout(location = 0) in vec4 vertex;
out vec2 TexCoord;
 
uniform mat4 projection;

void main()
{
	gl_Position = projection * vec4(vertex.xy, 0, 1);
	TexCoord = vertex.zw;
}





#shader fragment
#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D character;
uniform vec3 textColor;

void main()
{
	vec4 sample = vec4(1.0, 1.0, 1.0, texture(character, TexCoord).r);
	FragColor = vec4(textColor, 1.0) * sample;
}



