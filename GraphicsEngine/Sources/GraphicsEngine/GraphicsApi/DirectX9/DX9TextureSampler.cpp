#include "DX9TextureSampler.h"
//#include <iostream>

#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9GraphicsEngineContext.h"


DX9TextureSampler::DX9TextureSampler(TextureFilterMode filterMode, TextureWrapMode wrapMode)
{
	const GraphicsEngineContext * pContext = Application::Instance().GetContext();
	const DX9GraphicsEngineContext * pDX9Context = static_cast<const DX9GraphicsEngineContext *>( pContext );
	m_pDevice = pDX9Context->m_pDevice;

	SetFilterMode( filterMode );
	SetWrapMode  ( wrapMode );
}

DX9TextureSampler::~DX9TextureSampler()
{
	
}

void DX9TextureSampler::SetFilterMode(TextureFilterMode filterMode)
{
	m_filterMode = filterMode;

	if (m_filterMode == TEXTURE_FILTER_MODE_POINT)
	{
		m_filterModeDX9 = D3DTEXF_POINT;
		m_useMipMaps = false;
	}
	else if (m_filterMode == TEXTURE_FILTER_MODE_BILINEAR)
	{
		m_filterModeDX9 = D3DTEXF_LINEAR;
		m_useMipMaps = false; //I guess?
	}
	else if (m_filterMode == TEXTURE_FILTER_MODE_TRILINEAR) //билинейная + mipmapping
	{
		m_filterModeDX9 = D3DTEXF_LINEAR;
		m_useMipMaps = true;
	}
	else if (m_filterMode == TEXTURE_FILTER_MODE_ANISOTROPIC)
	{
		m_useAniso = true;
		m_filterModeDX9 = D3DTEXF_ANISOTROPIC;

	}	
}

void DX9TextureSampler::SetWrapMode(TextureWrapMode wrapMode)
{
	m_wrapMode = wrapMode;

	if (m_wrapMode == TEXTURE_WRAP_MODE_CLAMP)
	{
		m_wrapModeDX9 = D3DTADDRESS_CLAMP;
	}
	else if (m_wrapMode == TEXTURE_WRAP_MODE_REPEAT)
	{
		m_wrapModeDX9 = D3DTADDRESS_WRAP;
	}
}

void DX9TextureSampler::PassParamsToShader(int textureRegister, bool toPixelShader) const
{
	//std::cout << toPixelShader << std::endl;
	// https://msdn.microsoft.com/en-us/library/windows/desktop/bb174456(v=vs.85).aspx
	DWORD sampler = textureRegister;

	if (!toPixelShader)
	{
		// https://msdn.microsoft.com/en-us/library/windows/desktop/bb206339(v=vs.85).aspx#Sampling_Stage_Registers
		sampler += D3DVERTEXTEXTURESAMPLER0;
	}
	//во всех этих тудусах делаем IDirect3DDevice9::SetSamplerState(sampler) с разными вторыми аршкментами

	// Set wrap mode (Clamp, Repeat) 
	m_pDevice->SetSamplerState(sampler, D3DSAMP_ADDRESSU, m_wrapModeDX9);
	m_pDevice->SetSamplerState(sampler, D3DSAMP_ADDRESSV, m_wrapModeDX9); //w too?


	// Set filter mode (Point, Bilinear, Trilinear, Anisotropic)
	// TODO: Task05_01
	m_pDevice->SetSamplerState(sampler, D3DSAMP_MAGFILTER, m_filterModeDX9); //по умолчанию point
	m_pDevice->SetSamplerState(sampler, D3DSAMP_MINFILTER, m_filterModeDX9); //по умолчанию point

	
	// Set degree of anisotropic filtering (aniso level)
	if (m_useAniso)
	{
		// TODO: Task05_01
		m_pDevice->SetSamplerState(sampler, D3DSAMP_MAXANISOTROPY, 5); 

	}
	else
	{
		// TODO: Task05_01
		m_pDevice->SetSamplerState(sampler, D3DSAMP_MAXANISOTROPY, 1);
	}
	
	// Enable/Disable mip maps
	if (m_useMipMaps)
	{
		// TODO: Task05_01
		m_pDevice->SetSamplerState(sampler, D3DSAMP_MIPFILTER, m_filterMode);
	}
	else
	{
		// TODO: Task05_01
		m_pDevice->SetSamplerState(sampler, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
	}

	
}

#endif
