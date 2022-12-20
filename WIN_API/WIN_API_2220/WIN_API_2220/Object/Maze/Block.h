#pragma once
class Block
{
public:
	enum class Type
	{
		NONE,
		ABLE,
		DIABLE,
		START,
		END
	};

	Block();
	~Block();

	void Update();
	void Render(HDC hdc);

	void SetPosition(Vector2 pos) { _rect->GetCenter() = pos; }

	void SetType(Type type) { _type = type; }
	Type GetType() { return _type; }

private:
	Type _type = Type::NONE;

	vector<HBRUSH> _brushes;
	shared_ptr<RectCollider> _rect;
};

