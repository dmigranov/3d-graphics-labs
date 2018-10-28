#pragma once
#include "MaterialEarth.h"

#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"


MaterialEarth::MaterialEarth()
{
	m_vsFileName = "ShaderEarth";
	m_psFileName = "ShaderEarth";
	m_pTexture1 = NULL;

}

void MaterialEarth::Init()
{
	Material::Init();
	m_pTexture1 = new Texture2D("Earth_Albedo.jpg");
	m_pTexture1->SetFilterMode(TEXTURE_FILTER_MODE_ANISOTROPIC); //например
	m_pTexture1->SetWrapMode(TEXTURE_WRAP_MODE_REPEAT);

}

void MaterialEarth::Deinit()
{
	Material::Deinit();
}

void MaterialEarth::SetMaterial(const Object * pObject)
{
	// Заполняем матрицы World, View, Proj
	const Matrix4x4 & matWorld = SceneUtils::GetMatrixWorld(pObject);
	const Matrix4x4 & matView = SceneUtils::GetMatrixView();
	const Matrix4x4 & matProj = SceneUtils::GetMatrixProj();

	const Matrix4x4 matWorldViewProjT = MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);

	SetMaterialBegin();
	{
		SetVertexShaderBegin();
		SetVertexShaderMatrix4x4("matrixWorldViewProjT", matWorldViewProjT);
		SetVertexShaderVector4("constColor", Vector4(1, 1, 1, 1));
		SetVertexShaderEnd();

		SetPixelShaderBegin();
		SetPixelShaderTexture2d("texture1", m_pTexture1);
		SetPixelShaderEnd();
	}
	SetMaterialEnd();
}
