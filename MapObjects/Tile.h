#pragma once

class CTile
{
public:
    CTile();
    CTile(bool block, bool blockSight=false) : m_Blocked(block), m_BlockSight(blockSight)
    {
        //By default, if a tile is blocked, it is blocking sight!
        if (!blockSight)
            m_BlockSight = block;
    }
    ~CTile();

    bool isBlocked() { return m_Blocked; }
    bool isBlockingSight() { return m_BlockSight;}

private:
    bool m_Blocked;
    bool m_BlockSight;
};