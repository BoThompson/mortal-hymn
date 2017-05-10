#version 400
in vec2 fragmentUV;
in float fragDepth;
out vec4 color;
uniform sampler2D tex;
void main(){
  color = texture(tex, fragmentUV);
	color = vec4(1, 1, 0, 1);
	//color = vec4(gl_FragDepth,gl_FragDepth,gl_FragDepth,1);
}