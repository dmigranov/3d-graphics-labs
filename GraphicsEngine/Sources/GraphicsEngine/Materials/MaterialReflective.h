#pragma once
#include "GraphicsEngine/Materials/Material.h"



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
};
