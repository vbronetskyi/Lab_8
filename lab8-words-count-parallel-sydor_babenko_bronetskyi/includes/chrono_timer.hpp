//
// Created by Natalya on 26.02.2024.
//

#ifndef TEMPLATE_CHRONO_TIMER_HPP
#define TEMPLATE_CHRONO_TIMER_HPP
#include <iostream>
#include <chrono>
#include <atomic>


inline std::chrono::high_resolution_clock::time_point get_current_time_fenced() {
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::high_resolution_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}

template<class D>
inline long long to_ms(const D& d) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(d).count();
}

#endif //TEMPLATE_CHRONO_TIMER_HPP
