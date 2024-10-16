#type vertex
#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
out vec2 v_TexCoord;
uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
void main()
{
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
	v_TexCoord = a_TexCoord;
}

#type fragment
#version 330 core
layout(location = 0) out vec4 o_Color;
in vec2 v_TexCoord;
uniform sampler2D u_Texture;
uniform vec4 u_Color;
uniform float u_TilingFactor;
void main()
{
	o_Color = texture(u_Texture, v_TexCoord * u_TilingFactor) * u_Color;
}