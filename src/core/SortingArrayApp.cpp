#include "SortingArrayApp.hpp"

#include "Utils.hpp"

#include <iostream>
#include <iomanip>
#include <algorithm>

const p6::Color SortingArrayApp::fillColor {0.0f, 0.0f, 1.0f, 1.0f};
const p6::Color SortingArrayApp::sortedFillColor {0.0f, 1.0f, 0.0f, 1.0f};

void SortingArrayApp::ShuffleArray() {
    fillWithRandomfloatValues(array, 0.0f, 1.0f);
    sorted = false;
    max = *std::max_element(array.begin(), array.end());
}

void SortingArrayApp::Update(const PrimitiveWrapperOperatorType& value) {
    if(value == PrimitiveWrapperOperatorType::Swap) {
        SleepFor(delay);
    }else {
        if (value != PrimitiveWrapperOperatorType::ConversionToValueType && value != PrimitiveWrapperOperatorType::ValueMoveAssignment) {
            // thanks to magic_enum for enum to string conversion (https://github.com/Neargye/magic_enum))
            std::cout << CamelCaseConvert(magic_enum::enum_name(value)) << std::endl;
        }
    }
}

SortingArrayApp::SortingArrayApp(const size_t& arraySize, const double& delay, std::function<void(std::vector<PrimitiveWrapper<float>>&)> sort): ctx{{1920, 1080}}, array(arraySize), sortFunction(sort), isSorting(false), delay(delay) {

    // Attach observer(this) to all array value
    for (auto& value: array) value.Attach(&(*this));
    
    ShuffleArray();

    // Display initial values
    std::cout << "Initial values : ";
    if(array.size() < 30) {
        for (auto const& value: array) std::cout << std::setprecision(2) << value << ", ";
        std::cout << std::endl;
    }else {
        std::cout << "Too big for printing initial values (size>30)" << std::endl;
    }

    ctx.update = [this] () {
        ctx.background({1.0f, 1.0f, 1.0f, 1.0f});
        ctx.use_stroke = false;

        const float size = static_cast<float>(array.size());

        const float rectWidth = ctx.aspect_ratio() / size;

        const float fillRatio = 0.95f;
        const float colorshiftAmount = 0.2f;

        ctx.fill = sorted ? sortedFillColor : fillColor;

        for(size_t i = 0; i < size; ++i) {
            const float colorshift = ((1.0f-i%2)*2.0f-1.0f)*colorshiftAmount;
            ctx.fill = p6::Color(ctx.fill.r() + colorshift, ctx.fill.g() + colorshift, ctx.fill.b());
            ctx.rectangle(
                p6::BottomLeftCorner{p6::map<float>(static_cast<float>(i), 0, size, -ctx.aspect_ratio(), ctx.aspect_ratio()), -1.f},
                p6::Radii{rectWidth * fillRatio, array[i] / max}
            );
        }
    };

    ctx.key_pressed = [this](p6::Key key) {
        if(isSorting) {
            std::cout <<"Sorting function already started. Wait until it finish before do anithing else." << std::endl;
            return;
        }

        if (key.logical == "s") {
            isSorting = true;
            computeThread = std::thread([&]() {
                const auto begin = std::chrono::high_resolution_clock::now();
                sortFunction(array);
                const auto end = std::chrono::high_resolution_clock::now();
                sorted = std::is_sorted(array.begin(), array.end());
                isSorting = false;

                std::cout << "Array " << (sorted ? "" : "un") << "successfully sorted." << std::endl;
                if(sorted)
                    std::cout << "Elapsed time : " << std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count() << "ms" << std::endl;
            });
            computeThread.detach();

        }else if (key.logical == "g") {
            ShuffleArray();
        }
    };

    ctx.start();
}