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
      m_tiles(std::move(other.m_tiles)),
      m_location(std::move(other.m_location))
{
}

TileSheet& TileSheet::operator=(TileSheet&& other)
{
    m_sheet = std::exchange(other.m_sheet, nullptr);
    m_tiles = std::move(other.m_tiles);
    m_location=std::move(other.m_location);

    return *this;
}

TileSheet::TileSheet(const TileSheet& other)
{
    m_location = other.m_location;
    m_sheet = other.m_sheet;
    m_tiles = other.m_tiles;
}

TileSheet& TileSheet::operator=(const TileSheet& other)
{
    m_location = other.m_location;
    m_sheet = other.m_sheet;
    m_tiles = other.m_tiles;
    return *this;
}

TileSheet::~TileSheet()
{

}

