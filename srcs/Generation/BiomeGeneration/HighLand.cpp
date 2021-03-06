#include "Generation/MapGeneration.h"
#include "World/Block.h"

float  MapGeneration::GetHighLandElevation(glm::ivec2 pos)
{
    FastNoise& highlandNoise = _noises[HighLand];
    float exp = 1.2f;;
    float terraceValue = _terraceValue;

    float e = 1.f * (highlandNoise.GetNoise(pos.x, pos.y));
    float e1 = 0.50f * (highlandNoise.GetNoise(2.f * pos.x, 2.f * pos.y));
    float e2 = 0.25f * (highlandNoise.GetNoise(4.f * pos.x, 4.f * pos.y));
    e += e1 + e2;
    e = (e * 0.5f + 0.5f) * 10; // range 0..~10.3

    float mountainPeaks = pow(e, exp);
    float terrace = round(mountainPeaks * terraceValue) / terraceValue;
    float elevation = terrace;
    return elevation;
}

void MapGeneration::GetHighLandData(StoredMapData& column, glm::ivec2 pos)
{
    column.approximateElevation = GetHighLandElevation(pos);
    column.approximateElevation = SmoothBiomeSeams(column.approximateElevation, pos, HighLand);
    column.approximateElevation = (int)floorf(column.approximateElevation * 10.f);
    column.firstBlockLayer = Block::Stone;
    column.lastBlockLayer = Block::Stone;
    if (column.approximateElevation > 75 && column.approximateElevation < 86)
        column.lastBlockLayer = Block::SnowGrass;
    else if (column.approximateElevation >= 86)
        column.lastBlockLayer = Block::Ice;
}
