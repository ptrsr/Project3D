#include <glm.hpp>

#include "mge/materials/TextureMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/config.hpp"

//uniforms
GLint TextureMaterial::_uTexture = 0;

TextureMaterial::TextureMaterial(Texture* pTexture, glm::vec3 pModelColor = glm::vec3(1), float pShininess = 10.0f)
	: LitMaterial("litTexture", pModelColor, pShininess), _texture(pTexture)
{ 
	_uTexture = _shader->getUniformLocation("dTexture");
}


void TextureMaterial::setTexture (Texture* pTexture) {
    _texture = pTexture;
}

void TextureMaterial::renderPolygons(Mesh* pMesh)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture->getId());
	glUniform1i(_uTexture, 0);

	pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}

TextureMaterial::~TextureMaterial() {}
