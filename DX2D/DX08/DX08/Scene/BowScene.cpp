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
	_bow->GetTransform()->GetAngle() = MOUSE_POS.Angle();

	_bow->Update();
}

void BowScene::Render()
{
	_bow->Render();
}
