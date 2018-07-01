#include "perlinNoise.h"

PerlinNoise::PerlinNoise(){}

std::vector<int> PerlinNoise::getCoordinates(const int width, const int length, const int seed, const int octaves, const float bias){
		std::vector<int> values;
		std::srand(seed);
		int size = width * length;
		int* arr = new int[size];
		for(int i = 0; i < width * length; i++){
			arr[i] = 1 + std::rand() % 100;
		}

		// Used 1D Perlin Noise
		for (int x = 0; x < width; x++)
			for (int y = 0; y < length; y++)
			{
				float fNoise = 0.0f;
				float fScaleAcc = 0.0f;
				float fScale = 1.0f;

				for (int o = 0; o < octaves; o++)
				{
					
					int nPitch = width >> o;
					std::cout << nPitch << std::endl;
					int nSampleX1 = (x / nPitch) * nPitch;
					int nSampleY1 = (y / nPitch) * nPitch;

					int nSampleX2 = (nSampleX1 + nPitch) % width;
					int nSampleY2 = (nSampleY1 + nPitch) % width;

					float fBlendX = (float)(x - nSampleX1) / (float)nPitch;
					float fBlendY = (float)(y - nSampleY1) / (float)nPitch;

					float fSampleT = (1.0f - fBlendX) * arr[nSampleY1 * width + nSampleX1] + fBlendX * arr[nSampleY1 * width + nSampleX2];
					float fSampleB = (1.0f - fBlendX) * arr[nSampleY2 * width + nSampleX1] + fBlendX * arr[nSampleY2 * width + nSampleX2];

					fScaleAcc += fScale;
					fNoise += (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;
					fScale = fScale / bias;
				}

				// Scale to seed range

				values.emplace_back(fNoise / fScaleAcc);

			}
			delete arr;
			return values;
	}
