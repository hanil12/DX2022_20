#include "framework.h"
#include "Cup_Player.h"

using namespace tinyxml2;

Cup_Player::Cup_Player()
{
	wstring srvPath = L"Resource/Texture/CupHead/Idle.png";
	CreateAction("Idle", Action::Type::LOOP);
	CreateAction("Run", Action::Type::LOOP);
	CreateAction("AimStraightShot", Action::Type::END);
	_actions[State::CUP_SHOT]->SetCallBack(std::bind(&Cup_Player::SetIDLE, this));

	_transform = make_shared<Transform>();

	for (auto sprite : _sprites)
		sprite->GetTransform()->SetParent(_transform);

	_transform->GetScale() *= 0.7f;

	_oldState = State::CUP_IDLE;
	_actions[State::CUP_IDLE]->Play();
}

Cup_Player::~Cup_Player()
{
}

void Cup_Player::Update()
{
	Shot();
	Input();

	for (auto sprite : _sprites)
		sprite->Update();

	for (auto action : _actions)
		action->Update();

	_transform->UpdateSRT();
}

void Cup_Player::Render()
{
	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();
}

void Cup_Player::SetRight()
{
	for (auto sprite : _sprites)
	{
		sprite->GetLeftRight() = 0;
	}
}

void Cup_Player::SetLeft()
{
	for (auto sprite : _sprites)
	{
		sprite->GetLeftRight() = 1;
	}
}

void Cup_Player::Input()
{
	if (KEY_PRESS('A'))
	{
		_transform->GetPos().x -= _speed * DELTA_TIME;
		SetAction(State::CUP_RUN);

		SetLeft();
	}

	if (KEY_PRESS('D'))
	{
		_transform->GetPos().x += _speed * DELTA_TIME;
		SetAction(State::CUP_RUN);

		SetRight();
	}

	if (KEY_UP('A') || KEY_UP('D'))
	{
		SetAction(State::CUP_IDLE);
	}
}

void Cup_Player::Jump()
{
}

void Cup_Player::Shot()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		SetAction(State::CUP_SHOT);
	}
}

void Cup_Player::SetAction(State state)
{
	_curState = state;

	if (_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
}

void Cup_Player::SetIDLE()
{
	SetAction(State::CUP_IDLE);
}

void Cup_Player::CreateAction(string name, Action::Type type)
{
	wstring wName = wstring(name.begin(), name.end());
	wstring srvPath = L"Resource/Texture/CupHead/" + wName + L".png";
	shared_ptr<SRV> srv = SRV_ADD(srvPath);

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	string path = "Resource/XML/" + name + ".xml";
	document->LoadFile(path.c_str());

	XMLElement* textureAtlas = document->FirstChildElement();
	XMLElement* row = textureAtlas->FirstChildElement();

	vector<Action::Clip> clips;

	float wAverage = 0;
	float hAverage = 0;

	int count = 0;

	while (true)
	{
		if (row == nullptr)
			break;

		int x = row->FindAttribute("x")->IntValue();
		int y = row->FindAttribute("y")->IntValue();
		int w = row->FindAttribute("w")->IntValue();
		int h = row->FindAttribute("h")->IntValue();

		clips.emplace_back(x, y, w, h, srv);

		wAverage += w;
		hAverage += h;
		count++;

		row = row->NextSiblingElement();
	}

	wAverage /= count;
	hAverage /= count;

	string actionName = "CUP_" + name;
	_actions.emplace_back(make_shared<Action>(clips, actionName, type));
	_sprites.emplace_back(make_shared<Sprite>(srvPath, Vector2(wAverage, hAverage)));
}
