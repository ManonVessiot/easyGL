#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in float textID;

out vec2 v_TexCoord;
out float v_TexID;

uniform mat4 u_MVP;

void main(){
   gl_Position = u_MVP * position;
   v_TexCoord = texCoord;
   v_TexID = textID;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in float v_TexID;

uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;

void main(){
   vec4 textColor;
   if (int(v_TexID) == 0){
      textColor = texture(u_Texture0, v_TexCoord);
   }
   else{
      textColor = texture(u_Texture1, v_TexCoord);
   }
   color = textColor;
}