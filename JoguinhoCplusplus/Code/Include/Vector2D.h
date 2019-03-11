#pragma once

#include <iostream>
#include <string>

class Vector2D {

private:
    float x_;
    float y_;
public:
    Vector2D() {
        this->zero();
    }

    Vector2D(const float& x, const float& y) {
        this->setX(x);
        this->setY(y);
    }

    ~Vector2D() = default;

    void setX(const float& x) {
        this->x_ = x;
    }

    float getX() {
        return this->x_;
    }

    void setY(const float& y) {
        this->y_ = y;
    }

    float getY() {
        return this->y_;
    }

    Vector2D& zero() {
        this->setX(0.0f);
        this->setY(0.0f);

        return *this;
    }

    Vector2D& operator+(const Vector2D& other) {
        this->x_ += other.x_;
        this->y_ += other.y_;

        return *this;
    }

    Vector2D& operator-(const Vector2D& other) {
        this->x_ -= other.x_;
        this->y_ -= other.y_;

        return *this;
    }

    Vector2D& operator*(const float& val) {
        this->x_ *= val;
        this->y_ *= val;

        return *this;
    }

    Vector2D& operator*(const int& val) {
        this->x_ *= static_cast<float>(val);
        this->y_ *= static_cast<float>(val);

        return *this;
    }

    Vector2D& operator*(const Vector2D& other) {
        this->x_ *= other.x_;
        this->y_ *= other.y_;

        return *this;
    }

    Vector2D& operator/(const Vector2D& other) {
        this->x_ /= other.x_;
        this->y_ /= other.y_;

        return *this;
    }

    Vector2D& operator+=(const Vector2D& other) {
        return this->operator+(other);
    }

    Vector2D& operator-=(const Vector2D& other) {
        return this->operator-(other);
    }

    Vector2D& operator*=(const float& val) {
        return this->operator*(val);
    }

    Vector2D& operator*=(const int& val) {
        return this->operator*(val);
    }

    Vector2D& operator*=(const Vector2D& other) {
        return this->operator*(other);
    }

    Vector2D& operator/=(const Vector2D& other) {
        return this->operator/(other);
    }

    friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec) {
        stream << "[x:" << vec.x_ << ", y:" << vec.y_ << "]\n";
        return stream;
    }

};