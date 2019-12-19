#pragma once

typedef unsigned long long uint64;
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef long long int64;
typedef int int32;
typedef short int16;
typedef char int8;

typedef uint32 uint;

class Entity;
class Game;
class Locator;
class MapGeneration;
class Input;
class Player;
class Camera;
class CubeMap;
class Geometry;
class GLRenderer;
class RenderModel;
class Shader;
class Texture;
class VertexBuffers;
class UIController;
class ILogger;
class NullLogger;
class TerminalLogger;
class Utilities;
class Chunk;
class ResourceLoader;
class Shard;
class World;

enum class BlockType {
	Air = 0,
	Bedrock,
	Cobblestone,
	Dirt,
	Planks,
	Sand,
	Stone,
	OreCoal,
	OreDiamond,
	OreGold,
	OreIron,
	OreRedstone,
	CraftingTable,
	Grass,
	Leaves,
	Log,
	Dandelion,
	First = Air,
	Last = Dandelion,
	Size = Last + 1
};