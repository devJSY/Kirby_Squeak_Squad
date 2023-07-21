#pragma once
#include "syUI.h"

namespace sy
{
    class PlacardUI : public UI
    {
	public:
		PlacardUI();
		virtual ~PlacardUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
    };


}
