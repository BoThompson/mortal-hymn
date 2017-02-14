#version 400
in vec3 vertexPosition_modelspace;
in vec3 vertexColor;
in vec3 vertexBarycentric;
out vec4 fragmentColor;
out vec3 fragmentBarycentric;
uniform float baryFactor;
uniform mat4 MVP;
void main(){
  gl_Position.xyz = vertexPosition_modelspace;
  gl_Position.w = 1.0;
  gl_Position = MVP * gl_Position;
  fragmentColor = vec4(vertexColor, 1);
  fragmentBarycentric = vertexBarycentric;
}