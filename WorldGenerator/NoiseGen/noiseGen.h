#ifndef WORLDGENERATOR_NOISEGEN_NOISEGENERATOR_H_INCLUDED
#define WORLDGENERATOR_NOISEGEN_NOISEGENERATOR_H_INCLUDED

#include <iostream>
#include <mutex>

struct NoiseParameters
{
    int octaves;
    int amplitude;
    int smoothness;
    int heightOffset;

    float roughness;
};

class NoiseGenerator
{
    const int WATER_LEVEL = 0;

    static void init();

    bool isInit = false;
    static int m_seed;
	static std::once_flag initInstanceFlag;

    public:
        static NoiseGenerator& getInstance();
        NoiseGenerator(int seed);
        NoiseGenerator();

        float getHeight(int x, int z, int chunkX, int chunkZ) const noexcept;
        float getHeight(int x, int z) const noexcept;

        void setParameters(const NoiseParameters& params) noexcept;
        int randomInt();
    private:
        float getNoise(int  n) const noexcept;
        float getNoise(float  x, float  z) const noexcept;

        float lerp(float a, float b, float z) const noexcept;

        float noise(float  x, float  z) const noexcept;

        NoiseParameters m_noiseParameters;

};

#endif // NOISEGENERATOR_H_INCLUDED
