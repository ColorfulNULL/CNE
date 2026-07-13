#pragma once

#include "external.hpp"

namespace cne
{
    // 随机数引擎
    class Random
    {
    public:
        // 构造随机数生成器,默认使用 std::random_device
        explicit Random(unsigned int seed = std::random_device{}());

        // 设置种子
        void SetSeed(unsigned int seed);

        // 生成闭区间 [min, max] 内的均匀随机整数
        int NextInt(int min, int max);

        // 生成半开区间 [min, max) 内的均匀随机浮点数（float）
        float NextFloat(float min = 0.0f, float max = 1.0f);

        // 生成半开区间 [min, max) 内的均匀随机浮点数（double）
        double NextDouble(double min = 0.0, double max = 1.0);

        // 生成布尔值(probability为返回 true 的概率，取值范围 [0,1])
        bool NextBool(double probability = 0.5);

        /**
         * @brief 生成符合正态分布的随机数
         * @param mean 均值
         * @param stddev 标准差
         */
         // 生成符合正态分布的随机数(mean均值 stddev标准差)
        double NextGaussian(double mean = 0.0, double stddev = 1.0);

        // 获取全局单例（线程局部存储,每个线程独立实例,避免锁竞争）
        static Random& Global();

    private:
        std::mt19937 rng_;
    };
}