#pragma once
#include "syBackGround.h"

namespace sy
{
	class WorldTunnel : public BackGround
	{
	public:
		WorldTunnel();
		virtual ~WorldTunnel();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
	};
}
