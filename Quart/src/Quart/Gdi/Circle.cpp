# include "Circle.hpp"
# include "..\Window.hpp"

namespace Quart
{
	namespace Gdi
	{
		Circle::Circle(int x, int y, unsigned int diameter, rgb fillColor, rgb strokeColor, int strokeWidth):
			x(x), y(y), diameter(diameter), fillColor(fillColor), strokeColor(strokeColor), strokeWidth(strokeWidth),
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

			if(fillColor != -1)
				brush = CreateSolidBrush(fillColor);
		
			if(strokeColor != -1)
				pen = CreatePen(static_cast<int>(this->penStyle), this->strokeWidth, this->strokeColor);

			if(brush != nullptr)
				oldBrush = (HBRUSH)SelectObject(hdc, brush);
	
			if(pen != nullptr)
				oldPen = (HPEN)SelectObject(hdc, pen);

			Ellipse(hdc, x, y, x + diameter, y + diameter);

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

		std::pair<int, int> Circle::GetPosition() const
		{
			return std::make_pair(this->x, this->y);
		}

		void Circle::SetPosition(const std::pair<int,int>& position, bool forceRedraw)
		{
			this->SetPosition(position.first, position.second, forceRedraw);
		}

		void Circle::SetPosition(int x, int y, bool forceRedraw)
		{
			this->x = x;
			this->y = y;

			if(forceRedraw)
				this->parent->Redraw();
		}

		unsigned int Circle::GetDiameter() const
		{
			return this->diameter;
		}

		void Circle::SetDiameter(unsigned int diameter, bool forceRedraw /* = true */)
		{
			this->diameter = diameter;

			if(forceRedraw)
				this->parent->Redraw();
		}

		rgb Circle::GetFillColor() const
		{
			return rgb(this->fillColor);
		}

		void Circle::SetFillColor(const rgb& color, bool forceRedraw)
		{
			this->fillColor = color;

			if(forceRedraw)
				this->parent->Redraw();
		}

		rgb Circle::GetStrokeColor() const
		{
			return rgb(this->strokeColor);
		}

		void Circle::SetStrokeColor(const rgb& color, bool forceRedraw)
		{
			this->strokeColor = color;

			if(forceRedraw)
				this->parent->Redraw();
		}

		int Circle::GetStrokeWidth() const
		{
			return this->strokeWidth;
		}

		void Circle::SetStrokeWidth(int width, bool forceRedraw)
		{
			this->strokeWidth = width;

			if(forceRedraw)
				this->parent->Redraw();
		}
	}
}