#ifdef _VERTEX_

in vec3 position;
in vec3 normal;
in vec2 uv;

uniform mat4 model = mat4(1.0);
uniform mat4 perspective = mat4(1.0);
uniform mat4 view = mat4(1.0);
uniform float time = 0.0;

out vec3 color;

vec4 hsv_to_rgb(float h, float s, float v, float a)
{
	float c = v * s;
	h = mod((h * 6.0), 6.0);
	float x = c * (1.0 - abs(mod(h, 2.0) - 1.0));
	vec4 color;

	if (0.0 <= h && h < 1.0) {
		color = vec4(c, x, 0.0, a);
	} else if (1.0 <= h && h < 2.0) {
		color = vec4(x, c, 0.0, a);
	} else if (2.0 <= h && h < 3.0) {
		color = vec4(0.0, c, x, a);
	} else if (3.0 <= h && h < 4.0) {
		color = vec4(0.0, x, c, a);
	} else if (4.0 <= h && h < 5.0) {
		color = vec4(x, 0.0, c, a);
	} else if (5.0 <= h && h < 6.0) {
		color = vec4(c, 0.0, x, a);
	} else {
		color = vec4(0.0, 0.0, 0.0, a);
	}

	color.rgb += v - c;

	return color;
}

void main()
{
	gl_Position = perspective * view * model * vec4(position, 1.0);
	color = hsv_to_rgb(time, 1.0, 1.0, 1.0).xyz;
}

#else
#ifdef _FRAGMENT_
	
in vec3 color;

out vec4 frag_color;

void main()
{
	frag_color = vec4(color, 1.0);
}
#endif
#endif
