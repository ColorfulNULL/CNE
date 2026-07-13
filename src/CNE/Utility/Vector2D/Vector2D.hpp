#pragma once

#include "external.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace cne
{
    // 平面向量
    class Vector2D
    {
    public:
        double x_, y_;

        // 构造与赋值
        Vector2D(double x = 0.0, double y = 0.0) : x_(x), y_(y) {}
        Vector2D(const Vector2D&) = default;
        Vector2D& operator=(const Vector2D&) = default;

        // 基础运算符（内联）
        Vector2D operator+(const Vector2D& other) const
        {
            return Vector2D(x_ + other.x_, y_ + other.y_);
        }
        Vector2D operator-(const Vector2D& other) const
        {
            return Vector2D(x_ - other.x_, y_ - other.y_);
        }
        Vector2D operator*(double scalar) const
        {
            return Vector2D(x_ * scalar, y_ * scalar);
        }
        Vector2D operator/(double scalar) const
        {
            return Vector2D(x_ / scalar, y_ / scalar);
        }
        Vector2D operator-() const
        {
            return Vector2D(-x_, -y_);
        }

        Vector2D& operator+=(const Vector2D& other)
        {
            x_ += other.x_; y_ += other.y_; return *this;
        }
        Vector2D& operator-=(const Vector2D& other)
        {
            x_ -= other.x_; y_ -= other.y_; return *this;
        }
        Vector2D& operator*=(double scalar)
        {
            x_ *= scalar; y_ *= scalar; return *this;
        }
        Vector2D& operator/=(double scalar)
        {
            x_ /= scalar; y_ /= scalar; return *this;
        }

        bool operator==(const Vector2D& other) const
        {
            return std::fabs(x_ - other.x_) < 1e-9 && std::fabs(y_ - other.y_) < 1e-9;
        }
        bool operator!=(const Vector2D& other) const
        {
            return !(*this == other);
        }

        // 友元（支持左乘标量）
        friend Vector2D operator*(double scalar, const Vector2D& v)
        {
            return v * scalar;
        }

        // 模长与平方模长（内联）
        double Length() const
        {
            return std::sqrt(x_ * x_ + y_ * y_);
        }
        double LengthSquared() const
        {
            return x_ * x_ + y_ * y_;
        }

        // 简单计算（内联）
        double Dot(const Vector2D& other) const
        {
            return x_ * other.x_ + y_ * other.y_;
        }
        double Cross(const Vector2D& other) const
        {
            return x_ * other.y_ - y_ * other.x_;
        }

        // 其他成员函数（仅在头文件中声明）
        Vector2D Normalized() const;
        Vector2D& Normalize();

        Vector2D& SetLength(double newLength);

        Vector2D& RotateRad(double angle);
        Vector2D& RotateDeg(double angleDeg);
        Vector2D RotatedRad(double angle) const;
        Vector2D RotatedDeg(double angleDeg) const;

        double DistanceTo(const Vector2D& other) const;
        double DistanceSquaredTo(const Vector2D& other) const;

        double Angle() const;
        double AngleDeg() const;
        double AngleBetween(const Vector2D& other) const;
        double AngleDegBetween(const Vector2D& other) const;

        Vector2D Lerp(const Vector2D& target, double t) const;
        Vector2D ProjectOnto(const Vector2D& other) const;
        Vector2D Reflect(const Vector2D& normal) const;

        // 静态预设值（声明）
        static Vector2D Zero();
        static Vector2D One();
        static Vector2D Up();
        static Vector2D Down();
        static Vector2D Left();
        static Vector2D Right();
        static Vector2D UpLeft();
        static Vector2D UpRight();
        static Vector2D DownLeft();
        static Vector2D DownRight();

        // 流输出（友元）
        friend std::ostream& operator<<(std::ostream& os, const Vector2D& v);
    };
}