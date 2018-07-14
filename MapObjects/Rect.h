#pragma once

class CRect
{
public:
    CRect(int x, int y, int w, int h) : m_x1 {x}, m_y1 {y}
    {
        m_x2 = x + w;
        m_y2 = y + h;
    }
    ~CRect() {};

    const int getX1() const { return m_x1; }
    const int getX2() const { return m_x2; }
    const int getY1() const { return m_y1; }
    const int getY2() const { return m_y2; }

private:
    int m_x1;
    int m_x2;
    int m_y1;
    int m_y2;
};