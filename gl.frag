#version 130
in vec3 position;

out vec4 color;

uniform vec4 fixed_color;
uniform vec3 charges_position[4];
uniform float charges_value[4];

void main(void)
{
    vec3 sum = vec3(0, 0, 0);

    for (int i = 0; i < 4; ++i) {
        vec3 r = position - charges_position[i];
        if (dot(r, r) == 0) {
            color = vec4(0, 0, 0, 0);
            return;
        } else {
            const float cst = 4.0 * 3.14159265 * 8.854187e-12;
            vec3 e = normalize(r) * (charges_value[i] / (cst * dot(r, r)));
            sum += e;
        }
    }

    float intencity = length(sum);

    float a = pow(sin(log(intencity + 0.2) * 5.0), 6.0);
    color = fixed_color * min(1.0, a);

    float minimum = 1e5;
    if (intencity < minimum) {
        color *= intencity / minimum;
    }
}
