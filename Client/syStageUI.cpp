#include "syStageUI.h"

namespace sy
{
	StageUI::StageUI()
	{
	}

	StageUI::~StageUI()
	{
	}

	void StageUI::Initialize()
	{
		UI::Initialize();
	}

	void StageUI::Update()
	{
		UI::Update();
	}

	void StageUI::Render(HDC hdc)
	{
		UI::Render(hdc);
	}
}