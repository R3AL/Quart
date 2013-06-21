# include "Line.hpp"
# include "..\Window.hpp"

namespace Quart
{
	namespace Gdi
	{
		Point2::Point2(int x1, int y1, int x2, int y2):
			x1(x1), y1(y1), x2(x2), y2(y2)
		{

		}

		Point2 operator+(const Point2& p1, const Point2& p2)
		{
			return Point2(p1.x1 + p2.x1, p1.y1 + p2.y1,
						  p1.x2 + p2.x2, p1.y2 + p2.y2);
		}

		Point2 operator-(const Point2& p1, const Point2& p2)
		{
			return Point2(p1.x1 - p2.x1, p1.y1 - p2.y1,
						  p1.x2 - p2.x2, p1.y2 - p2.y2);
		}

		Point2 operator*(const Point2& p1, const Point2& p2)
		{
			return Point2(p1.x1 * p2.x1, p1.y1 * p2.y1,
						  p1.x2 * p2.x2, p1.y2 * p2.y2);
		}

		Point2 operator/(const Point2& p1, const Point2& p2)
		{
			return Point2(p1.x1 / p2.x1, p1.y1 / p2.y1,
						  p1.x2 / p2.x2, p1.y2 / p2.y2);
		}

		Point2& Point2::operator+=(const Point2& p)
		{
			*this = (*this) + p;
			return *this;
		}

		Point2& Point2::operator-=(const Point2& p)
		{
			*this = (*this) - p;
			return *this;
		}

		Point2& Point2::operator*=(const Point2& p)
		{
			*this = (*this) * p;
			return *this;
		}

		Point2& Point2::operator/=(const Point2& p)
		{
			*this = (*this) / p;
			return *this;
		}

		Line::Line(int x1, int y1, int x2, int y2, rgb strokeColor, int strokeWidth):
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

		Point2 Line::GetPosition() const
		{
			return Point2(x1, y1, x2, y2);
		}

		void Line::SetPosition(const Point2& position, bool forceRedraw /* = true */)
		{
			this->SetPosition(position.x1, position.y1,
							  position.x2, position.y2, forceRedraw);
		}

		void Line::SetPosition(int x1, int y1, int x2, int y2, bool forceRedraw /* = true */)
		{
			this->SetPoint1(x1, y1, false);
			this->SetPoint2(x2, y2, forceRedraw);
		}

		std::pair<int, int> Line::GetPoint1() const
		{
			return std::make_pair(this->x1, this->y1);
		}

		std::pair<int, int> Line::GetPoint2() const
		{
			return std::make_pair(this->x2, this->y2);
		}

		void Line::SetPoint1(const std::pair<int,int>& position, bool forceRedraw)
		{
			this->SetPoint1(position.first, position.second, forceRedraw);
		}

		void Line::SetPoint1(int x, int y, bool forceRedraw)
		{
			this->x1 = x;
			this->y1 = y;

			if(forceRedraw)
				this->parent->Redraw();
		}

		void Line::SetPoint2(const std::pair<int,int>& position, bool forceRedraw)
		{
			this->SetPoint2(position.first, position.second, forceRedraw);
		}

		void Line::SetPoint2(int x, int y, bool forceRedraw)
		{
			this->x2 = x;
			this->y2 = y;

			if(forceRedraw)
				this->parent->Redraw();
		}

		int Line::GetStrokeWidth() const
		{
			return this->strokeWidth;
		}

		void Line::SetStrokeWidth(int width, bool forceRedraw)
		{
			this->strokeWidth = width;

			if(forceRedraw)
				this->parent->Redraw();
		}

		rgb Line::GetStrokeColor() const
		{
			return this->strokeColor;
		}

		void Line::SetStrokeColor(const rgb& color, bool forceRedraw)
		{
			this->strokeColor = color;

			if(forceRedraw)
				this->parent->Redraw();
		}
	}
}