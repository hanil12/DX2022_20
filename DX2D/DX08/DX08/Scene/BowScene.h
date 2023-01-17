#pragma once
class BowScene : public Scene
{
public:
	BowScene();
	virtual ~BowScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<Bow_Bow> _bow;
};

