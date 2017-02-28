#ifndef TEXTUREMATERIAL_H
#define TEXTUREMATERIAL_H

#include "mge/core/ShaderProgram.hpp"
#include "mge/core/Texture.hpp"
#include "mge/materials/LitMaterial.hpp"


class TextureMaterial : public LitMaterial
{
    public:
        TextureMaterial (Texture* pDiffuseTexture, glm::vec3 pModelColor = glm::vec3(1), float pShininess = 10.0f);
        virtual ~TextureMaterial ();

        void setTexture (Texture* pDiffuseTexture);

    protected:
		virtual ShaderProgram* getShader() override;
		
		virtual void renderPolygons(Mesh* pMesh) override;

    private:
		static ShaderProgram* _shader;

		static GLint _uTexture;

        Texture* _texture;
};

#endif // TEXTUREMATERIAL_H
