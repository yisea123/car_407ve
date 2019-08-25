#pragma once

#include <math.h>
#include <limits>
#include <stdint.h>
#include "definitions.h"

#ifdef __GNUC__
#include <float.h>
 #define WARN_IF_UNUSED __attribute__ ((warn_unused_result))
#else
 #define WARN_IF_UNUSED
#endif

/* 
 * @brief: Check whether a float is zero
 */
template <typename T>
inline bool is_zero(const T fVal1) {
    return (fabsf(static_cast<float>(fVal1)) < FLT_EPSILON);
}

/* 
 * @brief: Check whether a float is greater than zero
 */
template <typename T>
inline bool is_positive(const T fVal1) {
    return (static_cast<float>(fVal1) >= FLT_EPSILON);
}


/* 
 * @brief: Check whether a float is less than zero
 */
template <typename T>
inline bool is_negative(const T fVal1) {
    return (static_cast<float>(fVal1) <= (-1.0 * FLT_EPSILON));
}


/*
 * A variant of asin() that checks the input ranges and ensures a valid angle
 * as output. If nan is given as input then zero is returned.
 */
template <typename T>
float safe_asin(const T v);

/*
 * A variant of sqrt() that checks the input ranges and ensures a valid value
 * as output. If a negative number is given then 0 is returned.  The reasoning
 * is that a negative number for sqrt() in our code is usually caused by small
 * numerical rounding errors, so the real input should have been zero
 */
template <typename T>
float safe_sqrt(const T v);

// invOut is an inverted 4x4 matrix when returns true, otherwise matrix is Singular
bool inverse3x3(float m[], float invOut[]) WARN_IF_UNUSED;

// invOut is an inverted 3x3 matrix when returns true, otherwise matrix is Singular
bool inverse4x4(float m[],float invOut[]) WARN_IF_UNUSED;

// matrix multiplication of two NxN matrices
float *mat_mul(float *A, float *B, uint8_t n);

// matrix algebra
bool inverse(float x[], float y[], uint16_t dim) WARN_IF_UNUSED;

/*
 * Constrain an angle to be within the range: -180 to 180 degrees. The second
 * parameter changes the units. Default: 1 == degrees, 10 == dezi,
 * 100 == centi.
 */
template <typename T>
float wrap_180(const T angle, float unit_mod = 1);

/*
 * Wrap an angle in centi-degrees. See wrap_180().
 */
template <typename T>
auto wrap_180_cd(const T angle) -> decltype(wrap_180(angle, 100.f));

/*
 * Constrain an euler angle to be within the range: 0 to 360 degrees. The
 * second parameter changes the units. Default: 1 == degrees, 10 == dezi,
 * 100 == centi.
 */
template <typename T>
float wrap_360(const T angle, float unit_mod = 1);

/*
 * Wrap an angle in centi-degrees. See wrap_360().
 */
template <typename T>
auto wrap_360_cd(const T angle) -> decltype(wrap_360(angle, 100.f));

/*
  wrap an angle in radians to -PI ~ PI (equivalent to +- 180 degrees)
 */
template <typename T>
float wrap_PI(const T radian);

/*
 * wrap an angle in radians to 0..2PI
 */
template <typename T>
float wrap_2PI(const T radian);

/*
 * Constrain a value to be within the range: low and high
 */
template <typename T>
T constrain_value(const T amt, const T low, const T high);

inline float constrain_float(const float amt, const float low, const float high)
{
    return constrain_value(amt, low, high);
}

inline int16_t constrain_int16(const int16_t amt, const int16_t low, const int16_t high)
{
    return constrain_value(amt, low, high);
}

inline int32_t constrain_int32(const int32_t amt, const int32_t low, const int32_t high)
{
    return constrain_value(amt, low, high);
}

inline int64_t constrain_int64(const int64_t amt, const int64_t low, const int64_t high)
{
    return constrain_value(amt, low, high);
}

// degrees -> radians
static inline constexpr float radians(float deg)
{
    return deg * DEG_TO_RAD;
}

// radians -> degrees
static inline constexpr float degrees(float rad)
{
    return rad * RAD_TO_DEG;
}

template<typename T>
float sq(const T val)
{
    float v = static_cast<float>(val);
    return v*v;
}

/*
 * Variadic template for calculating the square norm of a vector of any
 * dimension.
 */
template<typename T, typename... Params>
float sq(const T first, const Params... parameters)
{
    return sq(first) + sq(parameters...);
}

/*
 * Variadic template for calculating the norm (pythagoras) of a vector of any
 * dimension.
 */
template<typename T, typename U, typename... Params>
float norm(const T first, const U second, const Params... parameters)
{
    return sqrtf(sq(first, second, parameters...));
}

inline uint32_t hz_to_nsec(uint32_t freq)
{
    return AP_NSEC_PER_SEC / freq;
}

inline uint32_t nsec_to_hz(uint32_t nsec)
{
    return AP_NSEC_PER_SEC / nsec;
}

inline uint32_t usec_to_nsec(uint32_t usec)
{
    return usec * AP_NSEC_PER_USEC;
}

inline uint32_t nsec_to_usec(uint32_t nsec)
{
    return nsec / AP_NSEC_PER_USEC;
}

inline uint32_t hz_to_usec(uint32_t freq)
{
    return AP_USEC_PER_SEC / freq;
}

inline uint32_t usec_to_hz(uint32_t usec)
{
    return AP_USEC_PER_SEC / usec;
}

/*
  linear interpolation based on a variable in a range
 */
float linear_interpolate(float low_output, float high_output,
                         float var_value,
                         float var_low, float var_high);

/* cubic "expo" curve generator 
 * alpha range: [0,1] min to max expo
 * input range: [-1,1]
 */
float expo_curve(float alpha, float input);

/* throttle curve generator
 * thr_mid: output at mid stick
 * alpha: expo coefficient
 * thr_in: [0-1]
 */
float throttle_curve(float thr_mid, float alpha, float thr_in);

/* simple 16 bit random number generator */
uint16_t get_random16(void);

// confirm a value is a valid octal value
bool is_valid_octal(uint16_t octal) WARN_IF_UNUSED;