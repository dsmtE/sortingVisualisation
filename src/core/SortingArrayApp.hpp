#pragma once

#include "PrimitiveWrapper.hpp"
#include "ObservablePattern.hpp"
#include "Utils.hpp"

#include <p6/p6.h>
#include "magic_enum.hpp"

#include <thread>
#include <vector>
#include <chrono>
#include <utility>
#include <functional>

class SortingArrayApp : public IObserver<PrimitiveWrapperOperatorType> {
private:

    p6::Context ctx;

    const static p6::Color fillColor;
    const static p6::Color sortedFillColor;

    std::vector<PrimitiveWrapper<float>> array;
    bool sorted;
    float max;

    std::function<void(std::vector<PrimitiveWrapper<float>>&)> sortFunction;

    std::thread computeThread;
    bool isSorting;

    double delay;

    void ShuffleArray();

public:
    SortingArrayApp(const size_t& arraySize, const double& delay, std::function<void(std::vector<PrimitiveWrapper<float>>& )> sortFunction);

    void Update(const PrimitiveWrapperOperatorType& value) override;

};