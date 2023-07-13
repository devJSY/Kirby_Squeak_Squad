#include "syAnimator.h"
#include "syResourceManager.h"

namespace sy
{
	Animator::Animator()
		: Component(eComponentType::Animator)
		, mActiveAnimation(nullptr)
		, mbLoop(false)					
		, mbAffectedCamera(false)			
		, mAlpha(1.0f)
	{
	}

	Animator::~Animator()
	{
	}

	void Animator::Initialize()
	{
	}

	void Animator::Update()
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Update();

			// �ִϸ��̼��� �� ������ ������ mbLoop������ �Ǿ��ִٸ� ����ȣ���Ͽ� �ٽ� ����ϵ��� ����
			if (mActiveAnimation->IsComplete() && mbLoop) 
			{
				mActiveAnimation->Reset();
			}
		}
	}

	void Animator::Render(HDC hdc)
	{
		if (mActiveAnimation)
			mActiveAnimation->Render(hdc);
	}

	void Animator::CreateAnimation(const std::wstring& name, Texture* texture, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration)
	{
		Animation* animation = nullptr;
		animation = ResourceManager::Find<Animation>(name); // ResourceManager ���� ���� ���ҽ��� �ִ��� ���� Ȯ��
		if (animation != nullptr)
			return;

		animation = new Animation();
		animation->Create(name, texture
			, leftTop, size, offset
			, spriteLength, duration);
		animation->SetAnimator(this);

		mAnimations.insert(std::make_pair(name, animation)); // mAnimations�� ������ �ִϸ��̼� �߰�
		ResourceManager::Insert<Animation>(name, animation); // ResourceManager �� �߰�
	}

	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		auto iter = mAnimations.find(name);
		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}

	void Animator::PlayAnimation(const std::wstring& name, bool loop)
	{
		// mAnimations �κ��� ã�ƿͼ� ���� �ִϸ��̼����� ����
		Animation* animation = FindAnimation(name);
		if (animation == nullptr)
			return;

		mActiveAnimation = animation;
		mActiveAnimation->Reset();
		mbLoop = loop;
	}
}
