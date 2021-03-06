#include "Generation/MapGeneration.h"
#include "World/Block.h"

float MapGeneration::GetBasicElevation(glm::ivec2 pos)
{
    FastNoise& basicNoise = _noises[Basic];
    float terraceValue = _terraceValue;

    float e = 1.f * (basicNoise.GetNoise(1.f * pos.x, 1.f * pos.y));
    float e1 = 0.50f * (basicNoise.GetNoise(2.f * pos.x, 2.f * pos.y));

    e += e1;
    e = (e * 0.5f + 0.5f) * 10.f;

    float terrace = round(e * terraceValue) / terraceValue;  
    int elevation = (int)floorf(terrace);
    return elevation;
}

void MapGeneration::GetBasicData(StoredMapData& column, glm::ivec2 pos)
{
    column.approximateElevation = GetBasicElevation(pos);
    column.firstBlockLayer = Block::Stone;
    column.lastBlockLayer = Block::Stone;
}
