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

	Vector2 bgLB = _bg->LeftBottom();
	Vector2 bgRT = _bg->RightTop();

	Audio::GetInstance()->Add("bgm", "Resource/Sound/BGM.mp3", true);
	Audio::GetInstance()->Add("jump", "Resource/Sound/jump.wav");

	//Init();
	Audio::GetInstance()->Stop("bgm");

	_button = make_shared<Button>(L"Resource/Texture/UI/Button.png");
	_button->SetScale({ 0.1f,0.1f });
	_button->SetPostion(CENTER);

	_slider = make_shared<Slider>(Vector2(150, 50));
	_slider->SetPostion({ CENTER_X, CENTER_Y - 100 });

	// _button->SetEvent(std::bind(&CupHeadScene::Save, this));
}

CupHeadScene::~CupHeadScene()
{
}

void CupHeadScene::Init()
{
	//Load();

	CAMERA->SetTarget(_player->GetTransform());
	CAMERA->SetLeftBottom(_bg->LeftBottom());
	CAMERA->SetRightTop(_bg->RightTop());
	CAMERA->SetOffset(CENTER);

	Audio::GetInstance()->Play("bgm");
	Audio::GetInstance()->SetVolume("bgm", 0.5f);

	_button->SetStringEvent(std::bind(&SceneManager::SetScene, SCENE, "SolarSystemScene"));
}

void CupHeadScene::Finalize()
{
	Audio::GetInstance()->Stop("bgm");
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
			_player->Damaged(10.0f);
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

	_button->Update();
	_slider->Update();

	_slider->SetRatio(_player->GetHp() / 100.0f);
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

	if (ImGui::Button("NextScene", { 100,100 }))
	{
		SCENE->SetScene("SolarSystemScene");
	}

	_button->PostRender();
	_slider->PostRender();
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
