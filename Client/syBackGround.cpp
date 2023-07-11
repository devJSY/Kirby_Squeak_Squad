#include "syBackGround.h"

namespace sy
{
	BackGround::BackGround()
	{
	}

	BackGround::~BackGround()
	{
	}

	void BackGround::Initialize()
	{
	}

	void BackGround::Update()
	{
		GameObject::Update();
	}

	void BackGround::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}