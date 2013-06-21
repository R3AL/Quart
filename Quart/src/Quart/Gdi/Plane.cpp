# include "Plane.hpp"
# include "../Window.hpp"

namespace Quart
{
	namespace Gdi
	{
		Plane::Plane(int x, int y, int width, int height, rgb fillColor, rgb strokeColor, int strokeWidth /* = 0 */):
			x(x), y(y), width(width), height(height), fillColor(fillColor), strokeColor(strokeColor), strokeWidth(strokeWidth),
			penStyle(PenStyle::SOLID)
		{

		}

		void Plane::Draw(HDC& hdc, PAINTSTRUCT&)
		{
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

			Rectangle(hdc, this->x, this->y, this->x + this->width, this->y + this->height);

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

		std::pair<int,int> Plane::GetSize() const
		{
			return std::make_pair(this->width, this->height);
		}

		void Plane::SetSize(const std::pair<int,int>& size, bool forceRedraw /* = true */)
		{
			this->SetSize(size.first, size.second, forceRedraw);
		}

		void Plane::SetSize(int width, int height, bool forceRedraw /* = true */)
		{
			this->width  = width;
			this->height = height;

			if(forceRedraw)
				this->parent->Redraw();
		}

		rgb Plane::GetFillColor() const
		{
			return rgb(this->fillColor);
		}

		void Plane::SetFillColor(const rgb& color, bool forceRedraw)
		{
			this->fillColor = color;

			if(forceRedraw)
				this->parent->Redraw();
		}

		rgb Plane::GetStrokeColor() const
		{
			return rgb(this->strokeColor);
		}

		void Plane::SetStrokeColor(const rgb& color, bool forceRedraw)
		{
			this->strokeColor = color;

			if(forceRedraw)
				this->parent->Redraw();
		}

		int Plane::GetStrokeWidth() const
		{
			return this->strokeWidth;
		}

		void Plane::SetStrokeWidth(int width, bool forceRedraw)
		{
			this->strokeWidth = width;

			if(forceRedraw)
				this->parent->Redraw();
		}
	}
}