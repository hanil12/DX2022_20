#include "framework.h"
#include "Cup_Bg.h"

Cup_Bg::Cup_Bg()
{
	_bg = make_shared<Quad>(L"Resource/Texture/CupHead/clown_bg_main.png");
	_ground = make_shared<Quad>(L"Resource/Texture/CupHead/clown_bg_track.png");
	_ground->GetTransform()->SetParent(_bg->GetTransform());
	_ground->GetTransform()->GetPos().y -= 300.0f;

	_collider = make_shared<RectCollider>(_ground->GetImageSize());
	_collider->GetTransform()->SetParent(_ground->GetTransform());
	_collider->GetTransform()->GetPos().y -= 82.0f;
}

Cup_Bg::~Cup_Bg()
{
}

void Cup_Bg::Update()
{
	_bg->Update();
	_ground->Update();
	_collider->Update();

	if (_player.expired() == false)
	{
		shared_ptr<CircleCollider> circle = _player.lock()->GetBodyCollider();
		HIT_RESULT result = _collider->Block(circle);
		if (result.isHit == true)
		{
			_player.lock()->Ground();
		}
	}
}

void Cup_Bg::Render()
{
	_bg->Render();
	_ground->Render();
	_collider->Render();
}

void Cup_Bg::PostRender()
{
	ImGui::SliderFloat("ColliderY", (float*)&_collider->GetTransform()->GetPos().y, -200.0f, 200.0f);
}
