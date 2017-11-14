#include "stdafx.h"
#include "RenderTarget.h"
#include "Texture.h"
#include "Graphics.h"

#ifdef D3D11
#include "D3D11/D3D11RenderTarget.hpp"
#endif

RenderTarget::RenderTarget(Graphics* pGraphics) :
	m_pGraphics(pGraphics)
{
}

RenderTarget::~RenderTarget()
{
}

bool RenderTarget::Create(const RenderTargetDesc& RenderTargetDesc)
{
	AUTOPROFILE(RenderTarget_Create);

	if (!ValidateDesc(RenderTargetDesc))
		return false;

	m_pRenderTexture.reset();
	m_pDepthTexture.reset();
	m_pRenderTexture = make_unique<Texture>(m_pGraphics);
	if (!m_pRenderTexture->SetSize(RenderTargetDesc.Width, RenderTargetDesc.Height, RenderTargetDesc.ColorFormat, TextureUsage::RENDERTARGET, RenderTargetDesc.MultiSample, RenderTargetDesc.pColorResource))
		return false;

	m_pDepthTexture = make_unique<Texture>(m_pGraphics);
	if (!m_pDepthTexture->SetSize(RenderTargetDesc.Width, RenderTargetDesc.Height, RenderTargetDesc.DepthFormat, TextureUsage::DEPTHSTENCILBUFFER, RenderTargetDesc.MultiSample, RenderTargetDesc.pDepthResource))
		return false;

	return true;
}

bool RenderTarget::ValidateDesc(const RenderTargetDesc& desc) const
{
	if (desc.Width < 0 || desc.Height < 0)
	{
		FLUX_LOG(ERROR, "[RenderTarget::ValidateDesc] > RenderTarget dimensions (%i x %i) invalid", desc.Width, desc.Height);
		return false;
	}
	if (!desc.ColorBuffer && !desc.DepthBuffer)
	{
		FLUX_LOG(ERROR, "[RenderTarget::ValidateDesc] > RenderTarget needs at least one buffer to create");
		return false;
	}
	if (desc.MultiSample < 1)
	{
		FLUX_LOG(ERROR, "[RenderTarget::ValidateDesc] > MSAA Sample count has to be at least 1 (is %i)", desc.MultiSample);
		return false;
	}
	return true;
}
