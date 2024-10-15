#include "TileSheetDatabase.h"
#include "TileSize.h"
namespace simula24
{

TileSheetDatabase::TileSheetDatabase()
    : worldTiles{}, creatureTiles{}
{
    worldTiles.resize(TileSize::NUM);
    creatureTiles.resize(TileSize::NUM);
}

TileSheetDatabase::~TileSheetDatabase()
{

}


}