#pragma once
class CupHeadScene : public Scene
{
public:
	CupHeadScene();
	virtual ~CupHeadScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void PostRender() override;
	virtual void Render() override;
private:
	shared_ptr<Cup_Player> _player;
	shared_ptr<Cup_Monster> _monster;
	shared_ptr<Cup_Bg> _bg;

	// 과제
	// 몬스터 혹은 플레이어가 죽었을 때,
	// 1초 간격으로 모자이크 처리되면서 죽기
	// (모자이크 value1이 서서히 감소하면서..)
};

