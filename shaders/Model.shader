#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in float texID;

out vec3 v_Normals;
out vec2 v_TexCoord;
out float v_TexID;

uniform mat4 u_MVP;

void main(){
   gl_Position = u_MVP * position;
   v_Normals = normals;
   v_TexCoord = texCoord;
   v_TexID = texID;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Normals;
in vec2 v_TexCoord;
in float v_TexID;

uniform sampler2D u_Textures[2];

void main(){
   vec4 textColor;
   if (int(v_TexID) == 0){
      textColor = texture(u_Textures[0], v_TexCoord);
   }
   else{
      textColor = texture(u_Textures[1], v_TexCoord);
   }
   color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}