#pragma once

#include <type_traits>
#include <list>
#include <unordered_map>

template <typename T, typename = std::enable_if_t<std::is_enum<T>::value>>
class IObserver {
public:
    virtual ~IObserver(){};
    virtual void Update(const T& value) = 0;
};

template <typename T, typename = std::enable_if_t<std::is_enum<T>::value>>
class ISubject {
public:
    virtual ~ISubject(){};
    virtual void Attach(IObserver<T> *observer) = 0;
    virtual void Detach(IObserver<T> *observer) = 0;

protected:
    virtual void NotifyObservers(const T& value) const = 0;
};

template <typename T>
class Subject : public ISubject<T> {
private:
    std::list<IObserver<T>*> observers;

public:
    Subject() = default;
    inline void Attach(IObserver<T> *observer) override { observers.push_back(observer); }
    inline void Detach(IObserver<T> *observer) override { observers.remove(observer); }

protected:
    void NotifyObservers(const T& value) const override { for (IObserver<T>* observer : observers) observer->Update(value); }
};