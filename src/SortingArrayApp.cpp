#include "SortingArrayApp.hpp"

#include "Utils.hpp"

#include <iostream>
#include <iomanip>
#include <algorithm>

const glm::vec4 SortingArrayApp::fillColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
const glm::vec4 SortingArrayApp::sortedFillColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

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

SortingArrayApp::SortingArrayApp(const size_t& size, const double& d, std::function<void(std::vector<PrimitiveWrapper<float>>&)> sort): BaseApp(1920, 1080), array(size), sortFunction(sort), lastSwaped(std::make_pair(-1, -1)), delay(d) {

    fillWithRandomfloatValues(array, 0.0f, 1.0f);
    sorted = false;
    max = *std::max_element(array.begin(), array.end());
    // Attach observer(this) to all array value
    for (auto& value: array) value.Attach(&(*this));
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

void SortingArrayApp::draw(piksel::Graphics& g) {
    g.background(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    g.noStroke();

    const float height = Height();
    const float rectWidth = static_cast<float>(Width()) / array.size();

    const float fillRatio = 0.95f;

    if(sorted) {
        g.fill(sortedFillColor);
    }else {
        g.fill(fillColor);
    }

    for(size_t i = 0; i < array.size(); ++i) {
        float value = array[i] / max;
        g.rect(rectWidth * i, height * (1.0f - value), rectWidth * fillRatio, value * height);
    }
}

void SortingArrayApp::mouseMoved([[maybe_unused]]int x, [[maybe_unused]]int y) {
    // std::cout << "mouseMoved (" << x << ", " << y << ")" << std::endl;
}

void SortingArrayApp::mousePressed(int button) {
    if( button == 0 ) {
        std::cout << "left click" << std::endl;
    }
}

void SortingArrayApp::keyPressed(int key) {

    switch (static_cast<char>(key)) {
    case 'S':
        lock.lock();
        computeThread = std::thread([&]() {
            sortFunction(array);
            sorted = std::is_sorted(array.begin(), array.end());
            lock.unlock();
	    });
        break;

    default:
        std::cout << "keycode " << key << "(" << static_cast<char>(key) << ") not assigned yet " << std::endl;
        break;
    }
}