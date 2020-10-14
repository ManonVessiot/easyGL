#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 texCoord;

out vec3 v_Normals;
out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main(){
   gl_Position = u_MVP * position;
   v_Normals = normalize(normals);
   v_TexCoord = texCoord;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Normals;
in vec2 v_TexCoord;

uniform vec4 u_Color;

void main(){
    color = u_Color * (_LightColor0 + _AmbientLight);
}