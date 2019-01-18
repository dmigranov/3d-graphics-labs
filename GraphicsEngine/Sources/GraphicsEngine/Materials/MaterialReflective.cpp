#include <iostream>

#include "MaterialReflective.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9GraphicsEngineContext.h"
#include "GraphicsEngine/GraphicsApi/TextureSamplerImpl.h"
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9TextureSampler.h"

#include "GraphicsEngine/GraphicsEngine.h"


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
	{
		//yes, this is bad...
		const GraphicsEngineContext * pContext = Application::Instance().GetContext();
		const DX9GraphicsEngineContext * pDX9Context = static_cast<const DX9GraphicsEngineContext *>(pContext);
		m_pDevice = pDX9Context->m_pDevice;
		D3DXCreateTextureFromFileA(m_pDevice, "../Data/Wall.jpg", &m_pTextureD);

		std::cout << D3DXCreateCubeTexture(m_pDevice, 256, 1, D3DUSAGE_RENDERTARGET, D3DFMT_R8G8B8, D3DPOOL_DEFAULT, &m_pCubeMap) << std::endl;
		//TODO: надо ещё проинициализировать!
		//но наверное это надо каждый раз заново


		m_pTextureSampler = new DX9TextureSampler(TEXTURE_FILTER_MODE_POINT, TEXTURE_WRAP_MODE_REPEAT);
	}

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

	D3DXMATRIX matProjSave, matViewSave;
	m_pDevice->GetTransform(D3DTS_VIEW, &matViewSave);
	m_pDevice->GetTransform(D3DTS_PROJECTION, &matProjSave);

	LPDIRECT3DSURFACE9 pBackBuffer, pZBuffer;
	m_pDevice->GetRenderTarget(0, &pBackBuffer); //0 - index of the render target?
	m_pDevice->GetDepthStencilSurface(&pZBuffer);

	D3DXMATRIX matProjD;
	D3DXMatrixPerspectiveFovLH(&matProjD, D3DX_PI/2, 1.0f, 0.5f, 1000.0f);
	m_pDevice->SetTransform(D3DTS_PROJECTION, &matProjD);

	for (DWORD i = 0; i < 6; i++)
	{
		D3DXVECTOR3 vEnvEyePt = { 0.0f, 0.0f, 0.0f };
		D3DXVECTOR3 vLookatPt, vUpVec;
		switch (i)
		{
		case D3DCUBEMAP_FACE_POSITIVE_X:
			vLookatPt = { 1.0f, 0.0f, 0.0f };
			vUpVec = { 0.0f, 1.0f, 0.0f };
			break;
		case D3DCUBEMAP_FACE_NEGATIVE_X:
			vLookatPt = { -1.0f, 0.0f, 0.0f };
			vUpVec = { 0.0f, 1.0f, 0.0f };
			break;
		case D3DCUBEMAP_FACE_POSITIVE_Y:
			vLookatPt = { 0.0f, 1.0f, 0.0f };
			vUpVec = { 0.0f, 0.0f, -1.0f };
			break;
		case D3DCUBEMAP_FACE_NEGATIVE_Y:
			vLookatPt = { 0.0f, -1.0f, 0.0f };
			vUpVec = { 0.0f, 0.0f, 1.0f };
			break;
		case D3DCUBEMAP_FACE_POSITIVE_Z:
			vLookatPt = { 0.0f, 0.0f, 1.0f };
			vUpVec = { 0.0f, 1.0f, 0.0f };
			break;
		case D3DCUBEMAP_FACE_NEGATIVE_Z:
			vLookatPt = { 0.0f, 0.0f, 01.0f };
			vUpVec = { 0.0f, 1.0f, -.0f };
			break;
		}

		D3DXMATRIX matViewD;
		D3DXMatrixLookAtLH(&matViewD, &vEnvEyePt, &vLookatPt, &vUpVec);
		m_pDevice->SetTransform(D3DTS_VIEW, &matViewD);

		//переместились теперь делаем снимок
		LPDIRECT3DSURFACE9 pFace;
		m_pCubeMap->GetCubeMapSurface((D3DCUBEMAP_FACES)i, 0, &pFace);
		m_pDevice->SetRenderTarget(0, pFace);  //(pFace, pZBuffer)
		SAFE_RELEASE(pFace);

		//render scene!
		
	}

	m_pDevice->SetRenderTarget(0, pBackBuffer); //(pBackBuffer, pZBuffer)
	SAFE_RELEASE(pBackBuffer);
	SAFE_RELEASE(pZBuffer);

	m_pDevice->SetTransform(D3DTS_VIEW, &matViewSave);
	m_pDevice->SetTransform(D3DTS_PROJECTION, &matProjSave);

	SetMaterialBegin();
	{
		SetVertexShaderBegin();
		SetVertexShaderMatrix4x4("matrixWorldViewProjT", matWorldViewProjT);
		//SetVertexShaderVector4("constColor", m_color);
		SetVertexShaderEnd();

		SetPixelShaderBegin();

		//SetPixelShaderTexture2d("texture1", m_pTexture);
		{
			DWORD sampler = 0;
			HRESULT hr = m_pDevice->SetTexture(sampler, m_pTextureD);
			m_pTextureSampler->PassParamsToShader(0, 1);
		}

		SetPixelShaderEnd();
	}
	SetMaterialEnd();
}
