#version 420
in vec3 vertex;
uniform mat4 matrixp;
uniform mat4 matrixv;
uniform mat4 matrixm;
out vec3 position;

void main(void)
{
    vec4 p = matrixm * vec4(vertex, 1.0);
    gl_Position = matrixp * matrixv * p;
    position = p.xyz;
}
