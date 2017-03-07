#version 400
in vec2 fragmentUV;
out vec4 color;
uniform sampler2D tex;
void main(){
  color = texture(tex, fragmentUV);
	//color = vec4(1, 1, 0, 1);
}