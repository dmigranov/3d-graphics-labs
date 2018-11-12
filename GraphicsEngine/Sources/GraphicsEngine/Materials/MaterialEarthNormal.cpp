#pragma once
#include "MaterialEarthNormal.h"

#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"
#include "GraphicsEngine/Light.h"


MaterialEarthNormal::MaterialEarthNormal()
{
	m_vsFileName = "ShaderEarthNormal";
	m_psFileName = "ShaderEarthNormal";
	m_pTexture = NULL;
	m_pNormalMap = NULL;

}

void MaterialEarthNormal::Init()
{
	Material::Init();
	m_pTexture = new Texture2D("Earth_Albedo.jpg");
	m_pTexture->SetFilterMode(TEXTURE_FILTER_MODE_ANISOTROPIC);
	m_pNormalMap = new Texture2D("Earth_NormalMap.jpg");
	m_pNormalMap->SetFilterMode(TEXTURE_FILTER_MODE_ANISOTROPIC);

}

void MaterialEarthNormal::Deinit()
{
	Material::Deinit();
}

void MaterialEarthNormal::SetMaterial(const Object * pObject)
{
	// «аполн€ем матрицы World, View, Proj
	const Matrix4x4 & matWorld = SceneUtils::GetMatrixWorld(pObject);
	const Matrix4x4 & matView = SceneUtils::GetMatrixView();
	const Matrix4x4 & matProj = SceneUtils::GetMatrixProj();

	const Matrix4x4 matWorldViewProjT = MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);
	const Matrix4x4 matWorldT = matWorld.Transpose();
	const Matrix4x4 matWorldNormal = matWorld.Inverse();

	std::list<const Light *> lights = SceneUtils::GetLights();
	const Vector4 cameraPosition = Vector4(SceneUtils::GetEyePosition(), 1);
	const Vector4 specularPower = Vector4(100, 0, 0, 0);
	const Light * pLight = SceneUtils::GetLights().front();
	const Vector4 lightDirection = Vector4(pLight->GetDirection(), 0);
	SetMaterialBegin();
	{
		SetVertexShaderBegin();
		SetVertexShaderMatrix4x4("matrixWorldViewProjT", matWorldViewProjT);
		SetVertexShaderVector4("constColor", Vector4(1, 1, 1, 1));
		SetVertexShaderEnd();

		SetPixelShaderBegin();

		SetPixelShaderMatrix4x4("matWorldNormal", matWorldNormal);
		SetPixelShaderMatrix4x4("matWorldT", matWorldT);
		SetPixelShaderVector4("cameraPos", cameraPosition);
		SetPixelShaderVector4("direction", lightDirection);
		SetPixelShaderVector4("color", Vector4(1, 1, 1, 1));
		SetPixelShaderVector4("specPower", specularPower);

		//передать остальные


		SetPixelShaderTexture2d("nmap", m_pNormalMap);
		SetPixelShaderTexture2d("tex", m_pTexture);

		SetPixelShaderEnd();
	}
	SetMaterialEnd();
}
