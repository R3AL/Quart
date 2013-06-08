# include "Line.hpp"

namespace Quart
{
	Line::Line(int x1, int y1, int x2, int y2, unsigned long strokeColor /* = 0 */, int strokeWidth /* = 0 */):
		x1(x1), y1(y1), x2(x2), y2(y2), strokeColor(strokeColor), strokeWidth(strokeWidth),
		penStyle(PenStyle::SOLID)
	{

	}

	void Line::Draw(HDC& hdc, PAINTSTRUCT&)
	{
		MoveToEx(hdc, this->x1, this->y1, nullptr);

		HBRUSH brush = nullptr,
			oldBrush = nullptr;
		HPEN pen     = nullptr,
			oldPen   = nullptr;

		if(strokeColor != 0)
			pen = CreatePen(static_cast<int>(this->penStyle), this->strokeWidth, this->strokeColor);

		if(pen != nullptr)
			oldPen = (HPEN)SelectObject(hdc, pen);

		LineTo(hdc, this->x2, this->y2);

		if(pen != nullptr)
		{
			SelectObject(hdc, oldPen);
			DeleteObject(pen);
		}
	}

	PenStyle Line::GetPenStyle() const
	{
		return this->penStyle;
	}

	void Line::SetPenStyle(PenStyle style)
	{
		this->penStyle = style;
	}
}