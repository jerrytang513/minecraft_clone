#ifndef NOISEGENERATOR_H_INCLUDED
#define NOISEGENERATOR_H_INCLUDED

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
    public:
        NoiseGenerator(int seed);

        float getHeight(int x, int z, int chunkX, int chunkZ) const noexcept;
        float getHeight(int x, int z) const noexcept;

        void setParameters(const NoiseParameters& params) noexcept;

    private:
        float getNoise(int  n) const noexcept;
        float getNoise(float  x, float  z) const noexcept;

        float lerp(float a, float b, float z) const noexcept;

        float noise(float  x, float  z) const noexcept;

        NoiseParameters m_noiseParameters;

        int m_seed;
};

#endif // NOISEGENERATOR_H_INCLUDED
