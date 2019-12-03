#version 400
in vec2 uvPos;
out vec4 fragColor;

uniform sampler2D tex;
uniform sampler2D normal;
uniform	vec3 color;

void main() {
	fragColor = texture(tex, uvPos) * vec4(color, 1.0);
}