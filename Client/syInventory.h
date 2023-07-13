#pragma once
#include "syGameObject.h"

namespace sy
{
	class Inventory : public GameObject
	{
	public:
		Inventory();
		virtual ~Inventory();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}
