#include <graphics/tile/TileSheetParser.h>
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

std::optional<TileSheet> TileSheetParser::getNextSheet()
{
    if (m_cfgIter >= m_cfgIterEnd)
        return std::nullopt;

    TileSheet ts;
    
    if (!generateTileCoordinates(*m_cfgIter, ts))
        return std::nullopt;

    if (m_cfgIter <= m_cfgIterEnd)
        ++m_cfgIter;

    return { std::move(ts) };
}

bool TileSheetParser::generateTileCoordinates(const TileSheetConfig& tsc, TileSheet& dest)
{
    SDL_Rect rect; 
    for (int y = 0; y < tsc.imageHeight; y += tsc.tileHeight)
    {
        for (int x = 0; x < tsc.imageWidth; x += tsc.tileWidth)
        {
            rect = {
                .x = x,
                .y = y,
                .w = tsc.tileWidth,
                .h = tsc.tileHeight
            };
            dest.addTile(rect);
        }
    }
    dest.setLocation(tsc.filename);
    return true;
}

