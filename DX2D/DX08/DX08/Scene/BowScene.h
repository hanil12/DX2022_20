#pragma once
class BowScene : public Scene
{
public:
	BowScene();
	virtual ~BowScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<Bow_Bow> _bow;
};

