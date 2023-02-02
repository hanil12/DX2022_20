#pragma once
class Cup_Player
{
public:
	enum State
	{
		CUP_IDLE,
		CUP_RUN,
		CUP_SHOT,
		NONE
	};

	Cup_Player();
	~Cup_Player();

	void Update();
	void Render();

	void SetRight();
	void SetLeft();

	void Input();
	void Jump();
	void Shot();

	void SetAction(State state);
	void SetIDLE();

	shared_ptr<Transform> GetTransform() { return _transform; }

private:
	void CreateAction(string name, Action::Type type);

	State _curState = CUP_IDLE;
	State _oldState = NONE ;

	shared_ptr<Transform> _transform;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	float _speed = 300.0f;
	float _jumpPower = 400.0f;
};

