#include "FluxEngine.h"
#include "AnimatedModel.h"
#include "Rendering/Mesh.h"
#include "Scenegraph/SceneNode.h"
#include "Animation.h"
#include "Rendering/Core/GraphicsDefines.h"

AnimatedModel::AnimatedModel(Context* pContext):
	Model(pContext)
{
}

AnimatedModel::~AnimatedModel()
{
}

void AnimatedModel::Update()
{
	m_AnimationStates[0].Apply(m_SkinMatrices);
	for (size_t i = 0; i < m_SkinMatrices.size(); ++i)
	{
		Vector3 position, scale;
		Quaternion rotation;
		m_SkinMatrices[i].Decompose(scale, rotation, position);
		m_SkinQuaternions[i] = DualQuaternion(rotation, position);
	}
}

void AnimatedModel::SetMesh(Mesh* pMesh)
{
	checkf(m_pNode, "[AnimatedModel::SetMesh] Cannot set mesh when component is not attached to a node");
	checkf(pMesh->GetSkeleton().BoneCount() < GraphicsConstants::MAX_BONES, "[AnimatedModel::SetMesh] The given skeleton has more bones than allowed");

	const int geometries = pMesh->GetGeometryCount();
	m_Batches.resize(geometries);
	m_SkinMatrices.resize(pMesh->GetSkeleton().BoneCount());
	m_SkinQuaternions.resize(pMesh->GetSkeleton().BoneCount());
	for (int i = 0; i < geometries; ++i)
	{
		m_Batches[i].pGeometry = pMesh->GetGeometry(i);
		m_Batches[i].pModelMatrix = &m_pNode->GetWorldMatrix();
		m_Batches[i].pSkinMatrices = m_SkinMatrices.data();
		m_Batches[i].NumSkinMatrices = (int)m_SkinMatrices.size();
		m_Batches[i].pSkinDualQuaternions = m_SkinQuaternions.data();
	}
	m_BoundingBox = pMesh->GetBoundingBox();

	m_pMesh = pMesh;
}

const Skeleton& AnimatedModel::GetSkeleton() const
{
	return m_pMesh->GetSkeleton();
}

AnimationState* AnimatedModel::AddAnimationState(Animation* pAnimation)
{
	m_AnimationStates.push_back(AnimationState(pAnimation, this));
	return &m_AnimationStates.back();
}

void AnimatedModel::RemoveAnimationState(AnimationState* pAnimation)
{
	m_AnimationStates.erase(std::remove_if(m_AnimationStates.begin(), m_AnimationStates.end(), [pAnimation](const AnimationState& a) {return &a == pAnimation; }), m_AnimationStates.end());
}

AnimationState* AnimatedModel::GetAnimationState(const StringHash hash)
{
	for (AnimationState& state : m_AnimationStates)
	{
		if (state.GetAnimation()->GetNameHash() == hash)
		{
			return &state;
		}
	}
	return nullptr;
}
