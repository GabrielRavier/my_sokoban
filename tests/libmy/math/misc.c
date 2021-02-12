/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests a bunch of math stuff
*/

#include "../tests_header.h"
#include "my/stdlib.h"

// (search for "math")

// Get stuff from bionic for signbit, isfinite, isnan, isinf, fpclassify,
// isnormal, finitef, isfinite, finite, isinf, acos, acosf, acosl, asin, asinf,
// asinl, atan, atanl, atan2, atanf, atan2f, atan2l, cos, cosf, cosl, sin, sinf,
// sinl, sincos, sincosf, sincosl, tan, tanf, tanl, acosh, acoshf, acoshl,
// asinh, asinhf, asinhl, atanh, atanhf, atanhl, cosh, coshf, coshl, sinh,
// sinhf, sinhl, tanh, tanhf, tanhl, log, logf, logl, log2, log2f, log2l, log10,
// log10f, log10l, cbrt, cbrtf, cbrtl, sqrt, sqrtf, sqrtl, exp, expf, expl,
// exp2, exp2f, exp2l, expm1, expm1f, expm1l, pow, powf, powl, ceil, ceilf,
// ceill, floor, floorf, floorl, fabs, fabsf, fabsl, ldexp, ldexpf, ldexpl,
// fmod, fmodf, fmodl, remainder, remainderf, remainderl, drem, dremf, fmax,
// fmaxf, fmaxl, fmin, fminf, fminl, fma, fmaf, fmal, hypot, hypotf, hypotl,
// erf, erff, erfl, erfc, erfcf, erfcl, lrint, rint, lrintf, lrintl, rintf,
// rintl, nearbyint, nearbyintf, nearbyintl, fetestexcept, fesetenv,
// feclearexcept, lround, lroundf, lroundl, llround, llroundf, llroundl, ilobg,
// ilogbf, ilogbl, logb, logbf, logbl, log1p, log1pf, log1pl, fdim, fdimf,
// fdiml, round, roundf, roundl, trunc, truncf, truncl, nextafter, nextafterf,
// nextafterl, nexttoward, nexttowardf, nexttowardl, copysign, copysignf,
// copysignl, significand, significandf, significandl, scalb, scalbf, scalbln,
// scalblnf, scalblnl, scalbn, scalbnf, scalbnl, gamma, gammaf, lgamma, lgammaf,
// lgammal, lgamma_r, lgammaf_r, lgammal_r, tgamma, tgammaf, tgammal, j0, j0f,
// j0l, j1, j1f, jn, jnf, y0, y0f, y1, y1f, yn, ynf, frexp, frexpf, frexpl,
// modf, modff, modfl, remquo, remquof, remquol, exp2, exp2f, exp2l

// Get stuff from cloudlibc for acos, asin, atan, acosh, asinh, atanh, cos, sin, 
// tan, cosh, sinh, tanh, exp, log, pow, sqrt, fabs, atan2, cbrt, ceil,
// copysign, erf, erfc, exp2, expm1, fdim, floor, fma, fmax, fmin, fmod, frexp,
// hypot, ldexp, lgamma, log10, log1p, log2, logb, nearbyint, nextafter,
// nexttoward, remainder, remquo, rint, round, scalbn, scalbln, tgamma, trunc,
// carg, cimag, conj, cproj, creal

// Get stuff from Defora for cos, cosl, sin, sinl, fabs, fabsf, fabsl, fmod,
// fmodl, pow, round, sqrt

// Get stuff from plauger for fabs, ceil, floor, fmod, frexp, ldexp, modf, acos,
// asin, atan, atan2, cos, sin, tan, cosh, exp, log, log10, pow, sinh, sqrt,
// tanh

// Get stuff from libc-test for lrint, sqrt, pow
// Get stuff from Escape for round, roundf
// Get stuff from osv for nearbyint, finite
