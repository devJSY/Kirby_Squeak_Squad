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

		Animation* CreateAnimation(class Texture* texture
			, const std::wstring& name
			, Vector2 leftTop, Vector2 size, Vector2 Interbal
			, float duration = 0.1f, UINT spriteLength = 0, Vector2 offset = Vector2::Zero);

		void CreateAnimationFolder(const std::wstring& name
			, const std::wstring& path
			, float duration = 0.1f, Vector2 offset = Vector2::Zero);

		Animation* FindAnimation(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop = false); // ���� �⺻�� false

		float GetAlpha() { return mAlpha; }
		void SetAlpha(float alpha) { mAlpha = alpha; }

		void SetAffectedCamera(bool enable) { mbAffectedCamera = enable; }
		bool GetAffectedCamera() { return mbAffectedCamera; }

		bool IsActiveAnimationComplete() { return mActiveAnimation->IsComplete(); }

		void ActiveAnimationReset() { mActiveAnimation->Reset(); }		

	private:
		std::map<std::wstring, Animation*> mAnimations; // �ִϸ��̼ǵ��� ����

		Animation* mActiveAnimation;	// ���� �ִϸ��̼�
		bool mbLoop;					// �ִϸ��̼� �ݺ� ����
		bool mbAffectedCamera;			// ī�޶� ���� ����
		float mAlpha;					// ���� ���尪 0 ~ 1
	};
}


