#pragma once
#include "syBackGround.h"

namespace sy
{
	class Level_BG : public BackGround
	{
	public:
		Level_BG();
		virtual ~Level_BG();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetLevelType(eLevelType type);

	private:
		class Animator* mAnimator;
		eLevelType mtype;		
	};
}
