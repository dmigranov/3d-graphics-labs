#include "MaterialTexture.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"


MaterialTexture::MaterialTexture(TextureFilterMode filterMode, std::string shaderName, std::string fileName)
{
	m_vsFileName = shaderName; //"ShaderCeil";
	m_psFileName = shaderName;

	this->fileName = fileName;

	m_pTexture1 = NULL;
	m_filterMode = filterMode;
}

void MaterialTexture::Init()
{
	Material::Init();

	//m_pTexture1 = new Texture2D("Wall.jpg");
	m_pTexture1 = new Texture2D(fileName.c_str());
	m_pTexture1->SetFilterMode(m_filterMode);
}

void MaterialTexture::Deinit()
{
	delete m_pTexture1;
	m_pTexture1 = NULL;

	Material::Deinit();
}

void MaterialTexture::SetMaterial(const Object * pObject)
{
	const Matrix4x4 & matWorld	= SceneUtils::GetMatrixWorld(pObject);
	const Matrix4x4 & matView	= SceneUtils::GetMatrixView();
	const Matrix4x4 & matProj	= SceneUtils::GetMatrixProj();
	
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
