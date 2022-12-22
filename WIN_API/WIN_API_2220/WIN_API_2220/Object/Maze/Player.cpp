#include "framework.h"
#include "Player.h"

Player::Player(shared_ptr<Maze> maze)
: _maze(maze)
{
	_pos = _maze->GetStartPos();
	_maze->GetBlock(_pos)->SetType(Block::Type::PLAYER);
	RightHand();
}

Player::~Player()
{
}

void Player::Update()
{
	if (_pathIndex >= _path.size())
		return;

	_time += 0.2f;

	if (_time > 1.0f)
	{
		_time = 0.0f;
		_pos = _path[_pathIndex];

		if (_pathIndex != 0)
		{
			Vector2 temp = _path[_pathIndex - 1];
			_maze->GetBlock(temp)->SetType(Block::Type::FOOT_PRINT);
		}

		_pathIndex++;
	}
	_maze->GetBlock(_pos)->SetType(Block::Type::PLAYER);
}

void Player::RightHand()
{
	Vector2 pos = _pos; // 현재 위치
	_path.push_back(pos);
	Vector2 endPos = _maze->GetEndPos();
	_dir = Dir::DIR_UP;

	Vector2 frontPos[4] =
	{
		Vector2 {0, -1}, // UP 0
		Vector2 {-1, 0}, // LEFT 1
		Vector2 {0, 1}, // DOWN 2
		Vector2 {1, 0} // RIGHT 3
	};

	while (pos != endPos)
	{
		// 현재 바라보는 방향 기준으로 오른쪽으로 갈 수 있는지 확인
		int newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
		Vector2 oldDirVector2 = frontPos[_dir]; // 기존 방향
		Vector2 newDirVector2 = frontPos[newDir]; // 새로운 방향

		if (CanGo(pos + newDirVector2))
		{
			_dir = static_cast<Dir>(newDir);
			pos += newDirVector2;
			_path.push_back(pos);
		}
		
		// 현재 바라보는 방향 기준으로 전진할 수 있는지 확인
		else if (CanGo(pos + oldDirVector2))
		{
			pos += oldDirVector2;
			_path.push_back(pos);
		}

		// 오른쪽, 앞이 다 막혀있다면 왼쪽으로 회적
		else
		{
			_dir = static_cast<Dir>((_dir + 1 + DIR_COUNT) % DIR_COUNT);
		}
	}

	// Stack
	stack<Vector2> s;

	for (int i = 0; i < _path.size() - 1; i++)
	{
		if (s.empty() == false && s.top() == _path[i + 1])
		{
			s.pop();
		}
		else
			s.push(_path[i]);
	}

	s.push(_path.back());
	_path.clear();

	while (true)
	{
		if (s.empty() == true)
			break;
		_path.push_back(s.top());
		s.pop();
	}

	std::reverse(_path.begin(), _path.end());
}

bool Player::CanGo(Vector2 pos)
{
	if (_maze->GetBlock(pos)->GetType() == Block::Type::DISABLE)
		return false;

	return true;
}
