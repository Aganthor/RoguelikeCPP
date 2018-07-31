#pragma once

class CTile
{
public:
    CTile() {};
    CTile(bool block, bool blockSight=false) : m_Blocked {block}, m_BlockSight {blockSight}
    {
        //By default, if a tile is blocked, it is blocking sight!
        if (block)
            m_BlockSight = block;
    }
    ~CTile() { };

    //Getters / setters
    bool isBlocked() { return m_Blocked; }
    bool isBlockingSight() { return m_BlockSight;}
    void setBlocked(bool b) 
    { 
        m_Blocked = b; 
        if (b)
            m_BlockSight = true;
    }
    void setBlockSight(bool b) { m_BlockSight = b; }
    void setWall(void) { m_Blocked = true; m_BlockSight = true; }
    void setFloor(void) { m_Blocked = false; m_BlockSight = false; }

private:
    bool m_Blocked;
    bool m_BlockSight;
};