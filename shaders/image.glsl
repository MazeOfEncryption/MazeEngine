#version 330 core
in highp vec2 v_UV;
uniform sampler2D u_texture;
out highp vec4 color;
highp float dx = 0.001f, dy = 0.001f;
void main () {
	// highp float depth = texture(u_texture, v_UV).x;
	// highp vec2 derivative = normalize(vec2(-dFdx(depth), -dFdy(depth)));
	// highp vec3 norm = normalize(vec3(derivative, 1.0f));
	// color = vec4((norm.x + 1.0f) / 2.0f, (norm.y + 1.0f) / 2.0f, (norm.z + 1.0f) / 2.0f, 1.0f);
	// if(derivative.x == 0.0f && derivative.y == 0.0f) color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	highp float dzdx = (texture(u_texture, v_UV + vec2(dx, 0.0)).x - texture(u_texture, v_UV + vec2(-dx,  0.0f)).x) / (2.0 * dx);
	highp float dzdy = (texture(u_texture, v_UV + vec2(0.0, dy)).x - texture(u_texture, v_UV + vec2( 0.0f, -dy)).x) / (2.0 * dy);
	highp vec3 norm = normalize(vec3(-dzdx, -dzdy, 1.0f));
	color = vec4((norm.x + 1.0f) / 2.0f, (norm.y + 1.0f) / 2.0f, (norm.z + 1.0f) / 2.0f, 1.0f);
}