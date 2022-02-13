#pragma once

#include "ObservablePattern.hpp"

#include <type_traits>
#include <iostream>
#include <utility>

enum class PrimitiveWrapperOperatorType: unsigned short
{
    DefaultConstructor = 1,
    ValueCopyConstructor,
    ValueMoveConstructor,
    CopyConstructor,
    MoveConstructor,
    ConversionToValueType,
    CopyAssignment,
    MoveAssignment,
    ValueCopyAssignment,
    ValueMoveAssignment,
    PrefixIncrement,
    PostfixIncrement,
    PrefixDecrement,
    PostfixDecrement,
    AdditionAssignment,
    SubtractionAssignment,
    MultiplicationAssignment,
    DivisionAssignment,
    Swap,
};

template <typename T, typename = std::enable_if_t<std::is_arithmetic<T>::value>>
class PrimitiveWrapper : public Subject<PrimitiveWrapperOperatorType> {
    T value;

public:
    constexpr PrimitiveWrapper() noexcept: value() {
        NotifyObservers(PrimitiveWrapperOperatorType::DefaultConstructor);
    }
    constexpr PrimitiveWrapper(T const& value) noexcept: value(value) {
        NotifyObservers(PrimitiveWrapperOperatorType::ValueCopyConstructor);
    }
    constexpr PrimitiveWrapper(T && value) noexcept: value(value) {
        NotifyObservers(PrimitiveWrapperOperatorType::ValueMoveConstructor);
    }
    PrimitiveWrapper(PrimitiveWrapper<T> const& other) noexcept: value(other.value) {
        NotifyObservers(PrimitiveWrapperOperatorType::CopyConstructor);
    }
    PrimitiveWrapper(PrimitiveWrapper<T> && other) noexcept: value(std::exchange(other.value, T())) {
        NotifyObservers(PrimitiveWrapperOperatorType::MoveConstructor);
    }
    
    // constexpr T const& get() const noexcept { return value; }

    constexpr operator T() const noexcept {
        NotifyObservers(PrimitiveWrapperOperatorType::ConversionToValueType);
        return value;
    }

    PrimitiveWrapper& operator=(PrimitiveWrapper<T> const& other) {
        value = other.value;
        NotifyObservers(PrimitiveWrapperOperatorType::CopyAssignment);
        return *this;
    }

    PrimitiveWrapper& operator=(PrimitiveWrapper<T> && other) {
        // reset other not needed here
        value = other.value;
        NotifyObservers(PrimitiveWrapperOperatorType::MoveAssignment);
        return *this;
    }

    PrimitiveWrapper& operator=(T const& value) {
        this->value = value;
        NotifyObservers(PrimitiveWrapperOperatorType::ValueCopyAssignment);
        return *this;
    }
    PrimitiveWrapper& operator=(T && value) {
        this->value = value;
        NotifyObservers(PrimitiveWrapperOperatorType::ValueMoveAssignment);
        return *this;
    }

    PrimitiveWrapper& operator++() noexcept { 
        NotifyObservers(PrimitiveWrapperOperatorType::PrefixIncrement);
        ++value;
        return *this;
    }
    PrimitiveWrapper operator++(int) noexcept {
        PrimitiveWrapper copy(value);
        ++value;
        NotifyObservers(PrimitiveWrapperOperatorType::PrefixIncrement);
        return copy;
    }

    PrimitiveWrapper& operator--() noexcept { 
        --value;
        NotifyObservers(PrimitiveWrapperOperatorType::PrefixDecrement);
        return *this; 
    }
    PrimitiveWrapper operator--(int) noexcept {
        PrimitiveWrapper copy(value);
        --value;
        NotifyObservers(PrimitiveWrapperOperatorType::PostfixDecrement);
        return copy;
    }

    PrimitiveWrapper& operator+=(T const& other) noexcept {
        value += other;
        NotifyObservers(PrimitiveWrapperOperatorType::AdditionAssignment);
        return *this;
    }
    PrimitiveWrapper& operator+=(PrimitiveWrapper<T> const& other) { return *this += other.value; }

    PrimitiveWrapper& operator-=(T const& other) noexcept {
        value -= other;
        NotifyObservers(PrimitiveWrapperOperatorType::SubtractionAssignment);
        return *this;
    }
    PrimitiveWrapper& operator-=(PrimitiveWrapper<T> const& other) { return *this -= other.value; }

    PrimitiveWrapper& operator*=(T const& other) noexcept {
        value *= other;
        NotifyObservers(PrimitiveWrapperOperatorType::MultiplicationAssignment);
        return *this;
    }
    PrimitiveWrapper& operator*=(PrimitiveWrapper<T> const& other) { return *this *= other.value; }

    PrimitiveWrapper& operator/=(T const& other) noexcept {
        value /= other;
        NotifyObservers(PrimitiveWrapperOperatorType::DivisionAssignment);
        return *this;
    }
    PrimitiveWrapper& operator/=(PrimitiveWrapper<T> const& other) { return *this /= other.value; }

    // template <typename = std::enable_if_t<std::is_integral<T>::value>>
    // PrimitiveWrapper& operator%=(T const& other) noexcept {
    //     std::cout << "%= operator" << std::endl;
    //     value %= other;
    //     return *this;
    // }

    // template <typename std::enable_if<std::is_integral<T>::value, T>::type* = nullptr>
    // PrimitiveWrapper& operator%=(PrimitiveWrapper const& other) { return *this %= other.value; }

    // template <typename = std::enable_if_t<std::is_integral<T>::value>>
    // PrimitiveWrapper& operator<<=(T const& other) noexcept {
    //     std::cout << "<<= operator" << std::endl;
    //     value <<= other;
    //     return *this;
    // }
    // template <typename = std::enable_if_t<std::is_integral<T>::value>>
    // PrimitiveWrapper& operator<<=(PrimitiveWrapper<T> const& other) { return *this <<= other.value; }

    // template <typename = std::enable_if_t<std::is_integral<T>::value>>
    // PrimitiveWrapper& operator>>=(T const& other) noexcept {
    //     std::cout << "%= operator" << std::endl;
    //     value >>= other;
    //     return *this;
    // }
    // template <typename = std::enable_if_t<std::is_integral<T>::value>>
    // PrimitiveWrapper& operator>>=(PrimitiveWrapper<T> const& other) { return *this >>= other.value; }

    // template <typename = std::enable_if_t<std::is_integral<T>::value>>
    // PrimitiveWrapper& operator&=(T const& other) noexcept {
    //     std::cout << "&= operator" << std::endl;
    //     value &= other;
    //     return *this;
    // }
    // template <typename = std::enable_if_t<std::is_integral<T>::value>>
    // PrimitiveWrapper& operator&=(PrimitiveWrapper<T> const& other) { return *this &= other.value; }

    // template <typename = std::enable_if_t<std::is_integral<T>::value>>
    // PrimitiveWrapper& operator|=(T const& other) noexcept {
    //     std::cout << "|= operator" << std::endl;
    //     value |= other;
    //     return *this;
    // }
    // template <typename = std::enable_if_t<std::is_integral<T>::value>>
    // PrimitiveWrapper& operator|=(PrimitiveWrapper<T> const& other) { return *this |= other.value; }

    // template <typename = std::enable_if_t<std::is_integral<T>::value>>
    // PrimitiveWrapper& operator^=(T const& other) noexcept {
    //     std::cout << "^= operator" << std::endl;
    //     value ^= other;
    //     return *this;
    // }
    // template <typename = std::enable_if_t<std::is_integral<T>::value>>
    // PrimitiveWrapper& operator^=(PrimitiveWrapper<T> const& other) { return *this ^= other.value; }

    friend constexpr std::istream& operator>>(std::istream& is, PrimitiveWrapper<T> & rhs) { return is >> rhs.value; }
    friend constexpr std::ostream& operator<<(std::ostream& os, const PrimitiveWrapper<T>& rhs) { return os << rhs.value; }

    friend constexpr PrimitiveWrapper operator+(PrimitiveWrapper const& lhs, T const& rhs) noexcept { return lhs.value + rhs; }
    friend constexpr PrimitiveWrapper operator+(T const& lhs, PrimitiveWrapper const& rhs) noexcept { return lhs + rhs.value; }
    friend constexpr PrimitiveWrapper operator+(PrimitiveWrapper const& lhs, PrimitiveWrapper<T> const& rhs) noexcept { return lhs.value + rhs.value;}

    friend constexpr PrimitiveWrapper operator-(PrimitiveWrapper const& lhs, T const& rhs) noexcept { return lhs.value - rhs; }
    friend constexpr PrimitiveWrapper operator-(T const& lhs, PrimitiveWrapper const& rhs) noexcept { return lhs - rhs.value; }
    friend constexpr PrimitiveWrapper operator-(PrimitiveWrapper const& lhs, PrimitiveWrapper<T> const& rhs) noexcept { return lhs.value - rhs.value;}

    friend constexpr PrimitiveWrapper operator*(PrimitiveWrapper const& lhs, T const& rhs) noexcept { return lhs.value * rhs; }
    friend constexpr PrimitiveWrapper operator*(T const& lhs, PrimitiveWrapper const& rhs) noexcept { return lhs * rhs.value; }
    friend constexpr PrimitiveWrapper operator*(PrimitiveWrapper const& lhs, PrimitiveWrapper<T> const& rhs) noexcept { return lhs.value * rhs.value;}

    friend constexpr PrimitiveWrapper operator/(PrimitiveWrapper const& lhs, T const& rhs) noexcept { return lhs.value / rhs; }
    friend constexpr PrimitiveWrapper operator/(T const& lhs, PrimitiveWrapper const& rhs) noexcept { return lhs / rhs.value; }
    friend constexpr PrimitiveWrapper operator/(PrimitiveWrapper const& lhs, PrimitiveWrapper<T> const& rhs) noexcept { return lhs.value / rhs.value;}

    // template <typename = std::enable_if_t<std::is_integral<T>::value>>
    // friend constexpr PrimitiveWrapper operator%(PrimitiveWrapper const& lhs, T const& rhs) noexcept { return lhs.value % rhs; }
    // template <typename = std::enable_if_t<std::is_integral::value>>
    // friend constexpr PrimitiveWrapper operator%(T const& lhs, PrimitiveWrapper const& rhs) noexcept { return lhs % rhs.value; }
    // template <typename = std::enable_if_t<std::is_integral::value>>
    // friend constexpr PrimitiveWrapper operator%(PrimitiveWrapper const& lhs, PrimitiveWrapper const& rhs) noexcept { return lhs.value % rhs.value;}

    friend constexpr bool operator< (const PrimitiveWrapper& lhs, const T& rhs){ return lhs.value < rhs; }
    friend constexpr bool operator> (const PrimitiveWrapper& lhs, const T& rhs){ return rhs < lhs; }
    friend constexpr bool operator<=(const PrimitiveWrapper& lhs, const T& rhs){ return !(lhs > rhs); }
    friend constexpr bool operator>=(const PrimitiveWrapper& lhs, const T& rhs){ return !(lhs < rhs); }

    friend constexpr bool operator< (const PrimitiveWrapper& lhs, const PrimitiveWrapper& rhs){ return lhs.value < rhs.value; }
    friend constexpr bool operator> (const PrimitiveWrapper& lhs, const PrimitiveWrapper& rhs){ return rhs < lhs; }
    friend constexpr bool operator<=(const PrimitiveWrapper& lhs, const PrimitiveWrapper& rhs){ return !(lhs > rhs); }
    friend constexpr bool operator>=(const PrimitiveWrapper& lhs, const PrimitiveWrapper& rhs){ return !(lhs < rhs); }

    friend constexpr bool operator< (const T& lhs, const PrimitiveWrapper& rhs){ return lhs < rhs.value; }
    friend constexpr bool operator> (const T& lhs, const PrimitiveWrapper& rhs){ return rhs < lhs; }
    friend constexpr bool operator<=(const T& lhs, const PrimitiveWrapper& rhs){ return !(lhs > rhs); }
    friend constexpr bool operator>=(const T& lhs, const PrimitiveWrapper& rhs){ return !(lhs < rhs); }

    PrimitiveWrapper& swap(PrimitiveWrapper<T>& other) {
        std::swap(value, other.value);
        NotifyObservers(PrimitiveWrapperOperatorType::Swap);
        return *this;
    }
};