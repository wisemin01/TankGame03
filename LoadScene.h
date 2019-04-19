#pragma once
#include "Scene.h"


class LoadScene :
	public Scene
{
public:
	bool bLoading = false;

	std::thread loadTh;
public:
	LoadScene();
	virtual ~LoadScene();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	// CREATE ALL THE RESOURCE IN ThreadLoad() FUNCTION
	void ThreadLoad();
};

