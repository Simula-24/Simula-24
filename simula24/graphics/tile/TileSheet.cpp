#include "TileSheet.h"
#include <cassert>
#include <utility>
using simula24::TileSheet;


TileSheet::TileSheet()
    : m_sheet(nullptr)
{
}

TileSheet::TileSheet(TileSheet&& other)
    : m_sheet(std::exchange(other.m_sheet, nullptr)), 
      m_tiles(std::move(other.m_tiles))
{
}

TileSheet& TileSheet::operator=(TileSheet&& other)
{
    m_sheet = std::exchange(other.m_sheet, nullptr);
    m_tiles = std::move(other.m_tiles);
    return *this;
}

TileSheet::~TileSheet()
{
    if (m_sheet)
        SDL_DestroyTexture(m_sheet);
}

