#pragma once

class CTile
{
public:
    CTile() { };
    CTile(bool block, bool blockSight=false) : m_Blocked(block), m_BlockSight(blockSight)
    {
        //By default, if a tile is blocked, it is blocking sight!
        if (!blockSight)
            m_BlockSight = block;
    }
    ~CTile() { };

    //Getters / setters
    bool isBlocked() { return m_Blocked; }
    bool isBlockingSight() { return m_BlockSight;}

    void setBlocked(bool b) { m_Blocked = b; }
    void setBlockSight(bool b) { m_BlockSight = b; }
    void setBoth(bool block, bool block_sight) { m_Blocked = block; m_BlockSight = block_sight;}

private:
    bool m_Blocked;
    bool m_BlockSight;
};