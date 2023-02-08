#pragma once
class Cup_Monster
{
public:
	Cup_Monster();
	~Cup_Monster();

	void Update();
	void Render();

	shared_ptr<Transform> GetTransform() { return _transform; }

private:
	void CreateAction();

	shared_ptr<Transform> _transform;
	shared_ptr<RectCollider> _collider;

	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _action;
};

