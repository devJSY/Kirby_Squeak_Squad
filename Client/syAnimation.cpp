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

		Sprite sprite = mSpriteSheet[mIndex];

		Transform* tr = mAnimator->GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition() + sprite.offset;

		mTexture->Render(hdc
			, pos
			, sprite.size
			, sprite.leftTop
			, sprite.size
			, mAnimator->GetAffectedCamera()
			, mAnimator->GetScale()
			, mAnimator->GetAlpha());
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