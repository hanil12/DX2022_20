#pragma once
class Cup_Bg
{
public:
	Cup_Bg();
	~Cup_Bg();

	void Update();
	void Render();
	void PostRender();

	void SetPos(Vector2 pos) { _bg->GetTransform()->GetPos() = pos; }
	void SetPlayer(shared_ptr<Cup_Player> player) { _player = player; }

	Vector2 LeftBottom();
	Vector2 RightTop();

private:
	weak_ptr<Cup_Player> _player;

	shared_ptr<Quad> _bg;

	vector<shared_ptr<RectCollider>> _colliders;
	shared_ptr<RectCollider> _collider1;
	shared_ptr<Quad> _ground1;

	shared_ptr<RectCollider> _collider2;
	shared_ptr<Quad> _ground2;
};

