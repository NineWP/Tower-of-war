
#include "Player.h"

int createBackGround(VertexArray& rVA, IntRect arena)
{
	const int Tile_Size = 50;
	const int Tile_Type = 3;
	const int Verts_In_Quad = 4;

	int worldWidth = arena.width / Tile_Size;
	int worldHeight = arena.height / Tile_Size;

	rVA.setPrimitiveType(Quads);	

	// Set size of the vertex array
	rVA.resize(worldWidth * worldHeight * Verts_In_Quad);

	int currentVertex = 0;

	for (int w = 0; w < worldWidth; w++)
	{
		for (int h = 0; h < worldHeight; h++)
		{
			// Position each vertex in the current quad
			rVA[currentVertex].position = Vector2f(w * Tile_Size, h * Tile_Size);
			rVA[currentVertex + 1].position = Vector2f((w * Tile_Size) + Tile_Size, h * Tile_Size);
			rVA[currentVertex + 2].position = Vector2f((w * Tile_Size) + Tile_Size, (h * Tile_Size) + Tile_Size);
			rVA[currentVertex + 3].position = Vector2f(w * Tile_Size, (h * Tile_Size) + Tile_Size);

			if (h == 0 || h == worldHeight - 1 || w == 0 || w == worldWidth - 1 )
			{
				// Use the wall texture
				rVA[currentVertex].texCoords = Vector2f(0, Tile_Type * Tile_Size);
				rVA[currentVertex + 1].texCoords = Vector2f(Tile_Size, Tile_Type * Tile_Size);
				rVA[currentVertex + 2].texCoords = Vector2f(Tile_Size, Tile_Size + Tile_Type * Tile_Size);
				rVA[currentVertex + 3].texCoords = Vector2f(0, Tile_Size + Tile_Type * Tile_Size);
			}
			else
			{
				// Use random flore texture
				srand((int)time(0) + h * w - h);
				int fOrBF = rand() % Tile_Type;
				int verticalOffSet = fOrBF * Tile_Size;

				rVA[currentVertex].texCoords = Vector2f(0, verticalOffSet);
				rVA[currentVertex + 1].texCoords = Vector2f(Tile_Size, verticalOffSet);
				rVA[currentVertex + 2].texCoords = Vector2f(Tile_Size, Tile_Size + verticalOffSet);
				rVA[currentVertex + 3].texCoords = Vector2f(0, Tile_Size + verticalOffSet);
			}

			// Position ready for the next for vertices
			currentVertex = currentVertex + Verts_In_Quad;
		}
	}

	return Tile_Size;
}
