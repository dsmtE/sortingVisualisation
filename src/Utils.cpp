
#include "Utils.hpp"

#include <cctype>

#include <chrono>
#include <thread>

std::string CamelCaseConvert(const std::string_view& camelCase) {
    std::string str(1, std::tolower(camelCase[0]));

    for (auto it = camelCase.begin() + 1; it != camelCase.end(); ++it) {
        if (std::isupper(*it) && std::islower(*(it-1))) {
            str += " ";
        }
        str += *it;
    }

    // Then convert it to lower case.
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);

    return str;
}

//  not optimized(CPU ) but simple and relatively accurate sleep
void SleepFor(double dt) {
    static constexpr std::chrono::duration<double> MinSleepDuration(0);
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    while (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count() < dt) {
        std::this_thread::sleep_for(MinSleepDuration);
    }
}