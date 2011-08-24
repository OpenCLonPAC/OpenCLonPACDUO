#include <stdint.h>

/* scalar types  */
typedef int8_t          cl_char;
typedef uint8_t         cl_uchar;
typedef int16_t         cl_short    __attribute__((aligned(2)));
typedef uint16_t        cl_ushort   __attribute__((aligned(2)));
typedef int32_t         cl_int      __attribute__((aligned(4)));
typedef uint32_t        cl_uint     __attribute__((aligned(4)));
typedef int64_t         cl_long     __attribute__((aligned(8)));
typedef uint64_t        cl_ulong    __attribute__((aligned(8)));

typedef uint16_t        cl_half     __attribute__((aligned(2)));
typedef float           cl_float    __attribute__((aligned(4)));
typedef double          cl_double   __attribute__((aligned(8)));

/*
 * Vector types 
 *
 *  Note:   OpenCL requires that all types be naturally aligned. 
 *          This means that vector types must be naturally aligned.
 *          For example, a vector of four floats must be aligned to
 *          a 16 byte boundary (calculated as 4 * the natural 4-byte 
 *          alignment of the float).  The alignment qualifiers here
 *          will only function properly if your compiler supports them
 *          and if you don't actively work to defeat them.  For example,
 *          in order for a cl_float4 to be 16 byte aligned in a struct,
 *          the start of the struct must itself be 16-byte aligned. 
 *
 *          Maintaining proper alignment is the user's responsibility.
 */
typedef int8_t          cl_char2[2]     __attribute__((aligned(2)));
typedef int8_t          cl_char4[4]     __attribute__((aligned(4)));
typedef int8_t          cl_char8[8]     __attribute__((aligned(8)));
typedef int8_t          cl_char16[16]   __attribute__((aligned(16)));
typedef uint8_t         cl_uchar2[2]    __attribute__((aligned(2)));
typedef uint8_t         cl_uchar4[4]    __attribute__((aligned(4)));
typedef uint8_t         cl_uchar8[8]    __attribute__((aligned(8)));
typedef uint8_t         cl_uchar16[16]  __attribute__((aligned(16)));

typedef int16_t         cl_short2[2]     __attribute__((aligned(4)));
typedef int16_t         cl_short4[4]     __attribute__((aligned(8)));
typedef int16_t         cl_short8[8]     __attribute__((aligned(16)));
typedef int16_t         cl_short16[16]   __attribute__((aligned(32)));
typedef uint16_t        cl_ushort2[2]    __attribute__((aligned(4)));
typedef uint16_t        cl_ushort4[4]    __attribute__((aligned(8)));
typedef uint16_t        cl_ushort8[8]    __attribute__((aligned(16)));
typedef uint16_t        cl_ushort16[16]  __attribute__((aligned(32)));

typedef int32_t         cl_int2[2]      __attribute__((aligned(8)));
typedef int32_t         cl_int4[4]      __attribute__((aligned(16)));
typedef int32_t         cl_int8[8]      __attribute__((aligned(32)));
typedef int32_t         cl_int16[16]    __attribute__((aligned(64)));
typedef uint32_t        cl_uint2[2]     __attribute__((aligned(8)));
typedef uint32_t        cl_uint4[4]     __attribute__((aligned(16)));
typedef uint32_t        cl_uint8[8]     __attribute__((aligned(32)));
typedef uint32_t        cl_uint16[16]   __attribute__((aligned(64)));

typedef int64_t         cl_long2[2]     __attribute__((aligned(16)));
typedef int64_t         cl_long4[4]     __attribute__((aligned(32)));
typedef int64_t         cl_long8[8]     __attribute__((aligned(64)));
typedef int64_t         cl_long16[16]   __attribute__((aligned(128)));
typedef uint64_t        cl_ulong2[2]    __attribute__((aligned(16)));
typedef uint64_t        cl_ulong4[4]    __attribute__((aligned(32)));
typedef uint64_t        cl_ulong8[8]    __attribute__((aligned(64)));
typedef uint64_t        cl_ulong16[16]  __attribute__((aligned(128)));

typedef float           cl_float2[2]    __attribute__((aligned(8)));
typedef float           cl_float4[4]    __attribute__((aligned(16)));
typedef float           cl_float8[8]    __attribute__((aligned(32)));
typedef float           cl_float16[16]  __attribute__((aligned(64)));

typedef double          cl_double2[2]   __attribute__((aligned(16)));
typedef double          cl_double4[4]   __attribute__((aligned(32)));
typedef double          cl_double8[8]   __attribute__((aligned(64)));
typedef double          cl_double16[16] __attribute__((aligned(128)));
