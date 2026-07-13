#include "Random.hpp"

cne::Random::Random(unsigned int seed) : rng_(seed) {}

void cne::Random::SetSeed(unsigned int seed)
{
    rng_.seed(seed);
}

int cne::Random::NextInt(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng_);
}

float cne::Random::NextFloat(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(rng_);
}

double cne::Random::NextDouble(double min, double max)
{
    std::uniform_real_distribution<double> dist(min, max);
    return dist(rng_);
}

bool cne::Random::NextBool(double probability)
{
    std::bernoulli_distribution dist(probability);
    return dist(rng_);
}

double cne::Random::NextGaussian(double mean, double stddev)
{
    std::normal_distribution<double> dist(mean, stddev);
    return dist(rng_);
}

cne::Random& cne::Random::Global()
{
    // 使用 thread_local 实现每线程独立实例（适合多线程游戏）
    static thread_local Random instance;
    return instance;
}