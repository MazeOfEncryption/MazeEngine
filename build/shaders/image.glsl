#version 330 core
in highp vec2 v_UV;
uniform sampler2D image;
out highp vec4 color;
void main () {
	highp float depth = texture(image, v_UV).x;
	highp vec2 derivative = vec2(dFdx(depth), dFdy(depth));
	highp vec3 norm = normalize(vec3(normalize(derivative), 1.0f));
	color = vec4((norm.x + 1.0f) / 2.0f, (norm.y + 1.0f) / 2.0f, (norm.z + 1.0f) / 2.0f, 1.0f);
	if(derivative.x == 0.0f && derivative.y == 0.0f) color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}