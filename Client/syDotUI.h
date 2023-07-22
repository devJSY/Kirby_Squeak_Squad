#pragma once
#include "syUI.h"

namespace sy
{
    class DotUI : public UI
    {
	public:
		DotUI();
		virtual ~DotUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
    };
}

