#version 400
out vec4 color;
void main(){
  color = vec4(gl_FragCoord.x / 1000, gl_FragCoord.y / 1000, 0, 1);
}