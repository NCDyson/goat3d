/*
libvmath - a vector math library
Copyright (C) 2004-2013 John Tsiombikas <nuclear@member.fsf.org>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef VMATH_H_
#define VMATH_H_

#include <math.h>
#include "vmath_types.h"

#ifndef M_PI
#define M_PI	PI
#endif

#ifndef M_E
#define M_E				2.718281828459045
#endif

#define PI				3.141592653589793
#define HALF_PI			1.570796326794897
#define QUARTER_PI		0.785398163397448
#define TWO_PI			6.283185307179586


#define RAD_TO_DEG(a) ((((scalar_t)a) * 360.0) / TWO_PI)
#define DEG_TO_RAD(a) (((scalar_t)a) * (PI / 180.0))

#define SQ(x) ((x) * (x))

#define MIN(a, b)	((a) < (b) ? (a) : (b))
#define MAX(a, b)	((a) > (b) ? (a) : (b))

#ifndef __GNUC__
#define round(x)	((x) >= 0 ? (x) + 0.5 : (x) - 0.5)
#endif

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

static VMATH_INLINE scalar_t smoothstep(float a, float b, float x);

static VMATH_INLINE scalar_t frand(scalar_t range);
static VMATH_INLINE vec3_t sphrand(scalar_t rad);

scalar_t integral(scalar_t (*f)(scalar_t), scalar_t low, scalar_t high, int samples);
scalar_t gaussian(scalar_t x, scalar_t mean, scalar_t sdev);

static VMATH_INLINE scalar_t lerp(scalar_t a, scalar_t b, scalar_t t);

scalar_t bspline(scalar_t a, scalar_t b, scalar_t c, scalar_t d, scalar_t t);
scalar_t spline(scalar_t a, scalar_t b, scalar_t c, scalar_t d, scalar_t t);
scalar_t bezier(scalar_t a, scalar_t b, scalar_t c, scalar_t d, scalar_t t);

scalar_t noise1(scalar_t x);
scalar_t noise2(scalar_t x, scalar_t y);
scalar_t noise3(scalar_t x, scalar_t y, scalar_t z);

scalar_t fbm1(scalar_t x, int octaves);
scalar_t fbm2(scalar_t x, scalar_t y, int octaves);
scalar_t fbm3(scalar_t x, scalar_t y, scalar_t z, int octaves);

scalar_t turbulence1(scalar_t x, int octaves);
scalar_t turbulence2(scalar_t x, scalar_t y, int octaves);
scalar_t turbulence3(scalar_t x, scalar_t y, scalar_t z, int octaves);

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#include "vmath.inl"

#include "vector.h"
#include "matrix.h"
#include "quat.h"
#include "sphvec.h"
#include "ray.h"
#include "geom.h"

#endif	/* VMATH_H_ */
