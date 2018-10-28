#pragma once
#include "GraphicsEngine/Materials/Material.h"
#include "GraphicsEngine/Texture2D.h"


class MaterialEarth : public Material
{
public:
	MaterialEarth(); //?
	virtual void Init();

	virtual void Deinit();

	virtual void SetMaterial(const Object * pObject);

private:
	Texture2D *	m_pTexture1;

};
