#include "framework.h"
#include "InventoryScene.h"

InventoryScene::InventoryScene()
{
	_inventory = make_shared<Inventory>();
	_inventory->SetPannelPos(CENTER);
}

InventoryScene::~InventoryScene()
{
}

void InventoryScene::Update()
{
	_inventory->Update();
}

void InventoryScene::Render()
{
	_inventory->Render();
}

void InventoryScene::PostRender()
{
	RECT rect;
	rect.left = CENTER_X - 50;
	rect.right = CENTER_X + 50;
	rect.top = CENTER_Y + 50;
	rect.bottom = CENTER_Y - 50;
	DirectWrite::GetInstance()->RenderText(L"æ»≥Á«œººø‰", rect, 40.0f, L"Ownglyph 2022 UWY Yoon Yeong", XMFLOAT4(1,0,0,1));
}
