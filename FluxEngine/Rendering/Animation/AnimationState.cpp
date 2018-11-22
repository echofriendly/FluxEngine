#include "FluxEngine.h"
#include "AnimationState.h"
#include "Animation.h"
#include "AnimatedModel.h"
#include "Skeleton.h"

void AnimationKeyState::GetFrameIndex(float time, int& index) const
{
	if (time < 0.0f)
	{
		time = 0.0f;
	}
	if (index >= (int)pNode->Keys.size())
	{
		index = (int)pNode->Keys.size() - 1;
	}

	while (index && time < pNode->Keys[index].Time)
	{
		--index;
	}
	while (index < (int)pNode->Keys.size() - 1 && time >= pNode->Keys[index + 1].Time)
	{
		++index;
	}
}

void AnimationKeyState::GetMatrix(float time, Matrix& matrix)
{
	if (pNode->Keys.size() == 0)
	{
		matrix = Matrix::Identity;
		return;
	}

	GetFrameIndex(time, KeyFrame);
	int nextFrame = KeyFrame + 1;
	if (nextFrame >= (int)pNode->Keys.size())
	{
		nextFrame = 0;
	}

	const AnimationKey& key = pNode->Keys[KeyFrame].Key;
	const AnimationKey& nextKey = pNode->Keys[nextFrame].Key;

	float t = time > 0.0f ? (time - pNode->Keys[KeyFrame].Time) / (pNode->Keys[nextFrame].Time - pNode->Keys[KeyFrame].Time) : 1.0f;

	const Vector3 position = Vector3::Lerp(key.Position, nextKey.Position, t);
	const Vector3 scale = Vector3::Lerp(key.Scale, nextKey.Scale, t);
	const Quaternion rotation = Quaternion::Slerp(key.Rotation, nextKey.Rotation, t);
	matrix = Matrix::CreateScale(scale) * Matrix::CreateFromQuaternion(rotation) * Matrix::CreateTranslation(position);
}

AnimationState::AnimationState(Animation* pAnimation, AnimatedModel* pModel)
	: m_pAnimation(pAnimation)
{
	m_pSkeleton = &pModel->GetSkeleton();
	for (const AnimationNode& node : pAnimation->GetNodes())
	{
		AnimationKeyState state;
		state.KeyFrame = 0;
		state.pBone = m_pSkeleton->GetBone(node.BoneIndex);
		state.pNode = &node;
		checkf(state.pBone->Name == state.pNode->Name, "[AnimationState::AnimationState] The name of the node and the bone should match");
		m_KeyStates.push_back(state);
	}
}

void AnimationState::AddTime(float time)
{
	float duration = GetDuration();
	if (duration == 0.0f || time == 0.0f)
	{
		return;
	}

	if (m_Looped)
	{
		m_Time = fmodf(m_Time + time, duration / GetAnimation()->GetTicksPerSecond());
	}
	else if (m_Time > duration)
	{
		return;
	}
	else
	{
		m_Time += time;
	}
	m_IsDirty = true;
}

void AnimationState::SetTime(float time)
{
	m_Time = time;
	m_IsDirty = true;
}

void AnimationState::Apply(std::vector<Matrix>& skinMatrices)
{
	if (m_IsDirty)
	{
		CalculateAnimations(m_pSkeleton->GetRootBoneIndex(), Matrix(), skinMatrices);
		m_IsDirty = false;
	}
}

float AnimationState::GetDuration() const
{
	return m_pAnimation ? m_pAnimation->GetDurationInTicks() : 0.0f;
}

void AnimationState::CalculateAnimations(const int boneIndex, const Matrix& parentMatrix, std::vector<Matrix>& skinMatrices)
{
	float time = m_Time * m_pAnimation->GetTicksPerSecond();

	const Bone* pBone = m_pSkeleton->GetBone(boneIndex);

	//ASSUMPTION: The bone index matches the node index
	AnimationKeyState& state = m_KeyStates[boneIndex];
	Matrix m;
	if (m_KeyStates.size() != 0)
	{
		state.GetMatrix(time, m);
	}
	skinMatrices[boneIndex] = pBone->OffsetMatrix * m * parentMatrix;

	for (int childIndex : pBone->Children)
	{
		CalculateAnimations(childIndex, m * parentMatrix, skinMatrices);
	}
}