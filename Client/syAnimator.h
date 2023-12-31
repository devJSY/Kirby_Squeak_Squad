#pragma once
#include "syComponent.h"
#include "syAnimation.h"

namespace sy
{
	using namespace math;
	class Animator : public Component
	{
	public:
		Animator();
		virtual ~Animator();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		Animation* CreateAnimation(class Texture* texture
			, const std::wstring& name
			, Vector2 leftTop, Vector2 size, Vector2 Interbal
			, float duration = 0.1f, UINT spriteLength = 0, Vector2 offset = Vector2::Zero);

		Animation* CreateAnimation_Offset(class Texture* texture
			, const std::wstring& name
			, Vector2 leftTop, Vector2 size, Vector2 Interbal
			, float duration = 0.1f, UINT spriteLength = 0, std::vector<Vector2> offset = {});

		void CreateAnimationFolder(const std::wstring& name
			, const std::wstring& path
			, float duration = 0.1f, Vector2 offset = Vector2::Zero);

		Animation* FindAnimation(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop = false); // 루프 기본값 false

		float GetAlpha() const { return mAlpha; }
		void SetAlpha(float alpha) { mAlpha = alpha; }
		bool GetBlink() const { return mbBlink; }
		void SetBlink(bool blink) { mbBlink = blink; }

		void SetAffectedCamera(bool enable) { mbAffectedCamera = enable; }
		bool GetAffectedCamera() const { return mbAffectedCamera; }

		bool IsActiveAnimationComplete() const { return mActiveAnimation->IsComplete(); }
		int GetActiveAnimationIndex() const { return mActiveAnimation->GetIndex(); }

		void ActiveAnimationReset() { mActiveAnimation->Reset(); }		

		void SetBmpRGB(const std::wstring& name, BYTE r, BYTE g, BYTE b)
		{
			Animation* ani = FindAnimation(name);
			if (ani != nullptr) ani->SetBmpRGB(r, g, b);
		}

		Animation* GetActiveAnimation() const { return mActiveAnimation; }

	private:
		std::map<std::wstring, Animation*> mAnimations; // 애니메이션들을 저장

		Animation* mActiveAnimation;	// 현재 애니메이션
		bool mbLoop;					// 애니메이션 반복 여부
		bool mbAffectedCamera;			// 카메라 영향 여부
		float mAlpha;					// 알파 블랜드값 0 ~ 1
		bool mbBlink;					
	};
}


