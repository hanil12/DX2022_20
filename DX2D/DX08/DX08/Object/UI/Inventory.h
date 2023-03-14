#pragma once
class Inventory
{
public:
	Inventory();
	~Inventory();

	void Update();
	void Render();
	void PostRender();

	void Set();
	void SetPannelPos(Vector2 pos) { _pannel->GetTransform()->SetPosition(pos); Update(); Set(); }

	void BuyItem(string name);
	void SellItem(string name);
	bool AddMoney(UINT amout);
	bool SubMoney(UINT amout);

private:
	shared_ptr<Quad> _pannel;

	Vector2 _slotOffset;
	vector<shared_ptr<Slot>> _slots;
	vector<ItemInfo> _itemDates;

	vector<shared_ptr<ItemIcon>> _icons;

	int _money = 2000;
};

