#pragma once

class GameObject;
class Component
{
public:
	bool bActive = true;
	GameObject* gameObject = nullptr;
public:
	Component();
	virtual ~Component();
	
	virtual void Init() {}
	virtual void Update(float dt) {}
	virtual void Render() {}
	virtual void Destroy() {}
};

