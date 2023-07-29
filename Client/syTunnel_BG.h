#pragma once
#include "syBackGround.h"

namespace sy
{
	class Tunnel_BG : public BackGround
	{
	public:
		Tunnel_BG();
		virtual ~Tunnel_BG();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
	};
}
