#include <iostream>

#include "MaterialReflective.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9GraphicsEngineContext.h"
#include "GraphicsEngine/GraphicsApi/TextureSamplerImpl.h"
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9TextureSampler.h"


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

	//m_pTexture = new Texture2D("Wall.jpg");
	//m_pTexture->SetFilterMode(TEXTURE_FILTER_MODE_ANISOTROPIC);

	const GraphicsEngineContext * pContext = Application::Instance().GetContext();
	const DX9GraphicsEngineContext * pDX9Context = static_cast<const DX9GraphicsEngineContext *>(pContext);
	m_pDevice = pDX9Context->m_pDevice;

	
	std::cout << D3DXCreateTextureFromFileA(m_pDevice, "../Data/Wall.jpg", &m_pTextureD) << std::endl;
	m_pTextureSampler = new DX9TextureSampler(TEXTURE_FILTER_MODE_POINT, TEXTURE_WRAP_MODE_REPEAT);

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

		//SetPixelShaderTexture2d("texture1", m_pTexture);
		DWORD sampler = 0;

	
		HRESULT hr = m_pDevice->SetTexture(sampler, m_pTextureD);

		m_pTextureSampler->PassParamsToShader(0, 1);

		SetPixelShaderEnd();
	}
	SetMaterialEnd();
}
