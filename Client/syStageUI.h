#pragma once
#include "syUI.h"

namespace sy
{
	class StageUI : public UI
	{
	public:
		StageUI();
		virtual ~StageUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}
