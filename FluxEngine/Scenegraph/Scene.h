#pragma once
#include "SceneGraph\SceneNode.h"

class SceneNode;
class Drawable;
class Graphics;
class Renderer;
class Component;
class Camera;

class Scene : public SceneNode
{
	FLUX_OBJECT(Scene, SceneNode);

public:
	Scene(Context* pContext);
	virtual ~Scene();

	virtual void Initialize();
	void Update();

	void AddChild(SceneNode* pNode);
	Renderer* GetRenderer() const { return m_pRenderer; }
	Camera* GetCamera() const;

	SceneNode* FindNode(const std::string& name);

	virtual void OnSceneSet(Scene* pScene) override;

	MulticastDelegate<>& OnSceneUpdate() { return m_OnSceneUpdate; }
	
private:
	Renderer* m_pRenderer;
	std::vector<SceneNode*> m_Nodes;

	MulticastDelegate<> m_OnSceneUpdate;
};