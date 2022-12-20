#include "framework.h"
#include "Maze.h"

Maze::Maze()
{
	Vector2 offset = { 400,150 };

	for (int y = 0; y < _poolCountY; ++y)
	{
		for (int x = 0; x < _poolCountX; ++x)
		{
			shared_ptr<Block> block = make_shared<Block>();
			block->SetType(Block::Type::DIABLE);
			Vector2 distance = { 17.0f * x, 17.0f * y };
			block->SetPosition(offset + distance);

			_blocks.push_back(block);
			_blockMatrix[y][x] = block;
		}
	}

	CreateMaze();
}

Maze::~Maze()
{
	for (int y = 0; y < _poolCountY; ++y)
	{
		for (int x = 0; x < _poolCountX; ++x)
		{
			_blockMatrix[y][x] = nullptr;
		}
	}
}

void Maze::Update()
{
	for (auto block : _blocks)
		block->Update();
}

void Maze::Render(HDC hdc)
{
	for (auto block : _blocks)
		block->Render(hdc);

	wstring maze = L"Maze!!!";
	TextOut(hdc, CENTER_X - 100, 100, maze.c_str(), maze.size());
}

void Maze::CreateMaze()
{
	for (int y = 0; y < _poolCountY; ++y)
	{
		for (int x = 0; x < _poolCountX; ++x)
		{
			if (x % 2 == 0 || y % 2 == 0)
			{
				_blockMatrix[y][x]->SetType(Block::Type::DIABLE);
			}
			else
				_blockMatrix[y][x]->SetType(Block::Type::ABLE);
		}
	}

	// �������� ���� Ȥ�� �Ʒ��� ���� �մ� �۾�
	for (int y = 0; y < _poolCountY; ++y)
	{
		for (int x = 0; x < _poolCountX; ++x)
		{
			// ������
			if (x == 1 && y == 1)
			{
				_blockMatrix[y][x]->SetType(Block::Type::START);
			}

			if (x % 2 == 0 || y % 2 == 0)
				continue;

			// �̷ΰ� ������ �����̸� �� �ձ� ����
			if (x == _poolCountX - 2 && y == _poolCountY - 2)
			{
				_blockMatrix[y][x]->SetType(Block::Type::END);
				continue;
			}

			// �������� ���� Ȥ�� �Ʒ��θ� �վ��� �� ���� �Ȼ���� �� ����ó��
			if (y == _poolCountY - 2)
			{
				_blockMatrix[y][x + 1]->SetType(Block::Type::ABLE);
				continue;
			}

			if (x == _poolCountX - 2)
			{
				_blockMatrix[y + 1][x]->SetType(Block::Type::ABLE);
				continue;
			}

			const int randValue = rand() % 2;
			if (randValue == 0)
				_blockMatrix[y][x + 1]->SetType(Block::Type::ABLE);
			else
				_blockMatrix[y + 1][x]->SetType(Block::Type::ABLE);

		}
	}
}
