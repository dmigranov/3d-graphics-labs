#pragma once
#include "GraphicsEngine/Materials/Material.h"
#include <d3d9.h>


class MaterialReflective : public Material
{
public:

	MaterialReflective(double height);

	virtual void Init();

	virtual void Deinit();

	virtual void SetMaterial(const Object * pObject);

private:
	Texture2D *	m_pTexture;
	double height;
	TextureSamplerImpl * m_pTextureSampler;
	LPDIRECT3DDEVICE9 m_pDevice;
	LPDIRECT3DTEXTURE9 m_pTextureD;
};
