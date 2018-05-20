#pragma once


#define MATH_PI                     3.14159265358979323846f
#define MATH_PIDIV2					1.57079632679489661923f
#define MATH_PIDIV4					0.785398163397448309616f
#define MATH_PI2					6.28318530717958647693f
#define MATH_EPSILON                0.000001f


#define MATH_RAD_TO_DEG_COEF		57.29577951f
#define MATH_DEG_TO_RAD(x)          ((x) * 0.0174532925f)
#define MATH_RAD_TO_DEG(x)          ((x)* MATH_RAD_TO_DEG_COEF )


#define DEFAULT_TOLEARANCE_VALUE (1.e-4f)

#define MATRIX_ORDER_ROW_MAJOR			1
#define MATRIX_ORDER_COLOMN_MAJOR		2

// On windows we use Colum Major
//#define PLATFORM_CONFIG_MATRIX_ORDER	MATRIX_ORDER_COLOMN_MAJOR
#define PLATFORM_CONFIG_MATRIX_ORDER	MATRIX_ORDER_ROW_MAJOR

