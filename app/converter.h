#pragma once

#include "matrixes.hpp"
#include "working_spaces.h"

#include <vector>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;


const int gamutSize = 9;
static const char* gamutKeys[gamutSize]{
   "sRgb",
   "Adobe Rgb",
   "AppleRGB",
   "Best RGB",
   "Beta RGB",
   "ColorMatch RGB",
   "Ekta Space PS5",
   "PAL/SECAM RGB",
   "SMPTE-C RGB"
};

static int gamutKeyIndex = 0;

struct Color {
	int R, G, B;
};

struct XYZColor {
	float X, Y, Z;
};

namespace converter
{
	static Color iColor = { 0, 0, 0 };
	static XYZColor oColor = { .0f, .0f, .0f };
	static float gamutMatrix[9];

	inline std::vector<WorkingSpace> WorkingSpaces;
    inline WorkingSpace* CurrentWorkingSpace = nullptr;

	static float OutputColorScheme[3] = { .0f, .0f, .0f };

	inline void Init()
	{
		WorkingSpace sRgb, adobe, apple, best, beta, colormatch, ektaspace, palsecam, smtpec;
		sRgb.LoadFromFile("srgb.ws"); adobe.LoadFromFile("adobe.ws"); beta.LoadFromFile("beta.ws");
		apple.LoadFromFile("apple.ws"); best.LoadFromFile("best.ws"); colormatch.LoadFromFile("colormatch.ws");
		ektaspace.LoadFromFile("ektaspace.ws"); palsecam.LoadFromFile("palsecam.ws"); smtpec.LoadFromFile("smtpec.ws");

		WorkingSpaces.push_back(sRgb); WorkingSpaces.push_back(adobe); WorkingSpaces.push_back(beta);
		WorkingSpaces.push_back(apple); WorkingSpaces.push_back(best); WorkingSpaces.push_back(colormatch);
		WorkingSpaces.push_back(ektaspace); WorkingSpaces.push_back(palsecam); WorkingSpaces.push_back(smtpec);

		CurrentWorkingSpace = &WorkingSpaces[0];
	}
	
	inline void ComputeEntry()
	{
		OutputColorScheme[0] = static_cast<float>(iColor.R) / 255;
		OutputColorScheme[1] = static_cast<float>(iColor.G) / 255;
		OutputColorScheme[2] = static_cast<float>(iColor.B) / 255;

		for (auto i = 0; i < WorkingSpaces.size(); ++i)
			if (gamutKeyIndex == WorkingSpaces[i].GetWS().Id)
				CurrentWorkingSpace = &WorkingSpaces[i];

		for (auto i = 0; i < 9; ++i)
			gamutMatrix[i] = CurrentWorkingSpace->GetWS().RGB2XYZ_Matrix[i];
	}

	inline void ComputeOutput()
	{
		oColor.X = (gamutMatrix[0] * static_cast<float>(iColor.R) / 255) +
				   (gamutMatrix[1] * static_cast<float>(iColor.G) / 255) +
				   (gamutMatrix[2] * static_cast<float>(iColor.B) / 255);

		oColor.Y = (gamutMatrix[3] * static_cast<float>(iColor.R) / 255) +
				   (gamutMatrix[4] * static_cast<float>(iColor.G) / 255) +
				   (gamutMatrix[5] * static_cast<float>(iColor.B) / 255);

		oColor.Z = (gamutMatrix[6] * static_cast<float>(iColor.R) / 255) +
				   (gamutMatrix[7] * static_cast<float>(iColor.G) / 255) +
				   (gamutMatrix[8] * static_cast<float>(iColor.B) / 255);
	}
}
