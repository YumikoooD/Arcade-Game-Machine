/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-guillaume.deplaine
** File description:
** time
*/

#ifndef TIME_HPP_
    #define TIME_HPP_

#include <unistd.h>
#include <chrono>
#include <system_error>

template<typename T = std::chrono::steady_clock::time_point>
class Time {
    private:
        T __start;
    public:
        Time() {
            if constexpr (std::is_same_v<T, std::chrono::steady_clock::time_point>) {
                __start = std::chrono::steady_clock::now();
            } else {
                __start.reset();
            }
        };
        ~Time() = default;
        void framerate(long frames_per_sec) {
            if (frames_per_sec <= 0)
                std::__throw_system_error(95);
            wait(1.0 / frames_per_sec);
        };
        void wait(float time) {
            if constexpr (std::is_same_v<T, std::chrono::steady_clock::time_point>) {
                while (std::chrono::steady_clock::now() - __start
                    < std::chrono::duration<float>(time)) {
                    usleep(10);
                }
                __start = std::chrono::steady_clock::now();
            } else {
                while(__start.get_time() < time) {
                    usleep(10);
                };
                __start.reset();
            }
        };
};

#endif /* !TIME_HPP_ */
