#include "framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	_quad = make_shared<Quad>(L"Resource/Texture/SpyFamilly2.png");
	_quad->GetTransform()->GetPos() = { WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f };
	_quad->GetTransform()->GetScale() *= 0.5f;

	_quad2 = make_shared<Quad>(L"Resource/Texture/Pochita.png");
	_quad2->GetTransform()->SetParent(_quad->GetTransform());
	_quad2->GetTransform()->GetPos().x += 500;

	_view = make_shared<MatrixBuffer>();
	_projection = make_shared<MatrixBuffer>();

	XMMATRIX projectM = XMMatrixOrthographicOffCenterLH(0,WIN_WIDTH, 0, WIN_HEIGHT, -1.0f, 1.0f);

	_projection->SetData(projectM);
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Update()
{
	if (GetAsyncKeyState('A') & 0x8001)
	{
		_quad->GetTransform()->GetPos().x -= 0.1f;
	}
	if (GetAsyncKeyState('D') & 0x8001)
	{
		_quad->GetTransform()->GetPos().x += 0.1f;
	}
	if (GetAsyncKeyState('W') & 0x8001)
	{
		_quad->GetTransform()->GetScale().x += 0.01f;
	}
	if (GetAsyncKeyState('S') & 0x8001)
	{
		_quad->GetTransform()->GetScale().y += 0.01f;
	}

	if (GetAsyncKeyState('P') & 0x8001)
	{
		_quad->GetTransform()->GetAngle() += 0.001f;
	}

	if (GetAsyncKeyState('O') & 0x8001)
	{
		_quad->GetTransform()->GetAngle() -= 0.001f;
	}

	_quad->Update();
	_quad2->Update();

	_view->Update();
	_projection->Update();
}

void TutorialScene::Render()
{
	_view->SetVSBuffer(1);
	_projection->SetVSBuffer(2);
	_quad->Render();
	_quad2->Render();
}
