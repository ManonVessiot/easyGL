#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

void main(){
   gl_Position = position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform ivec2 u_ScreenSize;

void main(){
   float r = gl_FragCoord.x / u_ScreenSize.x;
   float g = gl_FragCoord.y / u_ScreenSize.y;
   color = vec4(r, g, 1.0, 1.0);
}