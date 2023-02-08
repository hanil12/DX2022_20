#include "framework.h"
#include "CupHeadScene.h"

CupHeadScene::CupHeadScene()
{
	_player = make_shared<Cup_Advanced_Player>();
	_player->GetTransform()->GetPos() = CENTER;

	_monster = make_shared<Cup_Monster>();
	_monster->GetTransform()->GetPos() = Vector2(WIN_WIDTH - 300, CENTER_Y);

	_bg = make_shared<Cup_Bg>();
	_bg->SetPos(CENTER);

	_bg->SetPlayer(_player);
}

CupHeadScene::~CupHeadScene()
{
}

void CupHeadScene::Update()
{
	_bg->Update();
	_player->Update();
	_monster->Update();
}

void CupHeadScene::PreRender()
{
	_bg->Render();
}

void CupHeadScene::PostRender()
{
	_bg->PostRender();
}

void CupHeadScene::Render()
{
	_monster->Render();
	_player->Render();
}
