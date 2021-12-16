//
// Created by mknoe on 16.12.2021.
//

#ifndef UNTITLED_BENCHMARKER_H
#define UNTITLED_BENCHMARKER_H

#include <iostream>

#include <iostream>
#include <chrono>
#include <ctime>


void runLoop(const std::function<void()>&  init, const std::function<void()>&  func, int loops)
{
    std::vector<double> results;
    for (int i = 0; i < loops; i++)
    {
        init();
        auto start = std::chrono::system_clock::now();
        func();
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        //			System.out.println(diff / 1_000_000 + " msecs");
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);

        std::cout << "finished computation at " << std::ctime(&end_time)
                  << "elapsed time: " << elapsed_seconds.count() << "s\n";
        results.push_back(elapsed_seconds.count());
    }
    double sum = 0;
    for (auto res : results) {
            sum += res;
    }
    double avg = sum / results.size();

    std::cout << "avg= " << avg / 1000000 << " msecs" << std::endl;
}



void bench( const std::function<void()>&  init,  const std::function<void()>& func, const std::string& title)
{
    std::cout << "Benchmarking " << title << std::endl;
    std::cout << "WARMUP"<< std::endl;
    runLoop(init, func, 10);
    std::cout << "Measurement"<< std::endl;
    runLoop(init, func, 20);
    std::cout << std::endl;
}



#endif //UNTITLED_BENCHMARKER_H
