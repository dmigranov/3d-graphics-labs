﻿#pragma once
#include "GraphicsEngine/Materials/Material.h"
#include "GraphicsEngine/Texture2D.h"


class MaterialDirty : public Material
{
public:
	MaterialDirty(TextureFilterMode filterMode);

	virtual void Init();
	virtual void Deinit();
	
	virtual void SetMaterial(const Object * pObject);

private:
	Texture2D *	m_pTexture1;
	TextureFilterMode m_filterMode;
};
