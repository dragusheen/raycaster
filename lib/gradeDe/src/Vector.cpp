/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/*  ---- INCLUDES ---- */
#include "GradeDe/Vector.hpp"

namespace gd
{
    template <typename T>
    Vector<T>::Vector()
        : x(0), y(0), z(0)
    {
    }

    template <typename T>
    Vector<T>::Vector(T x, T y)
        : x(x), y(y), z(0)
    {
    }

    template <typename T>
    Vector<T>::Vector(T x, T y, T z)
        : x(x), y(y), z(z)
    {
    }

    template <typename T>
    Vector<T> Vector<T>::operator+(const Vector<T> &vector)
    {
        return Vector<T>(x + vector.x, y + vector.y, z + vector.z);
    }

    template <typename T>
    Vector<T> &Vector<T>::operator+=(const Vector<T> &vector)
    {
        x += vector.x;
        y += vector.y;
        z += vector.z;
        return *this;
    }

    template <typename T>
    Vector<T> Vector<T>::operator-(const Vector<T> &vector)
    {
        return Vector<T>(x - vector.x, y - vector.y, z - vector.z);
    }

    template <typename T>
    Vector<T> &Vector<T>::operator-=(const Vector<T> &vector)
    {
        x -= vector.x;
        y -= vector.y;
        z -= vector.z;
        return *this;
    }

    template <typename T>
    Vector<T> Vector<T>::operator*(const Vector<T> &vector)
    {
        return Vector<T>(x * vector.x, y * vector.y, z * vector.z);
    }

    template <typename T>
    Vector<T> &Vector<T>::operator*=(const Vector<T> &vector)
    {
        x *= vector.x;
        y *= vector.y;
        z *= vector.z;
        return *this;
    }

    template <typename T>
    Vector<T> Vector<T>::operator/(const Vector<T> &vector)
    {
        return Vector<T>(x / vector.x, y / vector.y, z / vector.z);
    }

    template <typename T>
    Vector<T> &Vector<T>::operator/=(const Vector<T> &vector)
    {
        x /= vector.x;
        y /= vector.y;
        z /= vector.z;
        return *this;
    }

    template <typename T>
    bool Vector<T>::operator==(const Vector<T> &vector)
    {
        return x == vector.x && y == vector.y && z == vector.z;
    }

    template <typename T>
    bool Vector<T>::operator!=(const Vector<T> &vector)
    {
        return x != vector.x || y != vector.y || z != vector.z;
    }

    template class Vector<int>;
    template class Vector<unsigned int>;
    template class Vector<float>;
    template class Vector<double>;
} // namespace gd
