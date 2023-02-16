#include "framework.h"
#include "CupHeadScene.h"

CupHeadScene::CupHeadScene()
{
	_player = make_shared<Cup_Advanced_Player>();
	_player->GetTransform()->GetPos() = CENTER;

	Load();

	_monster = make_shared<Cup_Monster>();
	_monster->GetTransform()->GetPos() = Vector2(WIN_WIDTH - 300, CENTER_Y);

	_bg = make_shared<Cup_Bg>();
	_bg->SetPos(CENTER);

	_bg->SetPlayer(_player);

	Vector2 bgLB = _bg->LeftBottom();
	Vector2 bgRT = _bg->RightTop();
	CAMERA->SetTarget(_player->GetTransform());
	CAMERA->SetLeftBottom(_bg->LeftBottom());
	CAMERA->SetRightTop(_bg->RightTop());
	CAMERA->SetOffset(CENTER);

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
			Camera::GetInstance()->ShakeStart(2.0f, 0.3f);
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

	if (ImGui::Button("Save", { 100,100 }))
	{
		Save();
	}

	if (ImGui::Button("Load", { 100,100 }))
	{
		Load();
	}
}

void CupHeadScene::Render()
{
	_monster->Render();
	_player->Render();
}

void CupHeadScene::Save()
{
	BinaryWriter writer = BinaryWriter(L"Save/CupHeadInfo.cup");

	Vector2 pos = _player->GetTransform()->GetWorldPos();
	writer.Byte((void*)&pos, sizeof(Vector2));
}

void CupHeadScene::Load()
{
	BinaryReader reader = BinaryReader(L"Save/CupHeadInfo.cup");

	Vector2 pos;
	Vector2* posPtr = &pos;
	reader.Byte((void**)&posPtr, sizeof(Vector2));

	_player->GetTransform()->GetPos() = pos;
}
