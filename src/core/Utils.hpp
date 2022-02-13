#pragma once

#include <random>
#include <algorithm>
#include <string_view>
#include <functional>

// From https://devblogs.microsoft.com/oldnewthing/20190619-00/?p=102599
template <typename C, typename T = std::decay_t<decltype(*begin(std::declval<C>()))>, typename = std::enable_if_t<std::is_convertible_v<T, float>>>
C& fillWithRandomfloatValues(C& container, const float& min, const float& max) {
    static std::random_device rd;
    static std::mt19937 mte(rd());
    const std::uniform_real_distribution<float> dist(min, max);
    // lambda could also be used instead of std::bind : [&] () { return dist(mte); }
    std::generate(container.begin(), container.end(), std::bind(dist, std::ref(mte)));

    return container;
}

std::string CamelCaseConvert(const std::string_view& camelCase);

void SleepFor(double dt);
