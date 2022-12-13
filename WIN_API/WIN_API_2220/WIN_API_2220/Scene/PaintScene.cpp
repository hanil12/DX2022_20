#include "framework.h"
#include "PaintScene.h"

PaintScene::PaintScene()
{
    {
        pens.reserve(3);
        HPEN red = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
        HPEN green = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
        HPEN blue = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));

        pens.push_back(red);
        pens.push_back(green);
        pens.push_back(blue);
    }

    {
        brushes.reserve(3);
        HBRUSH red = CreateSolidBrush(RGB(255, 0, 0));
        HBRUSH green = CreateSolidBrush(RGB(0, 255, 0));
        HBRUSH blue = CreateSolidBrush(RGB(0, 0, 255));

        brushes.push_back(red);
        brushes.push_back(green);
        brushes.push_back(blue);
    }
}

PaintScene::~PaintScene()
{
    for (auto& pen : pens)
        DeleteObject(pen);

    for (auto& brush : brushes)
        DeleteObject(brush);
}

void PaintScene::Update()
{
}

void PaintScene::Render(HDC hdc)
{
    // PEN �� ����
    SelectObject(hdc, pens[0]);
    // Brush �� ����
    SelectObject(hdc, brushes[0]);

    // �簢�� �׸���
    // Rectangle(hdc, 0, 0, 500, 500);

    SelectObject(hdc, brushes[1]);
    SelectObject(hdc, pens[2]);
    // �� �׸���
    // Ellipse(hdc, mousePos.x - 25, mousePos.y - 25, mousePos.x + 25, mousePos.y + 25);

    // ���׸���
    // MoveToEx(hdc, 0, 0, nullptr);
    // LineTo(hdc, mousePos.x, mousePos.y);
}
