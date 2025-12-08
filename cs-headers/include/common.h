#pragma once

// Unknown function declaration
#define UNKNOWN_FUNCTION(name) void name(void);

// Use extern "C" in C++, use namespacing in mods
#ifdef __cplusplus
    #ifdef DECOMP
        #define CPP_WRAPPER(ns) \
            extern "C" {
        #define CPP_WRAPPER_END() }
    #elif defined RELAX_NAMESPACING
        #define CPP_WRAPPER(ns) \
            namespace ns {} \
            using namespace ns; \
            namespace ns { \
            extern "C" {
        #define CPP_WRAPPER_END() }}
    #else
        #define CPP_WRAPPER(ns) \
            namespace ns { \
            extern "C" {
        #define CPP_WRAPPER_END() }}
    #endif
#else
    #define CPP_WRAPPER(ns)
    #define CPP_WRAPPER_END()
#endif

// Macro for potential using statements
// Should go inside a CPP_WRAPPER
#if (defined __cplusplus) && !(defined DECOMP)
    #define USING(name) using name;
#else
    #define USING(name)
#endif

// Basic types

#define INT_TYPE int

typedef unsigned long long u64;
typedef unsigned INT_TYPE u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef signed long long s64;
typedef signed INT_TYPE s32;
typedef signed short s16;
typedef signed char s8;
typedef signed char Unk;

#undef INT_TYPE

typedef float f32;
typedef double f64;
