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
		// mSpriteSheet�� ������ �������¸� ���� 
		if (mbComplete)
			return;

		mTime += Time::DeltaTime();

		// ��������Ʈ�� ������ �ð��� �������
		if (mSpriteSheet[mIndex].duration < mTime)
		{
			mTime = 0.0f;

			if (mIndex < mSpriteSheet.size() - 1)
				mIndex++; // �����ε����� ����
			else
				mbComplete = true; // �� ������ ������� �Ϸἳ��
		}
	}

	void Animation::Render(HDC hdc)
	{
		assert(mTexture); // mTexture�� nullptr �̸� ����

		Transform* tr = mAnimator->GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (mAnimator->GetAffectedCamera())
			pos = Camera::CalculatePosition(pos);
				
		if (mTexture->GetType() == eTextureType::Bmp)
		{
			TransparentBlt(hdc
				, (int)(pos.x - ((mSpriteSheet[mIndex].size.x * mScale.x) / 2.0f) + mSpriteSheet[mIndex].offset.x) // ��������Ʈ�� �������� ������
				, (int)(pos.y - ((mSpriteSheet[mIndex].size.y * mScale.y) / 2.0f) + mSpriteSheet[mIndex].offset.y) // ��������Ʈ�� �������� ������
				, (int)(mSpriteSheet[mIndex].size.x * mScale.x)		// ���� Sprite �����ŭ �߶�
				, (int)(mSpriteSheet[mIndex].size.y * mScale.y)
				, mTexture->GetHdc()				// Sprite�� ������ �ؽ��� ����
				, (int)mSpriteSheet[mIndex].leftTop.x	// ���� Sprite�� �»�� ��ǥ ����
				, (int)mSpriteSheet[mIndex].leftTop.y
				, (int)mSpriteSheet[mIndex].size.x		// ���� Sprite �����ŭ �߶�
				, (int)mSpriteSheet[mIndex].size.y
				, RGB(255, 0, 255));				// ����Ÿ���� ���� �ʿ��ϸ� ����ȭ
		}
		else if (mTexture->GetType() == eTextureType::AlphaBmp)
		{
			// mAnimator�� ���� ���İ��� �޾ƿͼ� ���İ� ����
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
				, (int)(pos.x - ((mSpriteSheet[mIndex].size.x * mScale.x) / 2.0f) + mSpriteSheet[mIndex].offset.x) // ��������Ʈ�� �������� ������
				, (int)(pos.y - ((mSpriteSheet[mIndex].size.y * mScale.y) / 2.0f) + mSpriteSheet[mIndex].offset.y) // ��������Ʈ�� �������� ������
				, (int)(mSpriteSheet[mIndex].size.x * mScale.x)	// ���� Sprite �����ŭ �߶�
				, (int)(mSpriteSheet[mIndex].size.y * mScale.y)
				, mTexture->GetHdc()					// Sprite�� ������ �ؽ��� ����
				, (int)mSpriteSheet[mIndex].leftTop.x	// ���� Sprite�� �»�� ��ǥ ����
				, (int)mSpriteSheet[mIndex].leftTop.y
				, (int)mSpriteSheet[mIndex].size.x		// ���� Sprite �����ŭ �߶�
				, (int)mSpriteSheet[mIndex].size.y
				, func);
		}
		else if (mTexture->GetType() == eTextureType::Png)
		{
			Gdiplus::Graphics graphics(hdc);
			graphics.DrawImage(mTexture->GetImage()
				, (int)pos.x - ((mSpriteSheet[mIndex].size.x * mScale.x) / 2.0f) + mSpriteSheet[mIndex].offset.x	 // ��������Ʈ�� �������� ������
				, (int)pos.y - ((mSpriteSheet[mIndex].size.y * mScale.y) / 2.0f) + mSpriteSheet[mIndex].offset.y
				, mSpriteSheet[mIndex].size.x * mScale.x						 // ���� Sprite �����ŭ �߶�
				, mSpriteSheet[mIndex].size.y * mScale.y);
		}
	}

	void Animation::Create(Texture* texture, const std::wstring& name, Vector2 leftTop, Vector2 size, Vector2 Interbal, float duration, UINT spriteLength, Vector2 offset)
	{	
		// �ؽ��� ����
		mTexture = texture;

		// �ؽ����� �� ��������Ʈ�� ������ �����Ͽ� Sprite���·� vector�� �����Ѵ�.
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