#include "syAnimator.h"
#include "syResourceManager.h"
#include "syTexture.h"

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

	void Animator::CreateAnimation(const std::wstring& name
		, Texture* texture
		, Vector2 leftTop, Vector2 size
		, UINT spriteLength, Vector2 offset
		, float duration)
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

	void Animator::CreateAnimationFolder(const std::wstring& name
		, const std::wstring& path, Vector2 offset, float duration)
	{
		UINT width = 0;
		UINT height = 0;
		UINT fileCount = 0;

		std::filesystem::path fs(path);
		std::vector<Texture*> images = {};
		// ���丮 �����߿� width �� height �� ���� ū�� ���ϱ�, ���ϰ��� ����
		for (auto& p : std::filesystem::recursive_directory_iterator(path))
		{
			std::wstring fileName = p.path().filename();
			std::wstring fullName = p.path();

			// Ȯ���ڰ� png�� ��� ��ŵ
			const std::wstring ext = p.path().extension();
			if (ext == L".png")
				continue;

			Texture* image = ResourceManager::Load<Texture>(fileName, fullName);
			images.push_back(image);

			if (width < image->GetWidth())
				width = image->GetWidth();

			if (height < image->GetHeight())
				height = image->GetHeight();

			fileCount++;
		}

		// ���� ũ�Ⱚ���� Texture ����
		Texture* spriteSheet = Texture::Create(name, width * fileCount, height);
		spriteSheet->SetType(eTextureType::Bmp); // Video �⺻ Ÿ�� Bmp�� ����

		// Texture �� Load �صξ��� image �ٿ��ֱ�
		int idx = 0;
		for (Texture* image : images)
		{
			BitBlt(spriteSheet->GetHdc(), width * idx, 0
				, image->GetWidth(), image->GetHeight()
				, image->GetHdc(), 0, 0, SRCCOPY);

			idx++;
		}

		// ������ spriteSheet�� �ִϸ��̼� ����
		CreateAnimation(name
			, spriteSheet, Vector2(0.0f, 0.0f)
			, Vector2(width, height), fileCount
			, offset, duration);
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
