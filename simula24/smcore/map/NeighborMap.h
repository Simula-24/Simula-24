#ifndef SMCORE_MAP_NEIGHBOR_MAP_H_
#define SMCORE_MAP_NEIGHBOR_MAP_H_

namespace simula24
{

const static int NeighborMap[8][2] =
{
    // up-down-left-right
    {-1,  0},
    { 1,  0},
    { 0, -1},
    { 0,  1},
    // diag
    {-1, -1},
    {-1,  1},
    { 1, -1},
    { 1,  1}
};

} // simula24
#endif // SMCORE_MAP_NEIGHBOR_MAP_H_