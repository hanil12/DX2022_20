#include "framework.h"
#include "Program.h"

#include "../Scene/TutorialScene.h"

Program::Program()
{
	_scene = make_shared<TutorialScene>();
}

Program::~Program()
{
}

void Program::Update()
{
	_scene->Update();
}

void Program::Render()
{
	_scene->Render();
}
