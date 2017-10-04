#include "stdafx.h"
#include "SkyboxMaterial.h"
#include "Rendering/Core/Texture.h"

SkyboxMaterial::SkyboxMaterial() : Material()
{
	m_MaterialDesc.EffectName = "FluxEngine/Resources/Shaders/Skybox.fx";
	m_MaterialDesc.HasWorldMatrix = true;
	m_MaterialDesc.HasWvpMatrix = true;
}
SkyboxMaterial::~SkyboxMaterial()
{
}

void SkyboxMaterial::LoadShaderVariables()
{
	BIND_AND_CHECK_NAME(m_pTextureVar, gSkybox, AsShaderResource);
}

void SkyboxMaterial::UpdateShaderVariables()
{
	m_pTextureVar->SetResource((ID3D11ShaderResourceView*)m_pTexture->GetResourceView());
}