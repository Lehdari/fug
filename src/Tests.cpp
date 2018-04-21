//
// Created by Lehdari on 21.4.2018.
//

#include "Tests.hpp"
#include "Ecs.hpp"
#include "TestSystems.hpp"

#include <chrono>


namespace
{
    void getMeanAndVariance(const std::vector<double>& v, double& mean, double& var)
    {
        mean = 0.0f;
        var = 0.0f;
        for (auto& e : v)
            mean += e;
        mean /= v.size();
        for (auto& e : v)
            var += (e-mean)*(e-mean);
        var /= v.size();
    }
}


void test1()
{
    printf("Test1\n");
    printf("Iterating through 10k single component entities\n");
    {
        Ecs ecs;
        TestSystem1 sys;

        for (auto i=0llu; i<10000; ++i)
            ecs.addComponent(i, TestComponent1());

        std::vector<double> tv;
        tv.reserve(1000);
        for (auto i=0; i<1000; ++i) {
            auto start = std::chrono::steady_clock::now();
            ecs.runSystem(sys);
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double> diff = end-start;
            tv.push_back(diff.count());
        }

        double mean, var;
        getMeanAndVariance(tv, mean, var);

        printf("mean: %0.3f ms, variance: %0.4f ns\n", mean*1000, var*1000000000);
    }

    printf("Iterating through 10k two-component entities\n");
    {
        Ecs ecs;
        TestSystem2 sys;

        for (auto i=0llu; i<10000; ++i) {
            ecs.addComponent(i, TestComponent1());
            ecs.addComponent(i, TestComponent2());
        }

        std::vector<double> tv;
        tv.reserve(1000);
        for (auto i=0; i<1000; ++i) {
            auto start = std::chrono::steady_clock::now();
            ecs.runSystem(sys);
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double> diff = end-start;
            tv.push_back(diff.count());
        }

        double mean, var;
        getMeanAndVariance(tv, mean, var);

        printf("mean: %0.3f ms, variance: %0.4f ns\n", mean*1000, var*1000000000);
    }
#if 0
    printf("Iterating through 10k three-component entities\n");
    {
        Ecs ecs;
        TestSystem3 sys;

        for (auto i=0llu; i<10000; ++i) {
            ecs.addComponent(i, TestComponent1());
            ecs.addComponent(i, TestComponent2());
            ecs.addComponent(i, TestComponent3());
        }

        std::vector<double> tv;
        tv.reserve(1000);
        for (auto i=0; i<1000; ++i) {
            auto start = std::chrono::steady_clock::now();
            ecs.runSystem(sys);
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double> diff = end-start;
            tv.push_back(diff.count());
        }

        double mean, var;
        getMeanAndVariance(tv, mean, var);

        printf("mean: %0.3f ms, variance: %0.4f ns\n", mean*1000, var*1000000000);
    }
#endif
    printf("Iterating through 10k single component entities\n");
    {
        Ecs ecs;
        TestSystem3 sys;

        for (auto i=0llu; i<10000; i+=10) {
            ecs.addComponent(i, TestComponent1());
            ecs.addComponent(i, TestComponent2());
            ecs.addComponent(i, TestComponent3());
            ecs.addComponent(i+1, TestComponent1());
            ecs.addComponent(i+2, TestComponent1());
            ecs.addComponent(i+3, TestComponent1());
            ecs.addComponent(i+4, TestComponent1());
            ecs.addComponent(i+5, TestComponent1());
            ecs.addComponent(i+6, TestComponent1());
            ecs.addComponent(i+7, TestComponent1());
            ecs.addComponent(i+8, TestComponent1());
            ecs.addComponent(i+9, TestComponent1());
        }


        std::vector<double> tv;
        tv.reserve(1000);
        for (auto i=0; i<1000; ++i) {
            auto start = std::chrono::steady_clock::now();
            //printf("A\n");
            ecs.runSystem(sys);
            //printf("B\n");
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double> diff = end-start;
            tv.push_back(diff.count());
        }

        double mean, var;
        getMeanAndVariance(tv, mean, var);

        printf("mean: %0.3f ms, variance: %0.4f ns\n", mean*1000, var*1000000000);
    }
}
