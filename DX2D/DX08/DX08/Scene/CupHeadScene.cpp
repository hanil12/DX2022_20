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

	Audio::GetInstance()->Add("bgm", "Resource/Sound/BGM.mp3", true);
	Audio::GetInstance()->Add("jump", "Resource/Sound/jump.wav");
	Audio::GetInstance()->Play("bgm");
}

CupHeadScene::~CupHeadScene()
{
}

void CupHeadScene::Update()
{
	_bg->Update();
	_player->Update();
	_monster->Update();

	_monster->Shot(_player->GetTransform()->GetWorldPos());

	for (auto monsterBullet : _monster->GetBullets())
	{
		if (monsterBullet->Collision(_player->GetBodyCollider()))
		{
			// Player Damaged;
		}
	}

	shared_ptr<Cup_Advanced_Player> player = dynamic_pointer_cast<Cup_Advanced_Player>(_player);
	if (player == nullptr)
		return;
	for (auto playerBullet : player->GetBullets())
	{
		if (playerBullet->Collision(_monster->GetBodyCollider()))
		{
			_monster->Dameged(10);
		}
	}
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
