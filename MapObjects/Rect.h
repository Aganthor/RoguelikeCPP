#pragma once

#include <utility>

class CRect
{
public:
    CRect(int x, int y, int w, int h) : m_x1 {x}, m_y1 {y}
    {
        m_x2 = x + w;
        m_y2 = y + h;
    }
    ~CRect() {}

    int getX1() const { return m_x1; }
    int getX2() const { return m_x2; }
    int getY1() const { return m_y1; }
    int getY2() const { return m_y2; }

    using Point = std::pair<int,int>;
    const Point getCenter() const
    {
        return std::make_pair((m_x1 + m_x2) / 2, (m_y1 + m_y2) / 2);
    }
    bool Intersect(const CRect& other) const
    {
        return ((m_x1 <= other.getX2()) && (m_x2 >= other.getX1()) && 
               (m_y1 <= other.getY2()) && (m_y2 >= other.getY1()));
    }

private:
    int m_x1;
    int m_x2;
    int m_y1;
    int m_y2;
};
