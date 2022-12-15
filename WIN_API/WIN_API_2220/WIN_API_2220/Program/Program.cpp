#include "framework.h"
#include "Program.h"

#include "../Scene/PaintScene.h"
#include "../Scene/CollisionScene.h"
#include "../Scene/LineScene.h"
#include "../Scene/CannonScene.h"

Program::Program()
{
	_sceneTable["Paint"] = make_shared<PaintScene>();
	_sceneTable["Collision"] = make_shared<CollisionScene>();
	_sceneTable["Cannon"] = make_shared<CannonScene>();
	_sceneTable["Line"] = make_shared<LineScene>();

	_curScene = _sceneTable["Line"];
}

Program::~Program()
{

}

void Program::Update()
{
	_curScene->Update();
}

void Program::Render(HDC hdc)
{
	_curScene->Render(hdc);
}
