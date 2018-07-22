#include "FluxEngine.h"
#include "Renderer.h"
#include "Drawable.h"
#include "Material.h"
#include "Rendering/Core/Graphics.h"
#include "Geometry.h"
#include "Core/ShaderVariation.h"
#include "Camera/Camera.h"
#include "Rendering/Core/Texture.h"
#include "Core/BlendState.h"
#include "Core/RasterizerState.h"
#include "Core/DepthStencilState.h"
#include "Core/VertexBuffer.h"
#include "Core/IndexBuffer.h"

Renderer::Renderer(Context* pContext) :
	Subsystem(pContext) 
{
	m_pGraphics = pContext->GetSubsystem<Graphics>();
	CreateQuadGeometry();
}

Renderer::~Renderer()
{

}

void Renderer::Draw()
{
	m_pCurrentMaterial = nullptr;
	m_pCurrentCamera = nullptr;

	for (Drawable* pDrawable : m_Drawables)
	{
		pDrawable->Update();
	}

	m_OnPreRender.Broadcast();

	std::vector<Camera*> cameras = m_CameraQueue;
	m_CameraQueue.clear();
	for (Camera* pCamera : m_Cameras)
	{
		cameras.push_back(pCamera);
	}
		
	for (Camera* pCamera : cameras)
	{
		if (pCamera == nullptr)
		{
			continue;
		}

		m_pGraphics->SetRenderTarget(0, pCamera->GetRenderTarget());
		m_pGraphics->SetDepthStencil(pCamera->GetDepthStencil());
		m_pGraphics->SetViewport(pCamera->GetViewport());
		m_pGraphics->Clear(pCamera->GetClearFlags(), pCamera->GetClearColor(), 1.0f, 1);

		m_pCurrentMaterial = nullptr;

		for (Drawable* pDrawable : m_Drawables)
		{
			if (pDrawable == nullptr)
			{
				continue;
			}
			if (!pDrawable->DrawEnabled())
			{
				continue;
			}
			if (pDrawable->GetCullingEnabled() && !pCamera->GetFrustum().Intersects(pDrawable->GetWorldBoundingBox()))
			{
				continue;
			}

			const std::vector<Batch>& batches = pDrawable->GetBatches();
			for (const Batch& batch : batches)
			{
				if (batch.pGeometry == nullptr || batch.pMaterial == nullptr)
				{
					continue;
				}

				SetPerMaterialParameters(batch.pMaterial);
				SetPerBatchParameters(batch, pCamera);
				SetPerFrameParameters();
				SetPerCameraParameters(pCamera);

				batch.pGeometry->Draw(m_pGraphics);
			}
		}
	}
}

void Renderer::AddDrawable(Drawable* pDrawable)
{
	m_Drawables.push_back(pDrawable);
}

void Renderer::RemoveDrawable(Drawable* pDrawable)
{
	m_Drawables.erase(std::remove(m_Drawables.begin(), m_Drawables.end(), pDrawable), m_Drawables.end());
}

void Renderer::AddCamera(Camera* pCamera)
{
	m_Cameras.push_back(pCamera);
	std::sort(m_Cameras.begin(), m_Cameras.end(), [](Camera* pA, Camera* pB) {return pA->GetRenderOrder() > pB->GetRenderOrder(); });
}

void Renderer::RemoveCamera(Camera* pCamera)
{
	m_Cameras.erase(std::remove(m_Cameras.begin(), m_Cameras.end(), pCamera), m_Cameras.end());
}

void Renderer::QueueCamera(Camera * pCamera)
{
	m_CameraQueue.push_back(pCamera);
}

void Renderer::CreateQuadGeometry()
{
	m_pQuadVertexBuffer = std::make_unique<VertexBuffer>(m_pGraphics);
	std::vector<VertexElement> elements = {
		VertexElement(VertexElementType::FLOAT3, VertexElementSemantic::POSITION, 0, false)
	};
	m_pQuadVertexBuffer->Create(4, elements);
	Vector3 vertices[] = {
		Vector3(-1.0f, 1.0f, 0.0f),
		Vector3(1.0f, 1.0f, 0.0f),
		Vector3(1.0f, -1.0f, 0.0f),
		Vector3(-1.0f, -1.0f, 0.0f),
	};
	m_pQuadVertexBuffer->SetData(vertices);

	m_pQuadIndexBuffer = std::make_unique<IndexBuffer>(m_pGraphics);
	m_pQuadIndexBuffer->Create(6, false, false);
	int indices[] = {
		0, 1, 2,
		0, 2, 3
	};
	m_pQuadIndexBuffer->SetData(indices);

	m_pQuadGeometry = std::make_unique<Geometry>();
	m_pQuadGeometry->SetIndexBuffer(m_pQuadIndexBuffer.get());
	m_pQuadGeometry->SetVertexBuffer(m_pQuadVertexBuffer.get());
	m_pQuadGeometry->SetDrawRange(PrimitiveType::TRIANGLELIST, 6, 4);
}

void Renderer::SetPerFrameParameters()
{
	int frame = GameTimer::Ticks();
	if (frame != m_CurrentFrame)
	{
		m_CurrentFrame = frame;
		m_pGraphics->SetShaderParameter("cDeltaTime", GameTimer::DeltaTime());
		m_pGraphics->SetShaderParameter("cElapsedTime", GameTimer::GameTime());
		m_LightPosition.Normalize(m_LightDirection);
		m_LightDirection *= -1;
		m_pGraphics->SetShaderParameter("cLightDirection", m_LightDirection);
	}
}

void Renderer::SetPerCameraParameters(Camera* pCamera)
{
	m_pCurrentCamera = pCamera;
	m_pGraphics->SetShaderParameter("cViewProj", pCamera->GetViewProjection());
	m_pGraphics->SetShaderParameter("cView", pCamera->GetView());
	m_pGraphics->SetShaderParameter("cViewInverse", pCamera->GetViewInverse());
	m_pGraphics->SetShaderParameter("cNearClip", pCamera->GetNearPlane());
	m_pGraphics->SetShaderParameter("cFarClip", pCamera->GetFarPlane());
}

void Renderer::SetPerMaterialParameters(const Material* pMaterial)
{
	if (pMaterial == m_pCurrentMaterial)
		return;
	m_pCurrentMaterial = pMaterial;

	for (int i = 0; i < (int)ShaderType::MAX; ++i)
		m_pGraphics->SetShader((ShaderType)i, m_pCurrentMaterial->GetShader((ShaderType)i));

	const auto& pParameters = m_pCurrentMaterial->GetShaderParameters();
	for (const auto& pParameter : pParameters)
	{
		m_pGraphics->SetShaderParameter(pParameter.first, pParameter.second.GetData());
	}

	const auto& pTextures = m_pCurrentMaterial->GetTextures();
	for (const auto& pTexture : pTextures)
	{
		m_pGraphics->SetTexture(pTexture.first, pTexture.second);
	}

	//Blend state
	m_pGraphics->GetBlendState()->SetBlendMode(m_pCurrentMaterial->GetBlendMode(), m_pCurrentMaterial->GetAlphaToCoverage());
	
	//Rasterizer state
	m_pGraphics->GetRasterizerState()->SetCullMode(m_pCurrentMaterial->GetCullMode());
	m_pGraphics->GetRasterizerState()->SetFillMode(m_pCurrentMaterial->GetFillMode());
	
	//Depth stencil state
	m_pGraphics->GetDepthStencilState()->SetDepthTest(m_pCurrentMaterial->GetDepthTestMode());
	m_pGraphics->GetDepthStencilState()->SetDepthEnabled(m_pCurrentMaterial->GetDepthEnabled());
	m_pGraphics->GetDepthStencilState()->SetDepthWrite(m_pCurrentMaterial->GetDepthWrite());
}

void Renderer::SetPerBatchParameters(const Batch& batch, Camera* pCamera)
{
	if (batch.NumSkinMatrices > 1)
	{
		m_pGraphics->SetShaderParameter("cSkinMatrices", batch.pSkinMatrices, sizeof(Matrix), batch.NumSkinMatrices);
	}
	m_pGraphics->SetShaderParameter("cWorld", *batch.pModelMatrix);
	Matrix wvp = *batch.pModelMatrix * pCamera->GetViewProjection();
	m_pGraphics->SetShaderParameter("cWorldViewProj", wvp);
}