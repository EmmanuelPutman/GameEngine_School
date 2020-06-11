#include "EP_Engine_PCH.h"
#include "LevelParser_Pyxel.h"

#include "Logger.h"
#include "ResourceManager.h"

#include <fstream>

LevelParser_Pyxel::LevelParser_Pyxel(const std::string& fileName)
	:m_BlockHeight{ 0 }
	, m_BlockWidth{ 0 }
	, m_NrHorizontalBlocks{ 0 }
	, m_NrVerticalBlocks{ 0 }
{
	ParseFile(fileName);
}

void LevelParser_Pyxel::ParseFile(const std::string& fileName)
{
	std::ifstream input{ ep::ResourceManager::GetInstance().GetFullPath(fileName) };

	std::string text;
	std::string line;
	glm::vec3 blockPos{ 0.f, 0.f, 0.f };

	if (!input)
		ep::Logger::GetInstance().Error("{__LevelParser_PlainText__} File to parse could not be found.");

	while (input)
	{
		std::getline(input, line);

		std::string word{};

		if (line == "")
			continue;

		if (line.find("tileswide") != std::string::npos)
		{
			word = "tileswide";
			size_t pos = line.find(" ");
			m_NrHorizontalBlocks = std::stoi(line.substr(pos + 1, word.length() - 1));
		}
		else if (line.find("tileshigh") != std::string::npos)
		{
			word = "tileshigh";
			size_t pos = line.find(" ");
			m_NrVerticalBlocks = std::stoi(line.substr(pos + 1, word.length() - 1));
		}
		else if (line.find("tilewidth") != std::string::npos)
		{
			word = "tilewidth";
			size_t pos = line.find(" ");
			m_BlockWidth = std::stoi(line.substr(pos + 1, word.length() - 1));

			//This is due to the coordinate system (0, 0 : top left corner)
			blockPos.x = m_BlockWidth / 2.f;
		}
		else if (line.find("tileheight") != std::string::npos)
		{
			word = "tileheight";
			size_t pos = line.find(" ");
			m_BlockHeight = std::stoi(line.substr(pos + 1, word.length() - 1));

			//This is due to the coordinate system (0, 0 : top left corner)
			blockPos.y = m_BlockHeight / 2.f;
		}
		else if (line.find("") == std::string::npos || line.find("layer") == std::string::npos)
		{
			size_t pos = line.find(",");
			int id = std::stoi(line.substr(0, pos));
			m_BlockPositions.push_back(std::pair<glm::vec3, int>(blockPos, id));

			while (line.find(",", pos + 1) != std::string::npos)
			{
				blockPos.x += m_BlockWidth;

				size_t nexPos = line.find(",", pos + 1);
				id = std::stoi(line.substr(pos + 1, nexPos));
				m_BlockPositions.push_back(std::pair<glm::vec3, int>(blockPos, id));

				pos = nexPos;
			}

			//This is due to the coordinate system (0, 0 : top left corner)
			blockPos.x = m_BlockWidth/2.f;
			blockPos.y += m_BlockHeight;
		}
	}
}
