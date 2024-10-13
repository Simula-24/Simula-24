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

