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
		~Animator();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void CreateAnimation(const std::wstring& name
			, class Texture* texture
			, Vector2 leftTop, Vector2 size, UINT spriteLength
			, Vector2 offset = Vector2::Zero, float duration = 0.1f);

		void CreateAnimationFolder(const std::wstring& name
			, const std::wstring& path
			, Vector2 offset = Vector2::Zero, float duration = 0.1f);

		Animation* FindAnimation(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop = false); // 루프 기본값 false

		bool GetAffectedCamera() { return mbAffectedCamera; }
		void SetAffectedCamera(bool enable) { mbAffectedCamera = enable; }
		float GetAlpha() { return mAlpha; }
		void SetAlpha(float alpha) { mAlpha = alpha; }

		bool IsComplete() { return mbComplete; }

		void SetAniScale(const std::wstring& name, Vector2 scale);

	private:
		std::map<std::wstring, Animation*> mAnimations; // 애니메이션들을 저장

		Animation* mActiveAnimation;	// 현재 애니메이션
		bool mbLoop;					// 애니메이션 반복 여부
		bool mbAffectedCamera;			// 카메라 영향여부
		float mAlpha;					// 알파 블랜드값 0 ~ 1
		bool mbComplete;					// 애니메이션 재생중인지 여부

	};
}


