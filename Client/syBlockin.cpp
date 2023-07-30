#include "syBlockin.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"

namespace sy
{
	Blockin::Blockin()
		: Enemy(eAbilityType::Normal)
	{
	}

	Blockin::~Blockin()
	{
	}

	void Blockin::Initialize()
	{
		Texture* Enemies_Right = ResourceManager::Load<Texture>(L"Enemies_Right_Tex", L"..\\Resources\\Enemy\\Enemies_Right.bmp");
		Texture* Enemies_Left = ResourceManager::Load<Texture>(L"Enemies_Left_Tex", L"..\\Resources\\Enemy\\Enemies_Left.bmp");

		Animator* animator = GetComponent<Animator>();

		animator->CreateAnimation(Enemies_Right, L"BlockEnemy_Right_Idle", Vector2(1.f, 611.f), Vector2(16.f, 16.f), Vector2(16.f, 0.f), 1.f, 1);
		
		animator->CreateAnimation(Enemies_Right, L"BlockEnemy_Right_Appear", Vector2(0.f, 611.f), Vector2(18.f, 16.f), Vector2(18.f, 0.f), 0.12f, 6);
		animator->CreateAnimation(Enemies_Left, L"BlockEnemy_Left_Appear", Vector2(464.f, 611.f), Vector2(18.f, 16.f), Vector2(-18.f, 0.f), 0.12f, 6);
		
		animator->CreateAnimation(Enemies_Right, L"BlockEnemy_Right_Walk", Vector2(110.f, 616.f), Vector2(23.f, 35.f), Vector2(23.f, 0.f), 0.12f, 7);
		animator->CreateAnimation(Enemies_Left, L"BlockEnemy_Left_Walk", Vector2(349.f, 616.f), Vector2(23.f, 35.f), Vector2(-23.f, 0.f), 0.12f, 7);
		
		animator->CreateAnimation(Enemies_Right, L"BlockEnemy_Right_Death", Vector2(26.f, 653.f), Vector2(21.f, 20.f), Vector2(21.f, 0.f), 1.f, 1);
		animator->CreateAnimation(Enemies_Left, L"BlockEnemy_Left_Death", Vector2(435.f, 653.f), Vector2(21.f, 20.f), Vector2(-21.f, 0.f), 1.f, 1);
		
		animator->PlayAnimation(L"BlockEnemy_Right_Appear", true);

		Enemy::Initialize();
	}

	void Blockin::Update()
	{
		Enemy::Update();
	}

	void Blockin::Render(HDC hdc)
	{
		Enemy::Render(hdc);
	}

	void Blockin::OnCollisionEnter(Collider* other)
	{
	}

	void Blockin::OnCollisionStay(Collider* other)
	{
	}

	void Blockin::OnCollisionExit(Collider* other)
	{
	}

	void Blockin::CheckPixelCollision()
	{
	}
}