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

		//SpriteRenderer* sr = GetComponent<SpriteRenderer>();

		//float alpha = sr->GetAlpha();
		//alpha -= 0.2f * Time::DeltaTime();
		//sr->SetAlpha(alpha);
	}

	void BackGround::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}