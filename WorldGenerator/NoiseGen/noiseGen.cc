#include "noiseGen.h"

#include <cmath>

NoiseGenerator::NoiseGenerator(int seed)
{
    m_noiseParameters.octaves       = 7;
    m_noiseParameters.amplitude     = 70;
    m_noiseParameters.smoothness    = 235;
    m_noiseParameters.heightOffset  = -5;
    m_noiseParameters.roughness     = 0.53;
}

NoiseGenerator::NoiseGenerator()
{
    m_noiseParameters.octaves       = 7;
    m_noiseParameters.amplitude     = 70;
    m_noiseParameters.smoothness    = 235;
    m_noiseParameters.heightOffset  = -5;
    m_noiseParameters.roughness     = 0.53;
}

void NoiseGenerator::setParameters(const NoiseParameters& params) noexcept
{
    m_noiseParameters = params;
}


//wtf?
float NoiseGenerator::getNoise(int  n) const noexcept
{
    n += m_seed;
    n = (n << 13) ^ n;
    auto newN = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;

    return 1.0 - ((float)newN / 1073741824.0);
}

float NoiseGenerator::getNoise(float  x, float  z) const noexcept
{
    return getNoise(x + z * 57);
}

float NoiseGenerator::lerp(float a, float b, float z) const noexcept
{
    float mu2 = (1 - std::cos(z * 3.14)) / 2;
    return (a * (1 - mu2) + b * mu2);
}

float NoiseGenerator::noise(float  x, float  z) const noexcept
{
    auto floorX = (float)((int)x); //This is kinda a cheap way to floor a float integer.
    auto floorZ = (float)((int)z);

    auto    s = 0.0,
            t = 0.0,
            u = 0.0,
            v = 0.0;//Integer declaration

    s = getNoise(floorX,      floorZ);
    t = getNoise(floorX + 1,  floorZ);
    u = getNoise(floorX,      floorZ + 1);//Get the surrounding values to calculate the transition.
    v = getNoise(floorX + 1,  floorZ + 1);

    auto rec1 = lerp(s, t, x - floorX);//Interpolate between the values.
    auto rec2 = lerp(u, v, x - floorX);//Here we use x-floorX, to get 1st dimension. Don't mind the x-floorX thingie, it's part of the cosine formula.
    auto rec3 = lerp(rec1, rec2, z - floorZ);//Here we use y-floorZ, to get the 2nd dimension.
    return rec3;
}

float NoiseGenerator::getHeight(int x, int z, int chunkX, int chunkZ) const noexcept
{
    auto newX = (x + (chunkX * 16));
    auto newZ = (z + (chunkZ * 16));

    if (newX < 0 || newZ < 0) {
        return WATER_LEVEL - 1;
    }

    auto totalValue = 0.0;

    for (auto a = 0; a < m_noiseParameters.octaves - 1; a++) {    //This loops trough the octaves.
        auto frequency = pow(2.0, a);           //This increases the frequency with every loop of the octave.
        auto amplitude = pow(m_noiseParameters.roughness, a);  //This decreases the amplitude with every loop of the octave.
        totalValue += noise(((float)newX) * frequency / m_noiseParameters.smoothness,
                            ((float)newZ) * frequency / m_noiseParameters.smoothness)
                      * amplitude;
    }

    auto val =
        (((totalValue / 2.1) + 1.2) * m_noiseParameters.amplitude) + m_noiseParameters.heightOffset;

    return val > 0 ? val : 1;
}

float NoiseGenerator::getHeight(int x, int z) const noexcept
{
    auto newX = x;
    auto newZ = z;

    if (newX < 0 || newZ < 0) {
        return WATER_LEVEL - 1;
    }

    auto totalValue = 0.0;

    for (auto a = 0; a < m_noiseParameters.octaves - 1; a++) {    //This loops trough the octaves.
        auto frequency = pow(2.0, a);           //This increases the frequency with every loop of the octave.
        auto amplitude = pow(m_noiseParameters.roughness, a);  //This decreases the amplitude with every loop of the octave.
        totalValue += noise(((float)newX) * frequency / m_noiseParameters.smoothness,
                            ((float)newZ) * frequency / m_noiseParameters.smoothness)
                      * amplitude;
    }

    auto val =
        (((totalValue / 2.1) + 1.2) * m_noiseParameters.amplitude) + m_noiseParameters.heightOffset;

    return val > 0 ? val : 1;
}

NoiseGenerator& NoiseGenerator::getInstance(){
  static NoiseGenerator ng;
  std::call_once(initInstanceFlag, &NoiseGenerator::init);
  return ng;
}

void NoiseGenerator::init(){
  std::cout << "Initializing Noise Generator" << std::endl;
  float min = 1.0f;
  float max = 255.0f;
  float random = rand() / max;
  m_seed = (int)(min + random * (max - min));
}

std::once_flag NoiseGenerator::initInstanceFlag;
int NoiseGenerator::m_seed;
