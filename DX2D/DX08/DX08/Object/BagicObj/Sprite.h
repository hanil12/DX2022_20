#pragma once
class Sprite : public Quad
{
public:
	Sprite(wstring file, Vector2 size);
	Sprite(wstring file, Vector2 maxFrame, Vector2 size);
	virtual ~Sprite();

	virtual void Update() override;
	virtual void Render() override;

	virtual void CreateMesh() override;
	virtual void CreateMaterial(wstring file) override;

	void SetReverse();

	void SetCurFrame(Vector2 curFrame);
	void SetActionClip(Action::Clip clip);

	Vector2 GetClipSize() { return _clipSize; }

private:
	shared_ptr<ActionBuffer> _actionBuffer;
	shared_ptr<ReverseBuffer> _reverseBuffer;
	Vector2 _maxFrame;
	Vector2 _clipSize;
};

