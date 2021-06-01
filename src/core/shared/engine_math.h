//
// Created by Dimme on 9/03/2021.
//

#ifndef I3D_ENGINE_ENGINE_MATH_H
#define I3D_ENGINE_ENGINE_MATH_H

#include <cmath>
#include <iostream>
#include <ctime>

#define PI 3.14
#define PI2 3.14/2
#define DEG_TO_RAD (PI/180)

struct Vector2 {
    float x = 0;
    float y = 0;

    Vector2() = default;

    Vector2(float x, float y) {
        this->x = x;
        this->y = y;
    }

    Vector2 opposite() const {
        return {-x, -y};
    }

    static Vector2 zero() {
        return {0, 0};
    }

    static Vector2 identity() {
        return {1, 1};
    }

    Vector2 operator-(const Vector2& other) const {
        return {x - other.x, y - other.y};
    }

    Vector2 operator+(const Vector2& other) const {
        return {x + other.x, y + other.y};
    }
};

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

    Vector3 opposite() const {
        return {-x, -y, -z};
    }

    static Vector3 zero() {
        return {0, 0, 0};
    }

    static Vector3 identity() {
        return {1, 1, 1};
    }

    static Vector3 forward() {
        return {0, 0, 1};
    }

    static Vector3 up() {
        return {0, 1, 0};
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

struct Vector4 {
    float x = 0;
    float y = 0;
    float z = 0;
    float w = 0;

    Vector4() = default;

    Vector4(float x, float y, float z, float w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    Vector4 opposite() const {
        return {-x, -y, -z, -w};
    }

    static Vector4 zero() {
        return {0, 0, 0, 0};
    }

    static Vector4 identity() {
        return {1, 1, 1, 1};
    }
};


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

    static Vector3 MidPoint(Vector3 v1, Vector3 v2) {
        return {(v1.x + v2.x) / 2, (v1.y + v2.y) / 2, (v1.z + v2.z) / 2};
    }

    static Vector3 Cross(Vector3 v1, Vector3 v2) {
        return {
                v1.y * v2.z - v1.z * v2.y,
                v1.z * v2.x - v1.x * v2.z,
                v1.x * v2.y - v1.y * v2.x
        };
    }

    static void Print(Vector3 vector) {
        std::cout << "X: " << vector.x << " | Y: " << vector.y << " | Z: " << vector.z << std::endl;
    }

    static void Print(Vector2 vector) {
        std::cout << "X: " << vector.x << " | Y: " << vector.y << std::endl;
    }

    static Vector3 Normalize(Vector3 vector) {
        float magnitude = Magnitude(vector);
        if (magnitude > 0.00001F) {
            return vector / magnitude;
        } else {
            return Vector3::zero();
        }
    }


    // Dot product of vector
    static float Dot(Vector3 l, Vector3 r) {
        return l.x * r.x + l.y * r.y + l.z * r.z;
    }
};

struct Rotation {
    float x = 0;
    float y = 0;
    float z = 0;
    float w = 1;

    Rotation() = default;

    Rotation(float x, float y, float z, float w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    static Rotation zero() {
        return {0, 0, 0, 0};
    }

    static Rotation identity() {
        return {0, 0, 0, 1};
    }

    float* ToRotationMatrix() const {
        float* mat = new float[16];

        // First row
        mat[0] = 1 - 2 * (z * z + y * y);
        mat[1] = 2 * (x * y + w * z);
        mat[2] = 2 * (z * x - w * y);
        mat[3] = 0;

        // Second row
        mat[4] = 2 * (x * y - w * z);
        mat[5] = 1 - 2 * (x * x + z * z);
        mat[6] = 2 * (y * z + w * x);
        mat[7] = 0;

        // Third row
        mat[8] = 2 * (z * x + w * y);
        mat[9] = 2 * (y * z - w * x);
        mat[10] = 1 - 2 * (x * x + y * y);
        mat[11] = 0;

        // Fourth row
        mat[12] = 0;
        mat[13] = 0;
        mat[14] = 0;
        mat[15] = 1;

        // Pad to 4x4 from 3x3

        return mat;
    }

    static Rotation FromEuler(Vector3 euler) {
        double cx = cos(euler.x * 0.5);
        double cy = cos(euler.y * 0.5);
        double cz = cos(euler.z * 0.5);
        double sx = sin(euler.x * 0.5);
        double sy = sin(euler.y * 0.5);
        double sz = sin(euler.z * 0.5);
        Rotation q = Rotation();
        q.x = cx * sy * sz + cy * cz * sx;
        q.y = cx * cz * sy - cy * sx * sz;
        q.z = cx * cy * sz - cz * sx * sy;
        q.w = sx * sy * sz + cx * cy * cz;
        return q;
    }

     Vector3 ToEuler() {
        Rotation rotation = *this;
        double sqw = rotation.w * rotation.w;
        double sqx = rotation.x * rotation.x;
        double sqy = rotation.y * rotation.y;
        double sqz = rotation.z * rotation.z;

        // Normalize or use other
        double unit = sqx + sqy + sqz + sqw;
        double cond = rotation.x * rotation.w - rotation.y * rotation.z;
        Vector3 vector;
        // Singularity at north pole
        if (cond > 0.4995f * unit) {
            vector.y = 2 * atan2(rotation.y, rotation.x);
            vector.x = PI2;
            vector.z = 0;
            return vector;
        }
        // Singularity at south pole
        if (cond < -0.4995f * unit) {
            vector.y = -2 * atan2(rotation.y, rotation.x);
            vector.x = -PI2;
            vector.z = 0;
            return vector;
        }
        // Yaw (Y)
        vector.y = atan2(2 * rotation.w * rotation.y + 2 * rotation.z * rotation.x,
                         1 - 2 * (rotation.x * rotation.x + rotation.y * rotation.y));
        // Pitch (X)
        vector.x = asin(2 * (rotation.w * rotation.x - rotation.y * rotation.z));

        // Roll (Z)
        vector.z = atan2(2 * rotation.w * rotation.z + 2 * rotation.x * rotation.y,
                         1 - 2 * (rotation.z * rotation.z + rotation.x * rotation.x));
        return vector;
    }

    static double Norm(Rotation rotation) {
        return sqrt(rotation.x * rotation.x +
                    rotation.y * rotation.y +
                    rotation.z * rotation.z +
                    rotation.w * rotation.w);
    }

    static Rotation Normalized(Rotation rotation) {
        return rotation / Norm(rotation);
    }

    Rotation Inverse() {
        double n = Norm(*this);
        return Conjugate(*this) / (n * n);
    }

    Rotation operator+(Rotation rhs) {
        return rhs += *this;
    }

    Rotation operator*(const Rotation rhs) {
        return *this *= rhs;
    }

    static Rotation Conjugate(Rotation rotation) {
        return {-rotation.x, -rotation.y, -rotation.z, rotation.w};
    }

    Rotation operator/(const double rhs) { return *this /= rhs; }

    Rotation& operator+=(const Rotation rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
        return *this;
    }

    struct Rotation& operator/=(const double rhs) {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        w /= rhs;
        return *this;
    }

    bool operator==(const Rotation compare) {
        return x == compare.x &&
               y == compare.y &&
               z == compare.z &&
               w == compare.w;
    }

    Vector3 operator*(const Vector3 rhs) {
        Rotation lhs = *this;
        Vector3 u = Vector3(lhs.x, lhs.y, lhs.z);
        double s = lhs.w;
        return u * (VectorUtil::Dot(u, rhs) * 2)
               + rhs * (s * s - VectorUtil::Dot(u, u))
               + VectorUtil::Cross(u, rhs) * (2.0 * s);
    }

    Rotation operator*=(const Rotation rhs) {
        Rotation q;
        q.w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
        q.x = x * rhs.w + w * rhs.x + y * rhs.z - z * rhs.y;
        q.y = w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x;
        q.z = w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w;
        *this = q;
        return *this;
    }

};

// UTIL

static float Lerp(float v1, float v2, float t) {
    return v1 + (v2 - v1) * t;
}

// Inclusive random helpers
inline int getRandomNumber(int min, int max) {
    return min + rand() % ((max + 1) - min);
}

inline bool getRandomBool() {
    return getRandomNumber(0, 1);
}

inline float randomSign(float number) {
    return getRandomNumber(0, 1) == 1 ? -number : number;
}

inline float getRandomNumber(float min, float max) {
    return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}


#endif //I3D_ENGINE_ENGINE_MATH_H
