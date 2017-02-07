//LIT TEXTURE VERTEX SHADER
#version 330

uniform	mat4 	projectionMatrix;
uniform	mat4 	viewMatrix;
uniform	mat4 	modelMatrix;

in vec3 vertex;
in vec3 normal;
in vec2 uv;

out vec2 tCoord;

void main( void )
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 1.f);
	tCoord = uv;
}
