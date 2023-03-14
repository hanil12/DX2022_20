#include "framework.h"
#include "Inventory.h"

Inventory::Inventory()
{
	_pannel = make_shared<Quad>(L"Resource/Texture/UI/InventoryPanel.png");

	_slotOffset = Vector2(100, 100);

	for (int y = 1; y > -2; y--)
	{
		for (int x = -1; x < 2; x++)
		{
			shared_ptr<Slot> slot = make_shared<Slot>();
			slot->SetPosition(Vector2(_slotOffset.x * x, _slotOffset.y * y));
			slot->SetParent(_pannel->GetTransform());
			_slots.push_back(slot);
		}
	}

	for (int i = 0; i < 9; i++)
	{
		shared_ptr<ItemIcon> icon = make_shared<ItemIcon>();
		_icons.push_back(icon);
	}

	_itemDates.resize(9);

	Set();
}

Inventory::~Inventory()
{
}

void Inventory::Update()
{
	_pannel->Update();

	for (auto icon : _icons)
		icon->Update();

	for (auto slot : _slots)
		slot->Update();
}

void Inventory::Render()
{
	_pannel->Render();

	for (auto slot : _slots)
		slot->Render();

	for (auto icon : _icons)
		icon->Render();
}

void Inventory::PostRender()
{
	RECT rect;
	// 750 WIN_HEIGHT - 170... 가로세로 200, 30
	rect.left = 650;
	rect.right = 850;
	rect.bottom = WIN_HEIGHT - 185;
	rect.top = WIN_HEIGHT - 155;

	wstring money = to_wstring(_money);
	DirectWrite::GetInstance()->RenderText(L"Money : " + money, rect, 20.0f, FONT_YOON);
}

void Inventory::Set()
{
	for (int i = 0; i < _icons.size(); i++)
	{
		_icons[i]->SetPostion(_slots[i]->GetTransform()->GetWorldPos());
		_icons[i]->SetItem(_itemDates[i]);
	}
}

void Inventory::BuyItem(string name)
{
	ItemInfo info = DATA_M->GetItemByName(name);

	if (info.name == "" || _money - info.price < 0)
		return;


	auto iter = std::find_if(_itemDates.begin(), _itemDates.end(), [](const ItemInfo& info)-> bool
		{
			if (info.name == "")
				return true;
			return false;
		});

	if (iter == _itemDates.end())
	{
		return;
	}

	*iter = info;
	Set();

	SubMoney(info.price);
}

void Inventory::SellItem(string name)
{
	auto iter = std::find_if(_itemDates.begin(), _itemDates.end(), 
		[name](const ItemInfo& info)-> bool
		{
			if (info.name == name)
				return true;
			return false;
		});

	if (iter == _itemDates.end())
		return;

	AddMoney(iter->price);
	iter->SetEmpty();

	Set();
}

bool Inventory::AddMoney(UINT amout)
{
	_money += amout;
	return true;
}

bool Inventory::SubMoney(UINT amout)
{
	if (_money - amout < 0)
		return false;

	_money -= amout;
	return true;
}
