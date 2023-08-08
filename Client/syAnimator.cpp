#include "syAnimator.h"
#include "syTexture.h"
#include "syResourceManager.h"

namespace sy
{
	Animator::Animator()
		: Component(eComponentType::Animator)
		, mActiveAnimation(nullptr)
		, mbLoop(false)			
		, mbAffectedCamera(true)
		, mAlpha(1.0f)
	{
	}

	Animator::~Animator()
	{
		for (auto iter : mAnimations)
		{
			if (nullptr != iter.second)
			{
				delete iter.second;
				iter.second = nullptr;
			}
		}
	}

	void Animator::Initialize()
	{
	}

	void Animator::Update()
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Update();

			// 애니메이션이 한 루프를 돌고난뒤 mbLoop설정이 되어있다면 리셋호출하여 다시 재생하도록 설정
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
		// Animation은 ResourceManager가 관리하지않고 각 Animator 가 관리
		Animation* animation = nullptr;
		animation = FindAnimation(name); // Animator 에서 같은 이름의 애니메이션이 있다면 생성하지않고 리턴
		if (animation != nullptr)
			return animation;

		animation = new Animation();
		animation->Create(texture, name
			, leftTop, size, Interbal
			, duration, spriteLength, offset);
		animation->SetAnimator(this);

		mAnimations.insert(std::make_pair(name, animation));

		return animation;
	}

	Animation* Animator::CreateAnimation_Offset(Texture* texture, const std::wstring& name, Vector2 leftTop, Vector2 size, Vector2 Interbal, float duration, UINT spriteLength, std::vector<Vector2> offset)
	{
		// Animation은 ResourceManager가 관리하지않고 각 Animator 가 관리
		Animation* animation = nullptr;
		animation = FindAnimation(name); // Animator 에서 같은 이름의 애니메이션이 있다면 생성하지않고 리턴
		if (animation != nullptr)
			return animation;

		animation = new Animation();
		animation->Create_Offset(texture, name
			, leftTop, size, Interbal
			, duration, spriteLength, offset);
		animation->SetAnimator(this);

		mAnimations.insert(std::make_pair(name, animation));

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
		eTextureType TempType = eTextureType::None;
		// 디렉토리 파일중에 width 와 height 가 제일 큰값 구하기, 파일갯수 저장
		for (auto& p : std::filesystem::recursive_directory_iterator(path))
		{
			std::wstring fileName = p.path().filename();
			std::wstring fullName = p.path();

			// 확장자가 png인 경우 스킵
			const std::wstring ext = p.path().extension();
			if (ext == L".png")
				continue;

			Texture* image = ResourceManager::Load<Texture>(fileName, fullName);
			TempType = image->GetType();
			images.push_back(image);

			if (width < image->GetWidth())
				width = image->GetWidth();

			if (height < image->GetHeight())
				height = image->GetHeight();

			fileCount++;
		}

		std::wstring spriteSheetName = name + L"SpriteSheet";
		// 구한 크기값으로 Texture 생성
		Texture* spriteSheet = Texture::Create(spriteSheetName, width * fileCount, height);

		// 읽은 파일의 타입으로 spriteSheet의 타입을 생성한다
		spriteSheet->SetType(TempType);

		// Texture 에 Load 해두었던 image 붙여넣기
		int idx = 0;
		for (Texture* image : images)
		{
			// 이미지 중상단에 붙여넣기
			BitBlt(spriteSheet->GetHdc(), int((width * idx) + ((width - image->GetWidth()) / 2.0f)), 0
				, image->GetWidth(), image->GetHeight()
				, image->GetHdc(), 0, 0, SRCCOPY);

			idx++;
		}

		// 생성한 spriteSheet로 애니메이션 생성
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
		// mAnimations 로부터 찾아와서 현재 애니메이션으로 설정
		Animation* animation = FindAnimation(name);
		if (animation == nullptr)
			return;

		animation->Reset();
		mActiveAnimation = animation;
		mbLoop = loop;			
	}
}
