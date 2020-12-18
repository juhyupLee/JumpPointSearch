#include "StraightLine.h"

StraightLine::StraightLine()
{
	m_VecPoint.reserve(1000);
}

StraightLine::~StraightLine()
{
	Release();
}

std::vector<StraightLine::Point*>& StraightLine::GetLineValue(int32_t startX, int32_t startY, int32_t endX, int32_t endY)
{
	Release();

    int xDelta = endX - startX;
    int yDelta = endY - startY;

    int absXDelta = abs(xDelta);
    int absYDelta = abs(yDelta);

    bool bDeltaDiff = abs(xDelta) > abs(yDelta);

    int error = 0;
    int xCount = 0;
    int yCount = 0;

    int delValue = 0;
    int loopCount = 0;
    bool bFirst = true;

    if (bDeltaDiff)
    {
        while (startX + xCount != endX || startY + yCount != endY)
        {
            if (yDelta == 0)
            {
                if (xDelta > 0)
                {
                    ++xCount;
                }
                else
                {
                    --xCount;
                }
                m_VecPoint.push_back(new Point(startX + xCount, startY + yCount));

            }
            else if (abs(yDelta) == 1)
            {
                if (bFirst)
                {
                    delValue = absXDelta / 2;
                    loopCount = absXDelta - delValue;
                }
                while (true)//error < loopCount)
                {
                    error += absYDelta;
                    if (xDelta > 0)
                    {
                        xCount++;
                    }
                    else
                    {
                        xCount--;
                    }
                    if (error >= loopCount)
                    {
                        break;
                    }
                    m_VecPoint.push_back(new Point(startX + xCount, startY + yCount));
                }
                if (bFirst)
                {
                    error -= loopCount;
                    if (yDelta > 0)
                    {
                        yCount++;
                    }
                    else
                    {
                        yCount--;
                    }
                    loopCount = absXDelta - loopCount;
                    bFirst = false;
                }
                m_VecPoint.push_back(new Point(startX + xCount, startY + yCount));
            }
            else
            {
                while (true)//error < absXDelta)
                {
                    error += absYDelta;

                    if (xDelta > 0)
                    {
                        xCount++;
                    }
                    else
                    {
                        xCount--;
                    }

                    if (error >= absXDelta)
                    {
                        break;
                    }
                    m_VecPoint.push_back(new Point(startX + xCount, startY + yCount));
                }
                error -= absXDelta;
                if (yDelta > 0)
                {
                    yCount++;
                }
                else
                {
                    yCount--;
                }
                m_VecPoint.push_back(new Point(startX + xCount, startY + yCount));
            }
        }
    }
    else
    {
        while (startX + xCount != endX || startY + yCount != endY)
        {

            if (xDelta == 0)
            {
                if (yDelta > 0)
                {
                    yCount++;
                }
                else
                {
                    yCount--;
                }
                m_VecPoint.push_back(new Point(startX + xCount, startY + yCount));
            }
            else if (abs(xDelta) == 1)
            {
                if (bFirst)
                {
                    delValue = absYDelta / 2;
                    loopCount = absYDelta - delValue;
                }
                while (true)
                {
                    error += absXDelta;
                    if (yDelta > 0)
                    {
                        yCount++;
                    }
                    else
                    {
                        yCount--;
                    }
                    if (error >= loopCount)
                    {
                        break;
                    }
                    m_VecPoint.push_back(new Point(startX + xCount, startY + yCount));
                }
                if (bFirst)
                {
                    error -= loopCount;
                    if (xDelta > 0)
                    {
                        xCount++;
                    }
                    else
                    {
                        xCount--;
                    }
                    loopCount = absYDelta - loopCount;
                    bFirst = false;
                }
                m_VecPoint.push_back(new Point(startX + xCount, startY + yCount));
            }
            else
            {
                while (true)
                {
                    error += absXDelta;
                    if (yDelta > 0)
                    {
                        yCount++;
                    }
                    else
                    {
                        yCount--;
                    }
                    if (error >= absYDelta)
                    {
                        break;
                    }
                    m_VecPoint.push_back(new Point(startX + xCount, startY + yCount));
                }
                error -= absYDelta;

                if (xDelta > 0)
                {
                    xCount++;
                }
                else
                {
                    xCount--;
                }
                m_VecPoint.push_back(new Point(startX + xCount, startY + yCount));
            }
        }
    }

	return m_VecPoint;
}

void StraightLine::Release()
{
	for (size_t i = 0; i < m_VecPoint.size(); i++)
	{
		delete m_VecPoint[i];
	}
	m_VecPoint.clear();
}
