#include "MaterialCylinderMorphing.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"
#include "GraphicsEngine/Time.h"
#include <iostream>


MaterialCylinderMorphing::MaterialCylinderMorphing()
{
	m_vsFileName = "ShaderCylinderMorphing";
	m_psFileName = "ShaderCylinderMorphing"; //does it use ps or vs files?
}

// TODO: Реализовать переключение Graphics API при нажатии на кнопки (1 - DirectX 11, 2 - OpenGL 2.0, 9 - DirectX 9)
// и отладить на этом механизм использования функций Init() и Deinit()
void MaterialCylinderMorphing::Init()
{
	Material::Init();

	// TODO: Нужно при компиляции скопировать папку с шейдерами
	// Google it: "visual studio during build copy files into application folder"
}

void MaterialCylinderMorphing::Deinit()
{
	Material::Deinit();
}

void MaterialCylinderMorphing::SetMaterial(const Object * pObject)
{
	// Заполняем матрицы World, View, Proj
	const Matrix4x4 & matWorld = SceneUtils::GetMatrixWorld(pObject);
	const Matrix4x4 & matView = SceneUtils::GetMatrixView();
	const Matrix4x4 & matProj = SceneUtils::GetMatrixProj();

	const Matrix4x4 matWorldViewProjT = MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);
	Matrix4x4 upper, lower;
	/*upper = {
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	};*/
	for(int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			upper.m[i][j] = (i == j);
			lower.m[i][j] = 
		}


	SetMaterialBegin();
	{
		SetVertexShaderBegin();
		SetVertexShaderMatrix4x4("matrixWorldViewProjT", matWorldViewProjT);
		//SetVertexShaderVector4("time", Vector4(abs(sin(Time::GetTime())), 0, 0, 0));
		SetVertexShaderMatrix4x4("lower");
		SetVertexShaderMatrix4x4("upper");
		SetVertexShaderVector4("materialColor", Vector4(1, 1, 1, 1));

		

		
		//std::cout << abs(sin(Time::GetTime())) << " ";
		//SetVertexShaderVector4("timeVector", Vector4()); //time
		SetVertexShaderEnd();

		SetPixelShaderBegin();
		SetPixelShaderEnd();
	}
	SetMaterialEnd();
}
