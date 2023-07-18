#include "syBackGround.h"
#include "syTransform.h"
#include "syInput.h"
#include "syTime.h"
#include "sySpriteRenderer.h"

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
		GameObject::Initialize();
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