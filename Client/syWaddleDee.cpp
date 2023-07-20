#include "syWaddleDee.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"

namespace sy
{
	WaddleDee::WaddleDee()
		: Enemy(eAbilityType::Normal)
	{
	}

	WaddleDee::~WaddleDee()
	{
	}

	void WaddleDee::Initialize()
	{
		Texture* Enemies_Right = ResourceManager::Load<Texture>(L"Enemies_Right_Tex", L"..\\Resources\\Enemy\\Enemies_Right.bmp");
		Texture* Enemies_Left = ResourceManager::Load<Texture>(L"Enemies_Left_Tex", L"..\\Resources\\Enemy\\Enemies_Left.bmp");

		Animator* animator = GetAnimator();

		animator->CreateAnimation(Enemies_Right, L"Red_Right_Walk", Vector2(0.f, 675.f), Vector2(22.f, 20.f), Vector2(22.f, 0.f), 0.12f, 8);
		animator->CreateAnimation(Enemies_Left, L"Red_Left_Walk", Vector2(460.f, 675.f), Vector2(22.f, 20.f), Vector2(-22.f, 0.f), 0.12f, 8);

		animator->CreateAnimation(Enemies_Right, L"Red_Right_Death", Vector2(27.f, 722.f), Vector2(23.f, 23.f), Vector2(23.f, 0.f), 1.f, 1);
		animator->CreateAnimation(Enemies_Left, L"Red_Left_Death", Vector2(432.f, 722.f), Vector2(23.f, 23.f), Vector2(-23.f, 0.f), 1.f, 1);

		animator->PlayAnimation(L"Red_Right_Walk", true);

		Enemy::Initialize();
	}

	void WaddleDee::Update()
	{
		Enemy::Update();
	}

	void WaddleDee::Render(HDC hdc)
	{
		Enemy::Render(hdc);
	}
	void WaddleDee::OnCollisionEnter(Collider* other)
	{
	}
	void WaddleDee::OnCollisionStay(Collider* other)
	{

	}
	void WaddleDee::OnCollisionExit(Collider* other)
	{
	}
}