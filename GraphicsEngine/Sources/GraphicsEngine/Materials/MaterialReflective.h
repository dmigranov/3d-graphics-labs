#pragma once
#include "GraphicsEngine/Materials/Material.h"



class MaterialReflective : public Material
{
public:

	MaterialReflective();

	virtual void Init();

	virtual void Deinit();

	virtual void SetMaterial(const Object * pObject);

private:

};
