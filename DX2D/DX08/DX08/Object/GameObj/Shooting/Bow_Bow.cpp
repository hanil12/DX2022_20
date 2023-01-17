#include "framework.h"
#include "Bow_Bow.h"

Bow_Bow::Bow_Bow()
{
	_quad = make_shared<Quad>(L"Resource/Texture/Bow.png");
	_quad->GetTransform()->GetScale() *= 2.0f;

	_quad->GetTransform()->GetPos() = { 100,100 };

	_bullet = make_shared<Bow_Bullet>();
}

Bow_Bow::~Bow_Bow()
{
}

void Bow_Bow::Update()
{
	Fire();

	_quad->Update();

	_bullet->Update();
}

void Bow_Bow::Render()
{
	_quad->Render();

	_bullet->Render();
}

void Bow_Bow::Fire()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		_bullet->isActive = true;

		Vector2 direction = MOUSE_POS - _quad->GetTransform()->GetPos();
		_bullet->GetTransform()->GetPos() = _quad->GetTransform()->GetPos();
		_bullet->SetDirection(direction);
		_bullet->GetTransform()->GetAngle() = direction.Angle();
	}
}
