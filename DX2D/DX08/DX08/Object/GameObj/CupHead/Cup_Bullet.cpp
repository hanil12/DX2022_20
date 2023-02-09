#include "framework.h"
#include "Cup_Bullet.h"

Cup_Bullet::Cup_Bullet()
{
	CreateAction();

	_collider = make_shared<CircleCollider>(21);
	_collider->GetTransform()->SetParent(_sprite->GetTransform());
	_collider->GetTransform()->GetPos().y += 40;
}

Cup_Bullet::~Cup_Bullet()
{
}

void Cup_Bullet::Update()
{
	if (!isActive) return;

	_collider->Update();

	_delay += DELTA_TIME;

	if (_delay >= _lifeTime)
	{
		_action->Reset();
		isActive = false;
		_delay = 0.0f;
	}

	_sprite->GetTransform()->GetPos() += _direction * _speed * DELTA_TIME;

	_action->Update();
	_sprite->Update();
}

void Cup_Bullet::Render()
{
	if (!isActive) return;

	_sprite->SetActionClip(_action->GetCurClip());
	_sprite->Render();
	_collider->Render();
}

void Cup_Bullet::Fire(Vector2 dir)
{
	_action->Play();
	_sprite->GetTransform()->GetAngle() = dir.Angle() - PI * 0.5f;
	_direction = dir.NormalVector2();
}

void Cup_Bullet::Enable()
{
	isActive = true;
	_delay = 0.0f;
}

void Cup_Bullet::Disable()
{
	isActive = false;
	_delay = 0.0f;
}

bool Cup_Bullet::Collision(shared_ptr<Collider> col)
{
	if (isActive == false)
		return false;

	bool result = _collider->IsCollision(col);

	if (result == true)
	{
		Disable();
	}

	return result;
}

void Cup_Bullet::CreateAction()
{
	string xmlPath = "Resource/XML/Special_Bullet_Loop.xml";
	wstring srvPath = L"Resource/Texture/CupHead/Special_Bullet_Loop.png";

	MyXML xml = MyXML(xmlPath, srvPath);

	_action = make_shared<Action>(xml.GetClips(), "Bullet");
	Vector2 averageSize = xml.AverageSize() * 0.3f;
	_sprite = make_shared<Sprite>(srvPath, averageSize);
}
