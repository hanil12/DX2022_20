#include "framework.h"
#include "Cup_Bg.h"

Cup_Bg::Cup_Bg()
{
	_bg = make_shared<Quad>(L"Resource/Texture/CupHead/clown_bg_main.png");
	_ground1 = make_shared<Quad>(L"Resource/Texture/CupHead/clown_bg_track.png");
	_ground1->GetTransform()->SetParent(_bg->GetTransform());
	_ground1->GetTransform()->GetPos().y -= 300.0f;

	_collider1 = make_shared<RectCollider>(_ground1->GetImageSize());
	_collider1->GetTransform()->SetParent(_ground1->GetTransform());
	_collider1->GetTransform()->GetPos().y -= 82.0f;

	_ground2 = make_shared<Quad>(L"Resource/Texture/CupHead/clown_bg_track.png");
	_ground2->GetTransform()->SetParent(_bg->GetTransform());

	Vector2 col2Size = _ground2->GetImageSize();
	col2Size.y -= 100;
	_collider2 = make_shared<RectCollider>(col2Size);
	_collider2->GetTransform()->SetParent(_ground2->GetTransform());

	_ground2->GetTransform()->GetScale() *= 0.5f;
	_ground2->GetTransform()->GetPos() = Vector2(CENTER_X, 0);

	_colliders.push_back(_collider1);
	_colliders.push_back(_collider2);
}

Cup_Bg::~Cup_Bg()
{
}

void Cup_Bg::Update()
{
	_collider1->Update();
	_collider2->Update();

	_bg->Update();
	_ground1->Update();

	_ground2->Update();

	if (_player.expired() == false)
	{
		shared_ptr<CircleCollider> circle = _player.lock()->GetBodyCollider();
		HIT_RESULT result;

		for (auto rect : _colliders)
		{
			result = rect->Block(circle);
			if (result.isHit == true && result.dir == Dir::UP)
			{
				_player.lock()->Ground();
				break;
			}
			else if (result.isHit && result.dir == Dir::DOWN)
			{
				_player.lock()->Falling();
				break;
			}
		}

		if (result.isHit == false)
		{
			_player.lock()->Falling();
		}
	}
}

void Cup_Bg::Render()
{
	_bg->Render();
	_ground1->Render();
	_collider1->Render();

	_ground2->Render();
	_collider2->Render();
}

void Cup_Bg::PostRender()
{
	ImGui::SliderFloat("ColliderY", (float*)&_collider1->GetTransform()->GetPos().y, -200.0f, 200.0f);
}
