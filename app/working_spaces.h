#pragma once
#include <iostream>
#include <fstream>

typedef struct _W_SPACE_
{
	char Name[15];
	char RefWhite[3];
	float RGB2XYZ_Matrix[9];
	float Gamma;
	float LabGamutEfficiency;
	float CodingEfficiency;
	float Illuminant[3];
	unsigned char Id;
} W_SPACE, *P_W_SPACE;

class WorkingSpace
{
public :

	void LoadFromFile(std::string filepath)
	{
		std::fstream file("WorkingSpaces/" + filepath, std::ios::in | std::ios::binary);
		if (file.is_open())
		{
			file.seekg(file._Seekbeg);
			file.read((char*) & this->sWSpace, sizeof(W_SPACE));
			file.close();
		}
		else
			throw std::runtime_error("Could not find working space : " + filepath);
	}

	W_SPACE GetWS() const { return this->sWSpace; };
	W_SPACE sWSpace;
};
