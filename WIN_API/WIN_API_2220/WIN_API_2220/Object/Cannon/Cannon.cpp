#include "framework.h"
#include "Cannon.h"

Cannon::Cannon()
{
	_body = make_shared<CircleCollider>(Vector2(CENTER_X, CENTER_Y), 30.0f);
}

Cannon::~Cannon()
{
}

void Cannon::Update()
{
	if (GetAsyncKeyState(VK_RIGHT))
	{
		_body->GetCenter().x += 2.0f;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		_body->GetCenter().x -= 2.0f;
	}

	_body->Update();
}

void Cannon::Render(HDC hdc)
{
	_body->Render(hdc);
}
