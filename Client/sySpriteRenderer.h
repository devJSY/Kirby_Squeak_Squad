#pragma once
#include "syComponent.h"


namespace sy
{
    class SpriteRenderer : public Component
    {
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

    private:
    };
}
