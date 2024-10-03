#include "TileConfig.h"

#include <graphics/tile/TileSheet.h>
#include <stdio.h>
using simula24::TileConfig;
using simula24::TileSheet;
using simula24::Status;


TileConfig::TileConfig()
{
}

TileConfig::~TileConfig()
{
}

Status TileConfig::load(const stl::string& configFileName)
{
    File config;
    Status s = config.open(configFileName, File::READ);
    if (s != Status::OK)
        return s;

    stl::string contents;
    contents.resize(config.getSize() + 1);

    config.read(contents.data(), config.getSize());
    
    contents.setPos(config.getSize());
    
    contents += '\0';
    printf("%s\n",contents.c_str());

    if(!parseConfig(contents))
        return ERR_INVALID_PARAMETER;
    return OK;
}

bool simula24::TileConfig::extractDimensions(const stl::string& source, int& w_out, int& h_out)
{
    int pivot = 0;
    
    char width[10];

    for (int i = 0; i < source.length(); i++) 
    {
        if (source[i] == 'x' || source[i] == 'X')
        {
            pivot = i;
            break;
        }
    }

    strncpy(width, source.c_str(), pivot);
    width[pivot] = '\0';
    
    w_out = atoi(width);
    h_out = atoi(source.c_str() + pivot + 1);

    printf("%d x %d\n", w_out, h_out);
    return true;
}

bool TileConfig::parseConfig(const stl::string& cfg)
{
    TileSheetConfig tsc{};

    int nameStart = cfg.find('[');
    int nameEnd = cfg.find(']');

    if (nameStart == stl::string::npos || nameEnd == stl::string::npos)
        return false;

    tsc.filename = cfg.substr(nameStart + 1, nameEnd);


    // make sure we dont start ON a newline
    int pos = cfg.find(nameEnd,'\n') + 1;

    while (pos < cfg.length())
    {
        ///
        /// Essentially we are taking something like
        ///     key=value
        /// Finding the position of '=' and '\n'
        /// And extracting both using substrings
        ///     key=value\n
        ///pos~~^  ^     ^~~nextnl
        ///        \ nexteq
        /// 
        int nexteq = cfg.find(pos, '=');
        int nextnl = cfg.find(pos, '\n');

        if (nexteq == stl::string::npos || nextnl == stl::string::npos)
            break;

        // strip whitespace
        while (cfg[pos] == ' ' && pos < cfg.length())
            ++pos;

        stl::string keyName = cfg.substr(pos, nexteq).c_str();
        stl::string value = cfg.substr(nexteq + 1, nextnl);
        
        if (keyName == "tile_size")
        {
            if (!extractDimensions(value, tsc.tileWidth, tsc.tileHeight))
                return false;
        }

        else if (keyName == "size")
        {
            if (!extractDimensions(value, tsc.imageWidth, tsc.imageHeight))
                return false;
        }
        // skip over newline
        pos = nextnl + 1;
    }

    m_sheetConfigs.push_back(tsc);
    return true;
}
