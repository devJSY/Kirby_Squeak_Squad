#include "syDotUI.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "sySpriteRenderer.h"

namespace sy
{
	DotUI::DotUI()
	{
	}

	DotUI::~DotUI()
	{
	}

	void DotUI::Initialize()
	{
		Texture* Tex = ResourceManager::Load<Texture>(L"Dot", L"..\\Resources\\UI\\Dot.bmp");
		SpriteRenderer* renderer = AddComponent<SpriteRenderer>();
		renderer->SetTexture(Tex);

		UI::Initialize();
	}

	void DotUI::Update()
	{
		UI::Update();
	}

	void DotUI::Render(HDC hdc)
	{
		UI::Render(hdc);
	}
}