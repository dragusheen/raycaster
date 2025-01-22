/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

#ifndef GRADE_DE_VECTOR_SFML_HPP_
#define GRADE_DE_VECTOR_SFML_HPP_

/*  ---- CLASS ---- */
namespace gd
{
    template <typename T>
    class Vector
    {
        public:
            Vector();
            Vector(T x, T y);
            Vector(T x, T y, T z);
            ~Vector() = default;

            Vector<T> operator+(const Vector<T> &vector);
            Vector<T> &operator+=(const Vector<T> &vector);
            Vector<T> operator-(const Vector<T> &vector);
            Vector<T> &operator-=(const Vector<T> &vector);
            Vector<T> operator*(const Vector<T> &vector);
            Vector<T> &operator*=(const Vector<T> &vector);
            Vector<T> operator/(const Vector<T> &vector);
            Vector<T> &operator/=(const Vector<T> &vector);
            bool operator==(const Vector<T> &vector);
            bool operator!=(const Vector<T> &vector);

            T x;
            T y;
            T z;
    };
}

#endif
