#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(Vector2 center, float radius)
: center(center)
, radius(radius)
{
    _pens.reserve(3);
    HPEN red = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
    HPEN green = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
    HPEN blue = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));

    _pens.push_back(red);
    _pens.push_back(green);
    _pens.push_back(blue);

    _curPen = _pens[1];
}

CircleCollider::~CircleCollider()
{
    for (auto pen : _pens)
    {
        DeleteObject(pen);
    }
}

void CircleCollider::Update()
{
}

void CircleCollider::Render(HDC hdc)
{
    SelectObject(hdc, _curPen);

	float left = center.x - radius;
	float top = center.y - radius;
	float right = center.x + radius;
	float bottom = center.y + radius;
	Ellipse(hdc, left, top, right, bottom);
}

bool CircleCollider::IsCollision(const Vector2& pos)
{
    Vector2 centerToPos = pos - center;
    float length = centerToPos.Length();

    return length <= radius;
}

bool CircleCollider::IsCollision(shared_ptr<CircleCollider> circle)
{
    Vector2 centerToCenter = circle->center - center;
    float length = centerToCenter.Length();

    return length <= (radius + circle->radius);
}

bool CircleCollider::IsCollision(const shared_ptr<class RectCollider> rect)
{
    return rect->IsCollision(shared_from_this());
}
