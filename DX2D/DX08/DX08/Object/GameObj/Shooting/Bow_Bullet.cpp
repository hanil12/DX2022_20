#include "framework.h"
#include "Bow_Bullet.h"

Bow_Bullet::Bow_Bullet()
{
	_quad = make_shared<Quad>(L"Resource/Texture/Bullet.png");
	_quad->GetTransform()->GetScale() *= 0.1f;
}

Bow_Bullet::~Bow_Bullet()
{
}

void Bow_Bullet::Update()
{
	if (isActive == false)
		return;

	_quad->GetTransform()->GetPos() += _dir * _speed * DELTA_TIME;

	_quad->Update();
}

void Bow_Bullet::Render()
{
	if (isActive == false)
		return;

	_quad->Render();
}

void Bow_Bullet::SetDirection(Vector2 dir)
{
	dir.Normalize();
	_dir = dir;
}
