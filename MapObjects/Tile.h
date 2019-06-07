#pragma once

class CTile
{
public:
    CTile() {}
    CTile(bool block, bool blockSight=false, bool is_explored=false) : m_Blocked {block}, 
                                                                       m_BlockSight {blockSight},
                                                                       m_Explored {is_explored}
    {
        //By default, if a tile is blocked, it is blocking sight!
        if (block)
            m_BlockSight = block;
    }
    ~CTile() { }

    //Getters / setters
    bool isBlocked() { return m_Blocked; }
    bool isBlockingSight() { return m_BlockSight;}
    bool isExplored() { return m_Explored; }
    void setBlocked(bool b) 
    { 
        m_Blocked = b; 
        if (b)
            m_BlockSight = true;
    }
    void setBlockSight(bool b) { m_BlockSight = b; }
    void setWall(void) { m_Blocked = true; m_BlockSight = true; }
    void setFloor(void) { m_Blocked = false; m_BlockSight = false; }
    void setExplored() { m_Explored = true; }

private:
    bool m_Blocked;
    bool m_BlockSight;
    bool m_Explored;
};
