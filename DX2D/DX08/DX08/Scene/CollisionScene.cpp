#include "framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	_rect = make_shared<RectCollider>(Vector2(100, 100));
	_rect->GetTransform()->GetPos() = Vector2(CENTER_X, CENTER_Y);

	_circle1 = make_shared<CircleCollider>(50);
	_circle1->GetTransform()->GetPos() = Vector2(CENTER_X + 200, CENTER_Y + 100);

	_circle2 = make_shared<CircleCollider>(70);
	_circle2->GetTransform()->SetParent(_rect->GetTransform());
	_circle2->GetTransform()->GetPos() = Vector2(CENTER_X - 200, CENTER_Y + 100);
}

CollisionScene::~CollisionScene()
{
}

void CollisionScene::Update()
{
	_rect->Update();
	_circle1->Update();
	_circle2->Update();

	if (_circle1->IsCollision(_circle2))
	{
		_circle1->SetRed();
		_circle2->SetRed();
	}
	else
	{
		_circle1->SetGreen();
		_circle2->SetGreen();
	}
}

void CollisionScene::Render()
{
	_rect->Render();
	_circle1->Render();
	_circle2->Render();
}

void CollisionScene::PostRender()
{
	ImGui::SliderFloat2("Rect Pos", (float*)&_rect->GetTransform()->GetPos(),0, WIN_WIDTH);
	ImGui::SliderFloat2("Circle1 Pos", (float*)&_circle1->GetTransform()->GetPos(),0, WIN_WIDTH);
	ImGui::SliderFloat2("Circle2 Pos", (float*)&_circle2->GetTransform()->GetPos(),0, WIN_WIDTH);

	float circle2_scale = _circle2->GetTransform()->GetScale().x;
	ImGui::SliderFloat("Circle2 Scale", (float*)&circle2_scale,0, 3);
	_circle2->GetTransform()->GetScale() = Vector2(circle2_scale, circle2_scale);

	float rect_Scale = _rect->GetTransform()->GetScale().x;
	ImGui::SliderFloat("Rect Scale", (float*)&rect_Scale,0, 3);
	_rect->GetTransform()->GetScale() = Vector2(rect_Scale, rect_Scale);
}
