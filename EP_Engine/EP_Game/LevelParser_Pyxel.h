#pragma once
#include <map>

/* This is a parser that parses the .txt generated level from the application PyxelEdit */
class LevelParser_Pyxel
{
public:
	LevelParser_Pyxel(const std::string& fileName);
	~LevelParser_Pyxel() = default;
	LevelParser_Pyxel(const LevelParser_Pyxel&) = delete;
	LevelParser_Pyxel(LevelParser_Pyxel&&) = delete;
	LevelParser_Pyxel& operator= (const LevelParser_Pyxel&) = delete;
	LevelParser_Pyxel& operator= (const LevelParser_Pyxel&&) = delete;

	int GetBlockWidth() { return m_BlockWidth; };
	int GetBlockHeight() { return m_BlockHeight; };
	int GetNrOfHorizontalBlocks() { return m_NrHorizontalBlocks; };
	int GetNrOfVerticalBlocks() { return m_NrVerticalBlocks; };

	const std::vector<std::pair<glm::vec3, int>>& GetBlocks() { return m_BlockPositions; };

private:
	std::vector<std::pair<glm::vec3, int>> m_BlockPositions;

	int m_BlockWidth;
	int m_BlockHeight;
	int m_NrHorizontalBlocks;
	int m_NrVerticalBlocks;

	void ParseFile(const std::string& fileName);
};

