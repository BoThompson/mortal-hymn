#version 400
in vec3 vertexPosition_modelspace;
in vec2 vertexUV;
uniform sampler2D tex;
out vec2 fragmentUV;
uniform mat4 MVP;
void main(){
  gl_Position.xyz = vertexPosition_modelspace;
  gl_Position.w = 1.0;
  gl_Position = MVP * gl_Position;
  fragmentUV = vertexUV;
}