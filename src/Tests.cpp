//
// Created by Lehdari on 21.4.2018.
//

#include "Tests.hpp"
#include "Ecs.hpp"
#include "TestSystems.hpp"

#include <chrono>
#include <random>
#include <algorithm>


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

    printf("Iterating through 10k three component entities with 10%% hit rate\n");
    {
        Ecs ecs;
        TestSystem3 sys;

        for (auto i=0llu; i<100000; i+=10) {
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
            ecs.runSystem(sys);
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double> diff = end-start;
            tv.push_back(diff.count());
        }

        double mean, var;
        getMeanAndVariance(tv, mean, var);

        printf("mean: %0.3f ms, variance: %0.4f ns\n", mean*1000, var*1000000000);
    }
}

void test2()
{
    std::default_random_engine rnd(715517);

    for (uint64_t nAdd = 10000; nAdd <= 50000; nAdd+=10000) {
        Ecs ecs;

        std::vector<uint64_t> eIds;
        eIds.reserve(nAdd);
        for (uint64_t i = 0; i < nAdd; ++i)
            eIds.emplace_back(i);
        for (uint64_t i = 0; i < nAdd; ++i)
            std::swap(eIds[i], eIds[rnd()%nAdd]);

        printf("Adding %llu components in random order\n", nAdd);
        auto start = std::chrono::steady_clock::now();
        for (auto& eId : eIds)
            ecs.addComponent(eId, TestComponent1());
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end-start;
        double dt = diff.count();
        printf("%0.2f ms (%0.4f us per component)\n", dt*1000, (dt*1000000)/nAdd);

        auto nDel = nAdd/2;
        eIds.clear();
        for (uint64_t i = 0; i < nAdd; ++i)
            eIds.emplace_back(i);
        for (uint64_t i = 0; i < nDel; ++i) {
            uint64_t dId = rnd() % eIds.size();
            eIds.erase(eIds.begin()+dId);
        }

        printf("Removing %llu components in random order\n", nDel);
        start = std::chrono::steady_clock::now();
        for (auto& eId : eIds)
            ecs.removeComponent<TestComponent1>(eId);
        end = std::chrono::steady_clock::now();
        diff = end-start;
        dt = diff.count();
        printf("%0.2f ms (%0.4f us per component)\n", dt*1000, (dt*1000000)/nDel);
    }
}