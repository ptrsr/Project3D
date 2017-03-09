#version 330

in vec3 vertex;
in vec2 uv;

out vec2 tCoord;

uniform mat4 MVmatrix;

void main( void )
{
	gl_Position = MVmatrix * vec4(vertex, 1);
	tCoord = uv;
}