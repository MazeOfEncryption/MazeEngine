#version 330 core
in highp vec2 v_UV;
out highp vec4 color;
void main () {
	color = vec4(v_UV, 0.0f, 1.0f);
}