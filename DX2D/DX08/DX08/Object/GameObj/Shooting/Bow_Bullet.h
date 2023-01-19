#pragma once
class Bow_Bullet
{
public:
	Bow_Bullet();
	~Bow_Bullet();

	void Update();
	void Render();

	bool isActive = false;

	shared_ptr<Transform> GetTransform() { return _quad->GetTransform(); }
	void SetDirection(Vector2 dir);

private:
	shared_ptr<Quad> _quad;

	float _delay = 3.0f;
	float _check = 0.0f;
	float _speed = 300.0f;
	Vector2 _dir = { 0,0 };
};

