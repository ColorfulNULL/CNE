#include "Vector2D.hpp"

cne::Vector2D cne::Vector2D::Normalized() const
{
    double len = Length();
    if (len < 1e-12) return Vector2D(0, 0);
    return Vector2D(x_ / len, y_ / len);
}

cne::Vector2D& cne::Vector2D::Normalize()
{
    double len = Length();
    if (len < 1e-12)
    {
        x_ = 0; y_ = 0;
    }
    else
    {
        x_ /= len; y_ /= len;
    }
    return *this;
}

cne::Vector2D& cne::Vector2D::SetLength(double newLength)
{
    double len = Length();
    if (len < 1e-12)
    {
        x_ = 0; y_ = 0;
    }
    else
    {
        double scale = newLength / len;
        x_ *= scale; y_ *= scale;
    }
    return *this;
}

cne::Vector2D& cne::Vector2D::RotateRad(double angle)
{
    double cosA = std::cos(angle);
    double sinA = std::sin(angle);
    double newX = x_ * cosA - y_ * sinA;
    double newY = x_ * sinA + y_ * cosA;
    x_ = newX; y_ = newY;
    return *this;
}

cne::Vector2D& cne::Vector2D::RotateDeg(double angleDeg)
{
    return RotateRad(angleDeg * M_PI / 180.0);
}

cne::Vector2D cne::Vector2D::RotatedRad(double angle) const
{
    Vector2D result(*this);
    result.RotateRad(angle);
    return result;
}

cne::Vector2D cne::Vector2D::RotatedDeg(double angleDeg) const
{
    Vector2D result(*this);
    result.RotateDeg(angleDeg);
    return result;
}

double cne::Vector2D::DistanceTo(const Vector2D& other) const
{
    return (other - *this).Length();
}
double cne::Vector2D::DistanceSquaredTo(const Vector2D& other) const
{
    return (other - *this).LengthSquared();
}

double cne::Vector2D::Angle() const
{
    return std::atan2(y_, x_);
}
double cne::Vector2D::AngleDeg() const
{
    return Angle() * 180.0 / M_PI;
}

double cne::Vector2D::AngleBetween(const Vector2D& other) const
{
    double d = Dot(other);
    double l1 = Length();
    double l2 = other.Length();
    if (l1 < 1e-12 || l2 < 1e-12) return 0.0;
    double cosA = std::clamp(d / (l1 * l2), -1.0, 1.0);
    return std::acos(cosA);
}
double cne::Vector2D::AngleDegBetween(const Vector2D& other) const
{
    return AngleBetween(other) * 180.0 / M_PI;
}

cne::Vector2D cne::Vector2D::Lerp(const Vector2D& target, double t) const
{
    return Vector2D(x_ + (target.x_ - x_) * t, y_ + (target.y_ - y_) * t);
}

cne::Vector2D cne::Vector2D::ProjectOnto(const Vector2D& other) const
{
    double l2 = other.LengthSquared();
    if (l2 < 1e-12) return Vector2D(0, 0);
    double factor = Dot(other) / l2;
    return other * factor;
}

cne::Vector2D cne::Vector2D::Reflect(const Vector2D& normal) const
{
    Vector2D n = normal.Normalized();
    return *this - 2.0 * Dot(n) * n;
}

cne::Vector2D cne::Vector2D::Zero() { return Vector2D(0, 0); }
cne::Vector2D cne::Vector2D::One() { return Vector2D(1, 1); }
cne::Vector2D cne::Vector2D::Up() { return Vector2D(0, 1); }
cne::Vector2D cne::Vector2D::Down() { return Vector2D(0, -1); }
cne::Vector2D cne::Vector2D::Left() { return Vector2D(-1, 0); }
cne::Vector2D cne::Vector2D::Right() { return Vector2D(1, 0); }

cne::Vector2D cne::Vector2D::UpLeft()
{
    double inv = 1.0 / std::sqrt(2.0);
    return Vector2D(-inv, inv);
}
cne::Vector2D cne::Vector2D::UpRight()
{
    double inv = 1.0 / std::sqrt(2.0);
    return Vector2D(inv, inv);
}
cne::Vector2D cne::Vector2D::DownLeft()
{
    double inv = 1.0 / std::sqrt(2.0);
    return Vector2D(-inv, -inv);
}
cne::Vector2D cne::Vector2D::DownRight()
{
    double inv = 1.0 / std::sqrt(2.0);
    return Vector2D(inv, -inv);
}

std::ostream& operator<<(std::ostream& os, const cne::Vector2D& v)
{
    os << "(" << v.x_ << ", " << v.y_ << ")";
    return os;
}