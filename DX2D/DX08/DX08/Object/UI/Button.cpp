#include "framework.h"
#include "Button.h"

Button::Button(wstring path)
{
	_quad = make_shared<Quad>(path);
	_collider = make_shared<RectCollider>(_quad->GetImageSize());
	_collider->GetTransform()->SetParent(_quad->GetTransform());
}

Button::~Button()
{
}

void Button::Update()
{
	_collider->Update();
	_quad->Update();

	if (_collider->IsCollision(MOUSE_POS))
	{
		if (KEY_PRESS(VK_LBUTTON))
		{
			_collider->SetRed();
		}

		if (KEY_UP(VK_LBUTTON))
		{
			if (_event != nullptr)
				_event();
			if (_stringEvent != nullptr)
				_stringEvent("NONE");
		}
	}
	else
	{
		_collider->SetGreen();
	}
}

void Button::PostRender()
{
	_collider->Render();
	_quad->Render();
}

void Button::SetPostion(Vector2 pos)
{
	_quad->GetTransform()->SetPosition(pos);
}

void Button::SetScale(Vector2 scale)
{
	_quad->GetTransform()->SetScale(scale);
}
