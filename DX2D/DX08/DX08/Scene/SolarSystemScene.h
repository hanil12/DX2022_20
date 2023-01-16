#pragma once
class SolarSystemScene : public Scene
{
public:
	SolarSystemScene();
	virtual ~SolarSystemScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<Planet> _sun;
	shared_ptr<Planet> _earth;
	shared_ptr<Planet> _moon;
};

