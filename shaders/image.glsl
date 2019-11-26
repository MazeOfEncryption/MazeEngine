#version 330 core
in highp vec2 v_UV;
uniform sampler2D u_texture;
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
	highp vec3 loc = vec3(v_UV, depth);
	// highp vec3 point = vec3(v_UV, depth);
	// highp vec2 derivative = normalize(vec2(-dFdx(depth), -dFdy(depth)));
	// highp vec3 norm = normalize(vec3(derivative, 1.0f));
	// highp mat4 dir = lookat (vec3(0.0f), norm, vec3(0.0f, 0.0f, 1.0f));
	// color = vec4((norm + 1.0f) / 2.0f, 1.0f);

	highp float dzdx = (texture(u_texture, v_UV + vec2(d, 0.0)).x - texture(u_texture, v_UV + vec2(-d,  0.0f)).x) / (2.0 * d);
	highp float dzdy = (texture(u_texture, v_UV + vec2(0.0, d)).x - texture(u_texture, v_UV + vec2( 0.0f, -d)).x) / (2.0 * d);
	
	highp float d2 = 0.006;
	
	highp vec2 gradient = vec2(-dzdx, -dzdy);
	highp vec2 v1 = vec2(v_UV.x + d2, v_UV.y);
	highp vec2 v2 = vec2(v_UV.x, v_UV.y + d2);
	highp vec3 p1 = vec3(v1, texture(u_texture, v1).x);
	highp vec3 p2 = vec3(v2, texture(u_texture, v2).x);
	highp vec3 n1 = p1 - loc;
	highp vec3 n2 = p2 - loc;
	highp vec3 norm = normalize(cross(n1, n2));
	// highp vec3 norm = normalize(vec3(gradient, 1.0f));
	color = vec4((norm * 0.5f + 0.5f).xy, dot(-norm, loc) * 0.5f + 0.5f, 1.0f);
	// color = vec4(0.0f, 0.0f, dot(-norm, loc) * 0.5 + 0.5f, 1.0f);
	// color = vec4(norm * 0.5f + 0.5f, 1.0f);
	// color = vec4((norm * 0.5f + 0.5f).xy, 0.0f, 1.0f);
	// color = vec4(norm.x * 0.5f + 0.5f, norm.y * 0.5f + 0.5f, norm.z * 0.5f + 0.5f, 1.0f);
	// color = vec4(p2.xy, 1.0f, 1.0f);
}