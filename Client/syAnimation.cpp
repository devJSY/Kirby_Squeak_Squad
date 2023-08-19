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
		, mBMPRGB(RGB(255, 0, 255)) // 기본값 마젠타
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

		Sprite sprite = mSpriteSheet[mIndex];

		Transform* tr = mAnimator->GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition() + sprite.offset;

		mTexture->Render(hdc
			, pos
			, sprite.size
			, sprite.leftTop
			, sprite.size
			, mAnimator->GetAffectedCamera()
			, Vector2::One				// 애니메이션은 카메라속도 비율 1
			, tr->GetScale()			
			, mAnimator->GetAlpha()
			, mBMPRGB
			, tr->GetRotation()
			, mAnimator->GetBlink());
	}

	void Animation::Create(Texture* texture, const std::wstring& name, Vector2 leftTop, Vector2 size, Vector2 Interbal, float duration, UINT spriteLength, Vector2 offset)
	{	
		SetName(name);

		// 텍스쳐 설정
		mTexture = texture;

		// 텍스쳐의 각 스프라이트의 정보를 셋팅하여 Sprite형태로 vector에 저장한다.
		for (size_t i = 0; i < spriteLength; i++)
		{
			Sprite sprite = {};

			sprite.leftTop = leftTop + (Interbal * (float)i);
			if (sprite.leftTop.x >= texture->GetWidth())
			{
				int row = int(sprite.leftTop.x / texture->GetWidth());
				sprite.leftTop.x = sprite.leftTop.x - (texture->GetWidth() * row);
				sprite.leftTop.y = leftTop.y + (size.y * row);
			}
			sprite.size = size;
			sprite.offset = offset;
			sprite.duration = duration;

			mSpriteSheet.push_back(sprite);
		}
	}

	void Animation::Create_Offset(Texture* texture, const std::wstring& name, Vector2 leftTop, Vector2 size, Vector2 Interbal, float duration, UINT spriteLength, std::vector<Vector2> offset)
	{
		SetName(name);
		bool offsetFlag = true;

		if (offset.empty()) offsetFlag = false;

		// 텍스쳐 설정
		mTexture = texture;

		// 텍스쳐의 각 스프라이트의 정보를 셋팅하여 Sprite형태로 vector에 저장한다.
		for (size_t i = 0; i < spriteLength; i++)
		{
			Sprite sprite = {};

			sprite.leftTop = leftTop + (Interbal * (float)i);
			sprite.size = size;
			if (offsetFlag)
			{
				sprite.offset.x = offset[i].x;
				sprite.offset.y = offset[i].y;
			}
			else
			{
				sprite.offset.x = 0.f;
				sprite.offset.y = 0.f;
			}
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