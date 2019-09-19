#version 330 core
in lowp vec4 v_color;
in lowp vec3 v_normal;
in lowp vec3 v_fragPos;
in lowp vec3 v_cameraPos;
out highp vec4 color;
const float PI = 3.14159265358979323;
float DistributionGGX(vec3 N, vec3 H, float roughness) {
	float a = roughness*roughness;
	float a2 = a * a;
	float NdotH = max(dot(N, H), 0.0);
	float NdotH2 = NdotH*NdotH;
	float num = a2;
	float denom = (NdotH2 * (a2 - 1.0) + 1.0);
	denom = PI * denom * denom;
	return num / denom;
}
float GeometrySchlickGGX(float NdotV, float roughness) {
	float r = (roughness + 1.0f);
	float k = (r * r) / 8.0f;
	float num = NdotV;
	float denom = NdotV * (1.0f - k) + k;
	return num / denom;
}
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
	float NdotV = max(dot(N, V), 0.0);
	float NdotL = max(dot(N, L), 0.0);
	float ggx2 = GeometrySchlickGGX(NdotV, roughness);
	float ggx1 = GeometrySchlickGGX(NdotL, roughness);
	return ggx1 * ggx2;
}
vec3 fresnelSchlick(float cosTheta, vec3 F0) {
	return F0 + (1.0f - F0) * pow(1.0f - cosTheta, 5.0f);
}
void main () {
	vec3 lightPositions[4] = vec3[4](
		vec3(-3.0f, 2.0f,  2.5f),
		vec3( 3.0f, 2.0f,  5.0f),
		vec3( 3.0f, 2.0f, -2.5f),
		vec3(-3.0f, 2.0f, -5.0f)
	);
	vec3 lightColor = vec3(10.0f);
	
	vec3 albedo = vec3(1.0f, 0.0f, 0.0f);
	float metallic = 0.6f, roughness = 0.6f, ao = 0.0f;

	vec3 N = normalize(v_normal);
	vec3 V = normalize(v_cameraPos - v_fragPos);
	
	float ior = 1.0f;
	float fresnel = ((1.0f - ior) * (1.0f + ior));
	fresnel = fresnel * fresnel;
	vec3 F0 = vec3(fresnel);
	F0 = mix(F0, albedo, metallic);

	vec3 Lo = vec3(0.0f);
	// Per Light Calculations (Can run in loop):
	for (int i = 0; i < 4; i++) {
		vec3 L = normalize(lightPositions[i] - v_fragPos);
		vec3 H = normalize(V + L);
		float distance = length(lightPositions[i] - v_fragPos);
		float attenuation = 1.0f / (distance * distance);
		vec3 radiance = lightColor * attenuation;
		float NDF = DistributionGGX(N, H, roughness);
		float G = GeometrySmith(N, V, L, roughness);
		// Should be dot(H, V)
		vec3 F = fresnelSchlick(max(dot(H, V), 0.0f), F0);
		vec3 numerator = NDF * G * F;
		float denominator = 4.0f * max(dot(N, V), 0.0f) * max(dot(N, L), 0.0f);
		vec3 specular = numerator / max(denominator, 0.001f);
		vec3 kS = F;
		vec3 kD = vec3(1.0f) - kS;
		kD *= 1.0f - metallic;
		float NdotL = max(dot(N, L), 0.0f);
		Lo += (kD * albedo / PI + specular) * radiance * NdotL;
	}
	// End of Per Light Calculations
	vec3 ambient = vec3(0.0f) * albedo * ao;
	vec3 surface = ambient + Lo;
	
	surface = surface / (surface + vec3(1.0f));
	surface = pow(surface, vec3(1.0f / 2.2f));  
	
	color = vec4(surface, 1.0f);
}