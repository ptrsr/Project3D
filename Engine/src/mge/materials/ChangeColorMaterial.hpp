#ifndef CHANGECOLORMATERIAL_H
#define CHANGECOLORMATERIAL_H

#include <vector>
#include <glm.hpp>

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/behaviours/AbstractLight.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"

class ChangeColorMaterial : public AbstractMaterial
{
public:
	ChangeColorMaterial(Texture* pTexture, Texture* pHighlight, glm::vec3 pModelColor = glm::vec3(0), float pShininess = 10.0f, std::vector<AbstractLight*>* pLights = World::get()->GetLights());

	virtual ~ChangeColorMaterial();

	virtual void render(Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

	glm::vec3 getColor();
	void setColor(glm::vec3 pColor);

private:
	static void _lazyInitializeShader();
	void renderLights();
	void renderTextures();

	static ShaderProgram* _shader;

	//vertex uniforms
	static GLint _uMVPMatrix;
	static GLint _uModelMatrix;

	//fragment uniforms
	static GLint _uModelColor;
	static GLint _uShininess;
	static GLint _uCameraPos;
	static GLint _uTexture;
	static GLint _uHighlight;

	//vertex attributes
	static GLint _aVertex;
	static GLint _aNormal;
	static GLint _aUv;
	
	//lights
	std::vector<AbstractLight*>* _lights;

	//settings
	glm::vec3 _modelColor;
	Texture* _texture;
	Texture*_highlight;
	float _shininess;
};

#endif // LITMATERIAL_H
