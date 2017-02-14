#version 400
in vec4 fragmentColor;
in vec3 fragmentBarycentric;
out vec4 color;
uniform float baryFactor;
void main(){
  if(fragmentBarycentric.x < baryFactor
  || fragmentBarycentric.y < baryFactor
  || fragmentBarycentric.z < baryFactor)
	color = fragmentColor;
  else
	discard;
	//color = vec4(1, 1, 0, 1);
}