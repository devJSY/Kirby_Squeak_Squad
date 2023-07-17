#include "syFlower.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syInput.h"
#include "syFlower_Skill.h"
#include "syTransform.h"
#include "syObject.h"

namespace sy
{
	Flower::Flower()
		: Enemy(eAbilityType::None)
	{
	}

	Flower::~Flower()
	{
	}

	void Flower::Initialize()
	{
		Texture* Enemies_Right = ResourceManager::Load<Texture>(L"Enemies_Right", L"..\\Resources\\Enemy\\Enemies_Right.bmp");
		Texture* Enemies_Left = ResourceManager::Load<Texture>(L"Enemies_Left", L"..\\Resources\\Enemy\\Enemies_Left.bmp");

		mAnimator->CreateAnimation(Enemies_Right, L"Flower_Right_Move", Vector2(0.f, 2916.f), Vector2(25.f, 24.f), Vector2(25.f, 0.f), 0.15f, 6);
		mAnimator->CreateAnimation(Enemies_Right, L"Flower_Right_Death", Vector2(36.f, 3021.f), Vector2(20.f, 32.f), Vector2(20.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(Enemies_Right, L"Flower_Right_Attack", Vector2(0.f, 2941.f), Vector2(30.f, 26.f), Vector2(30.f, 0.f), 0.2f, 3);

		mAnimator->PlayAnimation(L"Flower_Right_Move", true);

		Enemy::Initialize();
	}

	void Flower::Update()
	{
		Enemy::Update();

		// Ư�� �����϶� ��ų ����
		if (Input::GetKeyDown(eKeyCode::MOUSE_LBTN))
		{
			Transform* tr = GetComponent<Transform>();
			// ���� HotHead ��ġ ���� ������ ��ġ�� ����
			Vector2 pos = tr->GetPosition();
			pos += Vector2(10.f, 0.f);
			FlowerSkill* skill = object::Instantiate<FlowerSkill>(eLayerType::Effect);
			skill->GetComponent<Transform>()->SetPosition(pos);
			skill->SetOwner(this);
		}
	}

	void Flower::Render(HDC hdc)
	{
		Enemy::Render(hdc);
	}
}