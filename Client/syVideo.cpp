#include "syVideo.h"


namespace sy
{
	Video::Video()
		: mSpeed(1.f)
	{
	}

	Video::~Video()
	{
	}

	void Video::Initialize()
	{
		GameObject::Initialize();
	}

	void Video::Update()
	{
		GameObject::Update();
	}

	void Video::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}