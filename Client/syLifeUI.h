#pragma once
#include "syUI.h"

namespace sy
{
	class LifeUI :
		public UI
	{
	public:
		LifeUI();
		virtual ~LifeUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}
