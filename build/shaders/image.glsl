#version 330 core
in highp vec2 v_UV;
uniform sampler2D image;
out highp vec4 color;
void main () {
	color = texture(image, v_UV);
}