#include "syAnimator.h"
#include "syResourceManager.h"
#include "syTexture.h"

namespace sy
{
	Animator::Animator()
		: Component(eComponentType::Animator)
		, mActiveAnimation(nullptr)
		, mbLoop(false)			
		, mbAffectedCamera(true)
		, mAlpha(1.0f)
		, mScale(Vector2::One)
	{
	}

	Animator::~Animator()
	{
		//for (auto iter : mAnimations)
		//{
		//	if (nullptr != iter.second)
		//	{
		//		delete iter.second;
		//		iter.second = nullptr;
		//	}
		//}
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

	Animation* Animator::CreateAnimation(Texture* texture
		, const std::wstring& name
		, Vector2 leftTop
		, Vector2 size, Vector2 Interbal
		, float duration, UINT spriteLength
		, Vector2 offset)
	{
		// Animation�� ResourceManager�� ���������ʰ� �� Animator �� ����
		Animation* animation = nullptr;
		animation = ResourceManager::Find<Animation>(name);
		if (animation != nullptr)
		{
			mAnimations.insert(std::make_pair(name, animation));
			return animation;
		}

		animation = new Animation();
		animation->Create(texture, name
			, leftTop, size, Interbal
			, duration, spriteLength, offset);
		animation->SetAnimator(this);

		mAnimations.insert(std::make_pair(name, animation));
		ResourceManager::Insert<Animation>(name, animation);

		return animation;
	}

	void Animator::CreateAnimationFolder(
		const std::wstring& name
		, const std::wstring& path
		, float duration
		, Vector2 offset)
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

		std::wstring spriteSheetName = name + L"SpriteSheet";
		// ���� ũ�Ⱚ���� Texture ����
		Texture* spriteSheet = Texture::Create(spriteSheetName, width * fileCount, height);

		// Video �⺻ Ÿ�� Bmp�� ����
		spriteSheet->SetType(eTextureType::Bmp); 

		// 32bit ��Ʈ�� �����ΰ�� AlphaBmp Ÿ������ �����Ѵ�
		BITMAP info = {};
		GetObject(spriteSheet->GetBitmap(), sizeof(BITMAP), &info);		
		if (info.bmBitsPixel == 32)
			spriteSheet->SetType(eTextureType::AlphaBmp);


		// Texture �� Load �صξ��� image �ٿ��ֱ�
		int idx = 0;
		for (Texture* image : images)
		{
			// �̹��� �߻�ܿ� �ٿ��ֱ�
			BitBlt(spriteSheet->GetHdc(), int((width * idx) + ((width - image->GetWidth()) / 2.0f)), 0
				, image->GetWidth(), image->GetHeight()
				, image->GetHdc(), 0, 0, SRCCOPY);

			idx++;
		}

		// ������ spriteSheet�� �ִϸ��̼� ����
		CreateAnimation(spriteSheet, name
			, Vector2(0.0f, 0.0f)
			, Vector2(width, height), Vector2(width, 0), duration
			,fileCount, offset);
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

		// �ִϸ��̼��� ����Ǵ� ��쿡�� Reset() ����
		if (mActiveAnimation != animation)		
			animation->Reset();		

		mActiveAnimation = animation;
		mbLoop = loop;			
	}

	void Animator::SetAniScale(const std::wstring& name, Vector2 scale)
	{
		Animation* animation = FindAnimation(name);
		if (animation == nullptr)
			return;

		animation->SetScale(scale);
	}
}
