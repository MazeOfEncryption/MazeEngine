#version 330 core
#define PI 3.14159265359
in highp vec2 v_UV;
uniform sampler2D u_texture;
uniform float u_time;
out highp vec4 color;
highp float d = 0.003f;
highp mat4 lookat(vec3 p, vec3 target, vec3 up) {
	highp vec3 z = normalize(p - target);
	highp vec3 x = normalize(cross(up, z));
	highp vec3 y = normalize(cross(z, x));
	return mat4 (
		x.x, x.y, x.z, 0.0f,	
		y.x, y.y, y.z, 0.0f,
		z.x, z.y, z.z, 0.0f,
		p.x, p.y, p.z, 1.0f
	);
}
// highp vec3 up = vec3(0.0f, 1.0f, 0.0f);
void main () {
	highp float depth = texture(u_texture, v_UV).x;
	// highp vec3 point = vec3(v_UV, depth);
	// highp vec2 derivative = normalize(vec2(-dFdx(depth), -dFdy(depth)));
	// highp vec3 norm = normalize(vec3(derivative, 1.0f));
	// highp mat4 dir = lookat (vec3(0.0f), norm, vec3(0.0f, 0.0f, 1.0f));
	// color = vec4((norm + 1.0f) / 2.0f, 1.0f);

	highp float dzdx = (texture(u_texture, v_UV + vec2(d, 0.0)).x - texture(u_texture, v_UV + vec2(-d,  0.0f)).x) / (2.0 * d);
	highp float dzdy = (texture(u_texture, v_UV + vec2(0.0, d)).x - texture(u_texture, v_UV + vec2( 0.0f, -d)).x) / (2.0 * d);
	highp vec2 gradient = vec2(dzdx, dzdy);
	highp float degrees = u_time * 90.0f;
	highp float theta = degrees * PI / 180.0f;
	mat2 rot = mat2(
		cos(theta), -sin(theta),
		sin(theta),  cos(theta)
	);
	highp vec3 norm = normalize(vec3(rot * gradient, 1.0f));
	color = vec4((norm * 0.5f + 0.5f), 1.0f);
	// color = vec4(norm.x * 0.5f + 0.5f, norm.y * 0.5f + 0.5f, norm.z * 0.5f + 0.5f, 1.0f);
}