#include "framework.h"
#include "Cup_Monster.h"

Cup_Monster::Cup_Monster()
{
	CreateAction();
	Vector2 colliderSize = _sprite->GetClipSize();
	colliderSize.x *= 0.65f;
	colliderSize.y *= 0.8f;
	_collider = make_shared<RectCollider>(colliderSize);

	_transform = _collider->GetTransform();
	_sprite->GetTransform()->SetParent(_transform);
	_sprite->SetReverse();
	_action->Play();
}

Cup_Monster::~Cup_Monster()
{
	_transform = nullptr;
}

void Cup_Monster::Update()
{
	_collider->Update();

	_action->Update();
	_sprite->Update();
}

void Cup_Monster::Render()
{
	_sprite->SetActionClip(_action->GetCurClip());
	_sprite->Render();
	_collider->Render();
}

void Cup_Monster::CreateAction()
{
	wstring srvPath = L"Resource/Texture/CupHead/Clown_Page_Last_Spawn_Penguin_Start.png";
	string xmlPath = "Resource/XML/Clown_Page_Last_Spawn_Penguin_Start.xml";
	MyXML xml = MyXML(xmlPath, srvPath);

	_action = make_shared<Action>(xml.GetClips(), "Boss_IDLE");
	Vector2 size = xml.AverageSize() * 0.7f;
	_sprite = make_shared<Sprite>(srvPath, size);
}
