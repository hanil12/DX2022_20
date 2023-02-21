#pragma once
class SpriteScene : public Scene
{
public:
	SpriteScene();
	virtual ~SpriteScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	shared_ptr<Sprite> _sprite;
	int curFrameX = 0;
	int curFrameY = 0;

	// ����ȭ
	// - ������ ����� �Ͼ�� ����
	// - GPU���� DrawCall�� ���� �����༭.

	// 1. �������� �ø�
	// 2. ��Ŭ���� �ø�

	// Instancing
	// -> Vertex ���۸� �̿�
};

