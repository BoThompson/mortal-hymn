#version 400
in vec3 vertexPosition_modelspace;
in vec2 vertexUV;
uniform sampler2D tex;
out vec2 fragmentUV;
out float fragDepth;
uniform mat4 MVP;
void main(){
  gl_Position = MVP * vec4(vertexPosition_modelspace, 1.0);
  fragmentUV = vertexUV;
  fragDepth=gl_Position.z;
}