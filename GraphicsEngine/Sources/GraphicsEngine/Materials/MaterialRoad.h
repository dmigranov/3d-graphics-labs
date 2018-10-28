#pragma once
#include "GraphicsEngine/Materials/Material.h"
#include "GraphicsEngine/Texture2D.h"


class MaterialRoad : public Material
{
public:
	MaterialRoad(); //?
	virtual void Init();

	virtual void Deinit();

	virtual void SetMaterial(const Object * pObject);

private:
	Texture2D *	m_pTexture1;
	Texture2D *	m_pTexture2;
	Texture2D *	m_pTexture3;
};
