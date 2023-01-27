#pragma once
class TutorialScene : public Scene
{
public:
	TutorialScene();
	virtual ~TutorialScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<Quad> _quad;

	// ������۸� �̿��ؼ�
	// -> 1. Shader�� �̿��ؼ� �¿���� ���Ѿ߉�
	// -> 2. Shader�� �ѱ� ����(����)�� �����߉�
	// �¿� ���� ��Ű��
};

