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
		virtual void renderPolygons(Mesh* pMesh) override;

		

    private:
		static GLint _uTexture;

        Texture* _texture;
};

#endif // TEXTUREMATERIAL_H
