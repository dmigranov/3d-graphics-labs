#include "MaterialReflective.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"


MaterialReflective::MaterialReflective(double height)
{
	m_vsFileName = "ShaderReflective";
	m_psFileName = "ShaderReflective";

	m_pTexture = NULL;
	this->height = height;
}


void MaterialReflective::Init()
{
	Material::Init();

	m_pTexture = new Texture2D("Wall.jpg");
	m_pTexture->SetFilterMode(TEXTURE_FILTER_MODE_ANISOTROPIC);

	//ПРОИНИЦИЛИЗИРОВАТЬ ТЕКСТУРУ?
	//m_pTexture->SetFilterMode(TEXTURE_FILTER_MODE_ANISOTROPIC);
}

void MaterialReflective::Deinit()
{
	delete m_pTexture;
	m_pTexture = NULL;
	Material::Deinit();
}

void MaterialReflective::SetMaterial(const Object * pObject)
{
	// Заполняем матрицы World, View, Proj
	const Matrix4x4 & matWorld = SceneUtils::GetMatrixWorld(pObject);
	const Matrix4x4 & matView = SceneUtils::GetMatrixView();
	const Matrix4x4 & matProj = SceneUtils::GetMatrixProj();

	const Matrix4x4 matWorldViewProjT = MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);

	//я так понимаю, тут надо каждый раз генерировать карту в зависимости от нашего положения
	//нам надо поместить камеру на место объекта (то есть потолка над нами - для этого и нужна высота)

	SetMaterialBegin();
	{
		SetVertexShaderBegin();
		SetVertexShaderMatrix4x4("matrixWorldViewProjT", matWorldViewProjT);
		//SetVertexShaderVector4("constColor", m_color);
		SetVertexShaderEnd();

		SetPixelShaderBegin();
		SetPixelShaderTexture2d("texture1", m_pTexture);
		SetPixelShaderEnd();
	}
	SetMaterialEnd();
}
