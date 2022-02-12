#include "SortingArrayApp.hpp"

#include "Utils.hpp"

#include <iostream>
#include <iomanip>
#include <algorithm>

const p6::Color SortingArrayApp::fillColor {0.0f, 0.0f, 1.0f, 1.0f};
const p6::Color SortingArrayApp::sortedFillColor {0.0f, 1.0f, 0.0f, 1.0f};

void SortingArrayApp::Update(const PrimitiveWrapperOperatorType& value) {
    if(value == PrimitiveWrapperOperatorType::Swap || value == PrimitiveWrapperOperatorType::MoveAssignment) {
        SleepFor(delay);
    }else {
        if (value != PrimitiveWrapperOperatorType::ConversionToValueType) {
            // thanks to magic_enum for enum to string conversion (https://github.com/Neargye/magic_enum))
            std::cout << CamelCaseConvert(magic_enum::enum_name(value)) << std::endl;
        }
    }
}

SortingArrayApp::SortingArrayApp(const size_t& size, const double& d, std::function<void(std::vector<PrimitiveWrapper<float>>&)> sort): ctx{{1920, 1080}}, array(size), sortFunction(sort), lastSwaped(std::make_pair(-1, -1)), delay(d) {

    fillWithRandomfloatValues(array, 0.0f, 1.0f);
    sorted = false;
    max = *std::max_element(array.begin(), array.end());
    // Attach observer(this) to all array value
    for (auto& value: array) value.Attach(&(*this));

    setup();

    ctx.update = [this] () {
        ctx.background({1.0f, 1.0f, 1.0f, 1.0f});
        ctx.use_stroke = false;

        const float rectWidth = ctx.aspect_ratio() / array.size();

        const float fillRatio = 0.95f;

        if(sorted) {
            ctx.fill = sortedFillColor;
        }else {
            ctx.fill = fillColor;
        }

        for(size_t i = 0; i < array.size(); ++i) {
            float value = array[i] / max;
            ctx.rectangle(p6::BottomLeftCorner{p6::map<float>(i, 0, array.size(),
                                                                 -ctx.aspect_ratio(),
                                                                 +ctx.aspect_ratio()),
                                               -1.f},
                          p6::Radii{rectWidth * fillRatio, value});
        }
    };

    ctx.key_pressed = [this](p6::Key key) {
        if (key.logical == "s") {
            lock.lock();
            computeThread = std::thread([&]() {
                sortFunction(array);
                sorted = std::is_sorted(array.begin(), array.end());
                lock.unlock();
            });
        }
    };

    ctx.start();
}

void SortingArrayApp::setup() {
    std::cout << "Initiale values : ";
    if(array.size() < 30) {
        for (auto const& value: array) std::cout << std::setprecision(2) << value << ", ";
        std::cout << std::endl;
    }else {
        std::cout << "Too big for printing initial values (size>30)" << std::endl;
    }
}