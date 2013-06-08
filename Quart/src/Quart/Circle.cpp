# include "Circle.hpp"

namespace Quart
{
	Circle::Circle(int x, int y, unsigned int radius, unsigned long fillColor, unsigned long strokeColor, int strokeWidth):
		x(x), y(y), radius(radius), fillColor(fillColor), strokeColor(strokeColor), strokeWidth(strokeWidth),
		penStyle(PenStyle::SOLID)
	{

	}

	void Circle::Draw(HDC& hdc, PAINTSTRUCT&)
	{
		MoveToEx(hdc, this->x, this->y, nullptr);

		HBRUSH brush = nullptr,
			oldBrush = nullptr;
		HPEN pen     = nullptr,
			oldPen	 = nullptr;

		if(fillColor != 0)
			brush = CreateSolidBrush(fillColor);
		
		if(strokeColor != 0)
			pen = CreatePen(static_cast<int>(this->penStyle), this->strokeWidth, this->strokeColor);

		if(brush != nullptr)
			oldBrush = (HBRUSH)SelectObject(hdc, brush);
	
		if(pen != nullptr)
			oldPen = (HPEN)SelectObject(hdc, pen);

		Ellipse(hdc, x, y, x + radius, y + radius);

		if(brush != nullptr)
		{
			SelectObject(hdc, oldBrush);
			DeleteObject(brush);
		}

		if(pen != nullptr)
		{
			SelectObject(hdc, oldPen);
			DeleteObject(pen);
		}

	}

	PenStyle Circle::GetPenStyle() const
	{
		return this->penStyle;
	}

	void Circle::SetPenStyle(PenStyle style)
	{
		this->penStyle = style;
	}
}