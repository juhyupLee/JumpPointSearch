#pragma once
#include <vector>
#include <iostream>
class StraightLine
{
public:
	struct Point
	{
		Point(int32_t x, int32_t y)
			:m_X(x),
			 m_Y(y)
		{
		}
		int32_t m_X;
		int32_t m_Y;
	};
public:
	StraightLine();
	~StraightLine();
	std::vector<StraightLine::Point*>& GetLineValue(int32_t startX, int32_t startY, int32_t endX, int32_t endY);
private:
	void Release();
	std::vector<StraightLine::Point*> m_VecPoint;
};
