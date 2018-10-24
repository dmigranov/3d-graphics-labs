#include "MaterialDiffuse.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Light.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"
#include <iostream>


MaterialDiffuse::MaterialDiffuse()
{
	m_vsFileName = "ShaderDiffuse";
	m_psFileName = "ShaderDiffuse";
}

// TODO: Реализовать переключение Graphics API при нажатии на кнопки (1 - DirectX 11, 2 - OpenGL 2.0, 9 - DirectX 9)
// и отладить на этом механизм использования функций Init() и Deinit()
void MaterialDiffuse::Init()
{
	Material::Init();
	
	// TODO: Нужно при компиляции скопировать папку с шейдерами
	// Google it: "visual studio during build copy files into application folder"
}

void MaterialDiffuse::Deinit()
{
	Material::Deinit();
}

void MaterialDiffuse::SetMaterial(const Object * pObject)
{
	// Заполняем матрицы World, View, Proj
	const Matrix4x4 & matWorld	= SceneUtils::GetMatrixWorld(pObject);
	const Matrix4x4 & matView	= SceneUtils::GetMatrixView();
	const Matrix4x4 & matProj	= SceneUtils::GetMatrixProj();
	
	const Matrix4x4 matWorldViewProjT	= MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);
	const Matrix4x4 matWorldT			= matWorld.Transpose();
	const Matrix4x4 matWorldNormal		= matWorld.Inverse();
	const Vector4 cameraPosition = Vector4(SceneUtils::GetEyePosition(), 1);

	// Получили список всех источников света в сцене
	std::list<const Light *> lights = SceneUtils::GetLights();
	const size_t count = lights.size() < 3 ? lights.size() : 3;

	SetMaterialBegin();
	{
		SetVertexShaderBegin();
		SetVertexShaderMatrix4x4("matrixWorldViewProjT", matWorldViewProjT);
		SetVertexShaderEnd();

		SetPixelShaderBegin();
		SetPixelShaderMatrix4x4	("matWorldNormal",	matWorldNormal);
		SetPixelShaderMatrix4x4	("matWorldT",		matWorldT);
		SetPixelShaderVector4	("materialColor",	Vector4(1, 1, 1, 1));
		SetPixelShaderVector4	("lightsCount",		Vector4(count, 1, 1, 1));
		SetPixelShaderVector4("cameraPos", cameraPosition);
		
		// Передаём параметры каждого источника света
		int i = 0;
		std::list<const Light *>::iterator iter;
		for (iter = lights.begin(); iter != lights.end(); ++iter, ++i)
		{

			const Light * pLight = *iter;
			const Vector4 lightType			= pLight->GetType();
			const Vector4 lightPosition		= Vector4( pLight->GetPosition(), 1 );
			//std::cout << lightPosition.v[0] << " " << lightPosition.v[1] << " " << lightPosition.v[2] << " " << std::endl;
			const Vector4 lightDirection	= Vector4( pLight->GetDirection(), 0 );
			//std::cout << lightDirection.v[0] << " " << lightDirection.v[1] << " " << lightDirection.v[2] << " " << std::endl;
			const Vector4 lightColor		= pLight->GetColor();
			const Vector4 specularPower = Vector4(100, 0, 0, 0);
			const Vector4 attenuation = Vector4(0, 0, 0.1, 0);
			const Vector4 spotlight = Vector4(0.3, 0.1, 1, 0); //(phi, theta, falloff, 0);
			
			//std::cout << std::endl;
			// "lights[i]"
			std::string lightStr = "lights[" + std::to_string(static_cast<long long>(i)) + "]";
			
			// "lights[i].type", "lights[i].position", "lights[i].direction", "lights[i].color"
			SetPixelShaderVector4( (lightStr + ".type").c_str(),		lightType);
			SetPixelShaderVector4( (lightStr + ".position").c_str(),	lightPosition );
			SetPixelShaderVector4( (lightStr + ".direction").c_str(),	lightDirection );
			SetPixelShaderVector4( (lightStr + ".color").c_str(),		lightColor );	
			SetPixelShaderVector4( (lightStr + ".specPower").c_str(), specularPower);
			SetPixelShaderVector4((lightStr + ".att").c_str(), attenuation);
			SetPixelShaderVector4((lightStr + ".spot").c_str(), spotlight);

		}


		SetPixelShaderEnd();
	}
	SetMaterialEnd();
}
