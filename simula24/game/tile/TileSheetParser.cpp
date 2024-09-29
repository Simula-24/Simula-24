#include "TileSheetParser.h"

#include <game/tile/TileSheet.h>
#include <stdio.h>
using simula24::TileSheetParser;
using simula24::TileSheet;
using simula24::Status;


TileSheetParser::TileSheetParser(SDL_Renderer* r)
    : m_renderer(r)
{
}

TileSheetParser::~TileSheetParser()
{
}

Status TileSheetParser::load(const stl::string& configFileName)
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

stl::shared_ptr<TileSheet> TileSheetParser::getNextSheet()
{
    return stl::shared_ptr<TileSheet>();
}

bool simula24::TileSheetParser::extractDimensions(const stl::string& source, int& w_out, int& h_out)
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

bool TileSheetParser::parseConfig2(const stl::string& cfg)
{
    TileSheetConfig tsc{};
    enum ParseStatus
    {
        NONE,
        PARSING_NAME,
        PARSING_DIMENSIONS_TILE_SIZE,
        PARSING_DIMENSIONS_IMAGE_SIZE
    };

    ParseStatus ps = NONE;
    
    const char* cur = cfg.c_str();
    stl::string dimensionsStr;
    int nameStart = 0;

    while(cur != &cfg.back())
    {
        if (*cur == '[')
        {
            ps = PARSING_NAME;
            cur++;
            nameStart = (cur - cfg.c_str());
            continue;
        }

        if (*cur == ']')
        {
            ps = NONE;
            tsc.filename = cfg.substr(nameStart, (cur - cfg.c_str()));
            tsc.filename += '\0';
            cur++;
            continue;
        }

        if (ps == PARSING_NAME)
        {
            cur++; 
            continue;
        }
        else if (ps == PARSING_DIMENSIONS_TILE_SIZE || ps == PARSING_DIMENSIONS_IMAGE_SIZE)
        {
            if (*cur == '\n' || *cur == '\r')
            {
                dimensionsStr += '\0';
                if(ps == PARSING_DIMENSIONS_IMAGE_SIZE)
                    extractDimensions(dimensionsStr, tsc.imageWidth, tsc.imageHeight);
                else if (ps == PARSING_DIMENSIONS_TILE_SIZE)
                    extractDimensions(dimensionsStr, tsc.tileWidth, tsc.tileHeight);
                ps = NONE;
                dimensionsStr.setPos(0);
            }
            else
                dimensionsStr += *cur;
        }
        else if (strncmp(cur, "tile_size=", 10) == 0)
        {
            ps = PARSING_DIMENSIONS_TILE_SIZE;
            cur += 10;
            continue;
        }
        
        else if (strncmp(cur, "size=", 5) == 0)
        {
            ps = PARSING_DIMENSIONS_IMAGE_SIZE;
            cur += 5;
            continue;
        }
        cur++;
    }

    printf("%s\n", tsc.filename.c_str());

    return true;
}

bool TileSheetParser::parseConfig(const stl::string& cfg)
{
    TileSheetConfig tsc{};

    int nameStart = cfg.find('[');
    int nameEnd = cfg.find(']');


}
