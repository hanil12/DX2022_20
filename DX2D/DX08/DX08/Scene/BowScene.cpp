#include "framework.h"
#include "BowScene.h"

BowScene::BowScene()
{
	_bow = make_shared<Bow_Bow>();
}

BowScene::~BowScene()
{
}

void BowScene::Update()
{
	_bow->GetTransform()->GetAngle() = (MOUSE_POS - _bow->GetTransform()->GetPos()).Angle();

	_bow->Update();
}

void BowScene::Render()
{
	_bow->Render();
}

void BowScene::PostRender()
{
	ImGui::SliderFloat("BowX", &_bow->GetTransform()->GetPos().x, 0, WIN_WIDTH);
	ImGui::SliderFloat("BowY", &_bow->GetTransform()->GetPos().y, 0, WIN_HEIGHT);
}
