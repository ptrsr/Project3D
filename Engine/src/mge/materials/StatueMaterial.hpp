#ifndef STATUEMATERIAL_H
#define STATUEMATERIAL_H

#include "mge/core/ShaderProgram.hpp"
#include "mge/core/Texture.hpp"
#include "mge/materials/LitMaterial.hpp"
#include "SFML/Graphics.hpp"

class StatueMaterial : public AbstractMaterial
{
 public:
        StatueMaterial (Texture* pTexture, Texture* pHighLights, glm::vec3 pModelColor = glm::vec3(1), float pShininess = 10.0f, std::vector<AbstractLight*>* pLights = World::get()->GetLights());
		virtual void render(Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

        void setTexture (Texture* pDiffuseTexture);
		void setHighLight(Texture* pSpecularTexture);

		glm::vec3 getColor();
		void setColor(glm::vec3 pColor);
		void setScore(float pScore);

private:
	static void _lazyInitializeShader();
	void renderLights();
	void renderTextures();

	//score floats
	float _relativeScore;
	float _minHeight;
	float _maxHeight;


	static ShaderProgram* _shader;

	//vertex attributes
	static GLint _aVertex;
	static GLint _aNormal;
	static GLint _aUV;

	//vertex uniforms
	static GLint _uMVPMatrix;
	static GLint _uModelMatrix;

	//fragment uniforms
	static GLint _uHighlight;
	static GLint _uTexture;
	static GLint _uShininess;
	static GLint _uCameraPos;

	//statue uniforms
	static GLint _uScore;
	static GLint _uMinHeight;
	static GLint _uMaxHeight;

	//lights
	std::vector<AbstractLight*>* _lights;

	//settings
	glm::vec3 _modelColor;
	Texture* _texture;
	Texture* _highLight;
	float _shininess;
};

#endif // TEXTUREMATERIAL_H
