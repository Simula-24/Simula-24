#include <game/tile/TileSheetParser.h>
#include <stdio.h>
using simula24::Status;
using simula24::TileSheet;
using simula24::TileSheetParser;

TileSheetParser::TileSheetParser()
    : m_isGood(false), m_cfgIter(nullptr)
{
}

TileSheetParser::~TileSheetParser()
{
}

Status TileSheetParser::loadConfig(const stl::string& name)
{
    Status stat = m_tcfg.load(name);
    if (stat == OK)
    {
        m_isGood = true;
        m_cfgIter = m_tcfg.getConfigIterBegin();
        m_cfgIterEnd = m_tcfg.getConfigIterEnd();
    }
    
    return stat;
}

stl::shared_ptr<TileSheet> TileSheetParser::getNextSheet()
{
    if (m_cfgIter > m_cfgIterEnd)
        return stl::shared_ptr<TileSheet>();
    
    if(!generateTileCoordinates(*m_cfgIter))
        return stl::shared_ptr<TileSheet>();

    if (m_cfgIter <= m_cfgIterEnd)
        ++m_cfgIter;

    return stl::make_shared<TileSheet>(1);
}

bool TileSheetParser::generateTileCoordinates(const TileSheetConfig& tsc)
{
    printf("hello niga\n");
    return true;
}

