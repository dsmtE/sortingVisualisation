#pragma once

#include "PrimitiveWrapper.hpp"
#include "ObservablePattern.hpp"
#include "Utils.hpp"

#include <p6/p6.h>
#include "magic_enum.hpp"

#include <thread>
#include <mutex>
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

    std::pair<float, float> lastSwaped;

    std::thread computeThread;
    std::mutex lock;

    double delay;
public:
    SortingArrayApp(const size_t& size, const double& d, std::function<void(std::vector<PrimitiveWrapper<float>>& )> sortFunction);

    void setup();

    void Update(const PrimitiveWrapperOperatorType& value) override;
};