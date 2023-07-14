#pragma once
#include "syUI.h"

namespace sy
{
	class AbilityUI :
		public UI
	{
	public:
		AbilityUI();
		virtual ~AbilityUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
	};
}