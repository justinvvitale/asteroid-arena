//
// Created by Dimme on 9/03/2021.
//

#ifndef I3D_ENGINE_ENGINE_MATH_H
#define I3D_ENGINE_ENGINE_MATH_H

#include <cmath>

#define PI 3.14
#define DEG_TO_RAD (PI/180)

struct Vector3 {
    float x = 0;
    float y = 0;
    float z = 0;

    Vector3() = default;

    Vector3(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector3 opposite() {
        return {-x, -y, -z};
    }

    static Vector3 zero() {
        return {0, 0, 0};
    }

    static Vector3 identity() {
        return {1, 1, 1};
    }

    Vector3 operator+(const Vector3& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    Vector3 operator-(const Vector3& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    Vector3 operator*(const Vector3& other) const {
        return {x * other.x, y * other.y, z * other.z};
    }

    Vector3 operator*(const float& value) const {
        return {x * value, y * value, z * value};
    }

    Vector3 operator/(const float& value) const {
        return {x / value, y / value, z / value};
    }
};

struct Rotation {
    float x = 0;
    float y = 0;
    float z = 0;
    float angle = 0;

    Rotation() = default;

    Rotation(float x, float y, float z, float w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->angle = w;
    }

    static Rotation zero() {
        return {0, 0, 0, 0};
    }

};

// UTIL

static float Lerp(float v1, float v2, float t) {
    return v1 + (v2 - v1) * t;
}

// Inclusive random helpers
inline int getRandomNumber(int min, int max) {
    return min + (rand() % max);
}

inline float getRandomNumber(float min, float max) {
    return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}

class VectorUtil {

public:
    // Core functions

    // Distance between two vectors
    static float Distance(Vector3 vert1, Vector3 vert2) {
        float diffX = vert1.x - vert2.x;
        float diffY = vert1.y - vert2.y;
        float diffZ = vert1.z - vert2.z;
        return (float) std::sqrt(diffX * diffX + diffY * diffY + diffZ * diffZ);
    }

    // Distance from a line to a vector target
    static float DistanceFromLine(Vector3 point1, Vector3 point2, Vector3 target) {
        float lineDist = VectorUtil::Distance(point1, point2);
        float p1TargetDist = VectorUtil::Distance(point1, target);
        float p2TargetDist = VectorUtil::Distance(point2, target);

        float sumDist = (lineDist + p1TargetDist + p2TargetDist) / 2;

        return 2 * sqrt(sumDist * (sumDist - lineDist) * (sumDist - p1TargetDist) * (sumDist - p2TargetDist)) /
               lineDist;
    }

    static float Magnitude(Vector3 vector) {
        return (float) sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
    }

    static Vector3 Normalize(Vector3 vector) {
        float magnitude = Magnitude(vector);
        if (magnitude > 0.00001F) {
            return vector / magnitude;
        } else {
            return Vector3::zero();
        }
    }

    static Vector3 GetForwardVector(Rotation rotation) {
        return {(-sinf(rotation.angle * DEG_TO_RAD)), (cosf(rotation.angle * DEG_TO_RAD)), 0};
    }

    // Dot product of vector
    static float Dot(Vector3 l, Vector3 r) {
        return l.x * r.x + l.y * r.y + l.z * r.z;
    }
};


#endif //I3D_ENGINE_ENGINE_MATH_H
