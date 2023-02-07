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

private:
	weak_ptr<Cup_Player> _player;

	shared_ptr<Quad> _bg;

	shared_ptr<RectCollider> _collider;
	shared_ptr<Quad> _ground;
};

