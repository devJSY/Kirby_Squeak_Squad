#include "syAnimation.h"
#include "syAnimator.h"
#include "syTime.h"
#include "syTransform.h"
#include "syGameObject.h"
#include "syCamera.h"

namespace sy
{
	Animation::Animation()
		: mAnimator(nullptr)
		, mTexture(nullptr)
		, mSpriteSheet{}
		, mIndex(-1)
		, mTime(0.0f)
		, mbComplete(false)
		, mScale(Vector2::One)
	{
	}

	Animation::~Animation()
	{
	}

	void Animation::Update()
	{
		// mSpriteSheet의 루프가 끝난상태면 리턴 
		if (mbComplete)
			return;

		mTime += Time::DeltaTime();

		// 스프라이트에 설정된 시간이 지난경우
		if (mSpriteSheet[mIndex].duration < mTime)
		{
			mTime = 0.0f;

			if (mIndex < mSpriteSheet.size() - 1)
				mIndex++; // 다음인덱스로 설정
			else
				mbComplete = true; // 한 루프가 끝난경우 완료설정
		}
	}

	void Animation::Render(HDC hdc)
	{
		assert(mTexture); // mTexture이 nullptr 이면 에러

		Transform* tr = mAnimator->GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (mAnimator->GetAffectedCamera())
			pos = Camera::CalculatePosition(pos);
				
		if (mTexture->GetType() == eTextureType::Bmp)
		{
			TransparentBlt(hdc
				, (int)(pos.x - ((mSpriteSheet[mIndex].size.x * mScale.x) / 2.0f) + mSpriteSheet[mIndex].offset.x) // 스프라이트의 중점기준 렌더링
				, (int)(pos.y - ((mSpriteSheet[mIndex].size.y * mScale.y) / 2.0f) + mSpriteSheet[mIndex].offset.y) // 스프라이트의 중점기준 렌더링
				, (int)(mSpriteSheet[mIndex].size.x * mScale.x)		// 현재 Sprite 사이즈만큼 잘라냄
				, (int)(mSpriteSheet[mIndex].size.y * mScale.y)
				, mTexture->GetHdc()				// Sprite를 가져올 텍스쳐 설정
				, (int)mSpriteSheet[mIndex].leftTop.x	// 현재 Sprite의 좌상단 좌표 설정
				, (int)mSpriteSheet[mIndex].leftTop.y
				, (int)mSpriteSheet[mIndex].size.x		// 현재 Sprite 사이즈만큼 잘라냄
				, (int)mSpriteSheet[mIndex].size.y
				, RGB(255, 0, 255));				// 마젠타색상 고정 필요하면 변수화
		}
		else if (mTexture->GetType() == eTextureType::AlphaBmp)
		{
			// mAnimator로 부터 알파값을 받아와서 알파값 셋팅
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			// 0.0f ~ 1.0f -> 0 ~ 255
			int alpha = (int)(mAnimator->GetAlpha() * 255.0f);
			if (alpha <= 0)
				alpha = 0;
			func.SourceConstantAlpha = alpha; // 0 ~ 255

			AlphaBlend(hdc
				, (int)(pos.x - ((mSpriteSheet[mIndex].size.x * mScale.x) / 2.0f) + mSpriteSheet[mIndex].offset.x) // 스프라이트의 중점기준 렌더링
				, (int)(pos.y - ((mSpriteSheet[mIndex].size.y * mScale.y) / 2.0f) + mSpriteSheet[mIndex].offset.y) // 스프라이트의 중점기준 렌더링
				, (int)(mSpriteSheet[mIndex].size.x * mScale.x)	// 현재 Sprite 사이즈만큼 잘라냄
				, (int)(mSpriteSheet[mIndex].size.y * mScale.y)
				, mTexture->GetHdc()					// Sprite를 가져올 텍스쳐 설정
				, (int)mSpriteSheet[mIndex].leftTop.x	// 현재 Sprite의 좌상단 좌표 설정
				, (int)mSpriteSheet[mIndex].leftTop.y
				, (int)mSpriteSheet[mIndex].size.x		// 현재 Sprite 사이즈만큼 잘라냄
				, (int)mSpriteSheet[mIndex].size.y
				, func);
		}
		else if (mTexture->GetType() == eTextureType::Png)
		{
			Gdiplus::Graphics graphics(hdc);
			graphics.DrawImage(mTexture->GetImage()
				, (int)pos.x - ((mSpriteSheet[mIndex].size.x * mScale.x) / 2.0f) + mSpriteSheet[mIndex].offset.x	 // 스프라이트의 중점기준 렌더링
				, (int)pos.y - ((mSpriteSheet[mIndex].size.y * mScale.y) / 2.0f) + mSpriteSheet[mIndex].offset.y
				, mSpriteSheet[mIndex].size.x * mScale.x						 // 현재 Sprite 사이즈만큼 잘라냄
				, mSpriteSheet[mIndex].size.y * mScale.y);
		}
	}

	void Animation::Create(Texture* texture, const std::wstring& name, Vector2 leftTop, Vector2 size, Vector2 Interbal, float duration, UINT spriteLength, Vector2 offset)
	{	
		// 텍스쳐 설정
		mTexture = texture;

		// 텍스쳐의 각 스프라이트의 정보를 셋팅하여 Sprite형태로 vector에 저장한다.
		for (size_t i = 0; i < spriteLength; i++)
		{
			Sprite sprite = {};

			/*sprite.leftTop.x = leftTop.x + (size.x * i);
			sprite.leftTop.y = leftTop.y;*/
			sprite.leftTop = leftTop + (Interbal * (float)i);
			sprite.size = size;
			sprite.offset = offset;
			sprite.duration = duration;

			mSpriteSheet.push_back(sprite);
		}
	}

	void Animation::Reset()
	{
		mTime = 0.0f;
		mIndex = 0;
		mbComplete = false;
	}
}