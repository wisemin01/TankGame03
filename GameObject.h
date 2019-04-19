#pragma once

class Component;

class Transform;
class Renderer;
class Collider;
class Rigidbody;
class Life;

class GameObject
{
public:
	list<Component*> listCom;

	int iLayer				= 0;
	bool bLive				= true;
	bool bScreen			= true;
	bool bActive			= true;

	Transform*	transform	= nullptr;
	Renderer*	renderer	= nullptr;
	Collider*	collider	= nullptr;
	Rigidbody*	rigidbody	= nullptr;
	Life*		life		= nullptr;

	string		tag;

public:
	GameObject();
	virtual ~GameObject();

	template <class T>
	T* AddComponent()
	{
		T* com = new T;
		com->gameObject = this;
		com->Init();
	
		listCom.push_back(com);
		return com;
	}

	template <class T>
	T* GetComponent()
	{
		for (auto iter : listCom)
		{
			if (typeid(*iter).name() == typeid(T).name())
				return iter;
		}
		return nullptr;
	}

	virtual void Init() {}
	virtual void Update(float dt) {}
	virtual void Render() {}
	virtual void Destroy() {}

	void ComUpdate(float dt);
	void ComRender();
	void ComDestroy();

	virtual void Kill() { bLive = false; }

private:
	friend class ObjectManager;
	bool bDeleteCheck = false;
};

