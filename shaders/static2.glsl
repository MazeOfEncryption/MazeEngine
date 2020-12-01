#version 330 core
in highp vec2 v_UV;
in highp vec3 v_normal;
out highp vec4 color;
void main () {
	// color = vec4((v_normal + vec3(1.0f)) / 2.0f, 1.0f);
	color = vec4(v_UV, 1.0f, 1.0f);
}