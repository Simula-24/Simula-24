#include "TileSheet.h"
#include <cassert>
using simula24::TileSheet;


TileSheet::TileSheet()
    : m_sheet(nullptr)
{
}

TileSheet::~TileSheet()
{
    if (m_sheet)
        SDL_DestroyTexture(m_sheet);
}

const SDL_Rect& TileSheet::getTile(size_t id) const
{
    assert(id < m_tiles.size());

    return m_tiles[id];
}

void TileSheet::addTile(const SDL_Rect& tileLoc)
{
    m_tiles.push_back(tileLoc);
}

