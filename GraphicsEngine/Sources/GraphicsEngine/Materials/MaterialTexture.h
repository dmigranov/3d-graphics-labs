#pragma once
#include "GraphicsEngine/Materials/Material.h"
#include "GraphicsEngine/Texture2D.h"


class MaterialTexture : public Material
{
public:
	MaterialTexture(TextureFilterMode filterMode, std::string shaderName, std::string fileName);

	virtual void Init();
	virtual void Deinit();
	
	virtual void SetMaterial(const Object * pObject);

private:
	Texture2D *	m_pTexture1;
	TextureFilterMode m_filterMode;
	std::string fileName;
};
