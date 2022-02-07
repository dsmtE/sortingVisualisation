#pragma once

#include "PrimitiveWrapper.hpp"
#include "ObservablePattern.hpp"
#include "Utils.hpp"

#include "piksel/baseapp.hpp"
#include "magic_enum.hpp"

#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <utility>
#include <functional>

class SortingArrayApp : public piksel::BaseApp, public IObserver<PrimitiveWrapperOperatorType> {

private:

    const static glm::vec4 fillColor;
    const static glm::vec4 sortedFillColor;

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

    void Update(const PrimitiveWrapperOperatorType& value) override;

    inline int Width() const { return width; }
    inline int Height() const { return height; }

    void draw(piksel::Graphics& g);
    void mouseMoved(int x, int y);
    void mousePressed(int button);
    void keyPressed(int key);
    void setup();
};