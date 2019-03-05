#ifndef VARIABLE_H
#define VARIABLE_H

template <typename T>
class Variable
{
public:
    Variable(T value, T derivative) :value(value), derivative(derivative) {}
    T value;
    T derivative;
};

template <typename T>
Variable<T> operator+(Variable<T> a, Variable<T> b)
{
    return Variable<T>(a.value + b.value, a.derivative + b.derivative);
}

template <typename T>
Variable<T> operator*(Variable<T> a, Variable<T> b)
{
    return Variable<T>(a.value * b.value, a.derivative * b.value + b.derivative * a.value);
}

template <typename T>
Variable<T> operator-(Variable<T> a, Variable<T> b)
{
    return Variable<T>(a.value - b.value, a.derivative - b.derivative);
}

#endif // VARIABLE_H
