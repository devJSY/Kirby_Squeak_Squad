#pragma once
#include "syBackGround.h"

namespace sy
{
	class WorldTunnel_BG : public BackGround
	{
	public:
		WorldTunnel_BG();
		virtual ~WorldTunnel_BG();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
	};
}
