#pragma once
#include "syResource.h"
#include "syTexture.h"

namespace sy
{
	using namespace math;
	class Texutre;
	class Animator;
	class Animation : public Resource
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;
			Vector2 size;
			Vector2 offset;
			float	duration;

			Sprite()
				: leftTop(Vector2::Zero)
				, size(Vector2::Zero)
				, offset(Vector2::Zero)
				, duration(0.0f)
			{}
		};

		Animation();
		virtual ~Animation();

		void Update();
		void Render(HDC hdc);

		virtual HRESULT Load(const std::wstring& path) { return E_FAIL; }

		void Create(Texture* texture, const std::wstring& name
			, Vector2 leftTop, Vector2 size, Vector2 Interbal
			, float duration, UINT spriteLength, Vector2 offset);

		void Create_Offset(Texture* texture, const std::wstring& name
			, Vector2 leftTop, Vector2 size, Vector2 Interbal
			, float duration, UINT spriteLength, std::vector<Vector2> offset);

		void Reset();

		bool IsComplete() const { return mbComplete; }
		void SetAnimator(Animator* animator) { mAnimator = animator; }
		int GetIndex() const { return mIndex; }

		void SetBmpRGB(BYTE r, BYTE g, BYTE b) { mBMPRGB = RGB(r, g, b); };

	private:
		Animator* mAnimator;
		Texture* mTexture;

		std::vector<Sprite> mSpriteSheet;
		int mIndex;
		float mTime;

		bool mbComplete;

		COLORREF	mBMPRGB;
	};
}
