#include "MaterialDirty.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9GraphicsEngineContext.h"

#include <d3d9.h>


MaterialDirty::MaterialDirty(TextureFilterMode filterMode)
{
	m_vsFileName = "ShaderDirt";
	m_psFileName = "ShaderDirt";

	m_pTexture1 = NULL;
	m_filterMode = filterMode;
}

void MaterialDirty::Init()
{
	Material::Init();

	m_pTexture1 = new Texture2D("dirt.png");
	m_pTexture1->SetFilterMode(m_filterMode);
}

void MaterialDirty::Deinit()
{
	delete m_pTexture1;
	m_pTexture1 = NULL;

	Material::Deinit();
}

void MaterialDirty::SetMaterial(const Object * pObject)
{
	const Matrix4x4 & matWorld	= SceneUtils::GetMatrixWorld(pObject);
	const Matrix4x4 & matView	= SceneUtils::GetMatrixView();
	const Matrix4x4 & matProj	= SceneUtils::GetMatrixProj();
	
	const Matrix4x4 matWorldViewProjT = MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);


	
	//yes, this is bad...
	/*const GraphicsEngineContext * pContext = Application::Instance().GetContext();
	const DX9GraphicsEngineContext * pDX9Context = static_cast<const DX9GraphicsEngineContext *>(pContext);
	LPDIRECT3DDEVICE9 m_pDevice = pDX9Context->m_pDevice;
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);*/

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
