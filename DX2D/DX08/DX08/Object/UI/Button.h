#pragma once
class Button
{
public:
	Button(wstring path);
	~Button();

	void Update();
	void PostRender();

	void SetPostion(Vector2 pos);
	void SetScale(Vector2 scale);

	void SetEvent(CallBack callBack) { _event = callBack; }
	void SetStringEvent(CallBack_String callBack) { _stringEvent = callBack; }

private:
	shared_ptr<Quad> _quad;
	shared_ptr<Collider> _collider;

	CallBack _event;
	CallBack_String _stringEvent;
};

