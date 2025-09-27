/**
 * @file
 * @license   ${PROJECT_LICENSE}
 * @copyright ${PROJECT_COPYRIGHT}
 * @version   ${PROJECT_VERSION}
 * @purpose   Embeutils library
 * @brief     A set of tools for working with compiler-specific attributes
 *
 * This header provides portable macros for compiler-specific attributes such
 * as:
 * - EMBEUTILS_PACKED: Structure packing (no padding)
 * - EMBEUTILS_NORETURN: Function does not return
 * - EMBEUTILS_WEAK: Weak symbol
 * - EMBEUTILS_NODISCARD: Warn if return value is unused
 * - EMBEUTILS_FALLTHROUGH: Intentional fallthrough in switch
 * - EMBEUTILS_INLINE: Always inline
 * - EMBEUTILS_RESTRICT: Restrict pointer
 * - EMBEUTILS_UNUSED: Mark argument as unused
 * - EMBEUTILS_NONNULL: Warn if argument is null
 * - EMBEUTILS_STATIC_ASSERT: Compile-time assertion
 * - EMBEUTILS_ALIGNAS: Alignment attribute
 * - EMBEUTILS_ALIGNOF: Alignment query
 */

#ifndef EMBEUTILS_COMPILER_SUPPORT_H_
#define EMBEUTILS_COMPILER_SUPPORT_H_

#if (__STDC_VERSION__ >= 202311L) || (__cplusplus >= 201103L)
#include <assert.h>
#include <stdalign.h>
#endif

// ===================== COMPILER DETECTION =====================
#if defined(__cplusplus) && (__cpp_attributes >= 200809L)
#define EMBEUTILS_HAS_STANDARD_ATTRIBUTE(attribute) __has_cpp_attribute(attribute)
#elif __STDC_VERSION__ >= 202311L
#define EMBEUTILS_HAS_STANDARD_ATTRIBUTE(attribute) __has_c_attribute(attribute)
#else
#define EMBEUTILS_HAS_STANDARD_ATTRIBUTE(attribute) 0
#endif

#if defined(__clang__)
#define EMBEUTILS_COMPILER_CLANG 1
#elif defined(__GNUC__)
#define EMBEUTILS_COMPILER_GCC 1
#elif defined(_MSC_VER)
#define EMBEUTILS_COMPILER_MSVC 1
#elif defined(__IAR_SYSTEMS_ICC__)
#define EMBEUTILS_COMPILER_IAR 1
#elif defined(__CC_ARM) || defined(__ARMCC_VERSION)
#define EMBEUTILS_COMPILER_KEIL 1
#endif

/**
 * @def EMBEUTILS_PACKED
 * Forces compiler to produce structure without padding (sizeof(structure) equals sum of sizeof(structure fields)).
 *
 * @note For MSVC use only with __declspec(align(1)) before struct, not for individual fields.
 */
#if (1 == EMBEUTILS_COMPILER_GCC) || (1 == EMBEUTILS_COMPILER_CLANG)
#define EMBEUTILS_PACKED __attribute__((packed))
#elif (1 == EMBEUTILS_COMPILER_MSVC)
#define EMBEUTILS_PACKED __declspec(align(1))
#elif (1 == EMBEUTILS_COMPILER_KEIL)
#define EMBEUTILS_PACKED __packed
#elif (1 == EMBEUTILS_COMPILER_IAR)
#define EMBEUTILS_PACKED __packed
#else
#define EMBEUTILS_PACKED
#endif

/**
 * @def EMBEUTILS_WEAK
 * Informs compiler that the symbol MUST be emitted as weak symbol.
 */
#if defined(EMBEUTILS_COMPILER_GCC) || defined(EMBEUTILS_COMPILER_CLANG)
#define EMBEUTILS_WEAK __attribute__((weak))
#elif defined(EMBEUTILS_COMPILER_MSVC)
#define EMBEUTILS_WEAK __declspec(selectany)
#elif defined(EMBEUTILS_COMPILER_IAR) || defined(EMBEUTILS_COMPILER_KEIL)
#define EMBEUTILS_WEAK __weak
#else
#define EMBEUTILS_WEAK
#endif

/**
 * @def EMBEUTILS_NORETURN
 * Informs compiler that the function may not return (i.e. has infinite loop, or throws).
 */
#if EMBEUTILS_HAS_STANDARD_ATTRIBUTE(noreturn)
#define EMBEUTILS_NORETURN [[noreturn]]
#elif defined(EMBEUTILS_COMPILER_GCC) || defined(EMBEUTILS_COMPILER_CLANG)
#define EMBEUTILS_NORETURN __attribute__((noreturn))
#elif defined(EMBEUTILS_COMPILER_MSVC)
#define EMBEUTILS_NORETURN __declspec(noreturn)
#elif defined(EMBEUTILS_COMPILER_IAR)
#define EMBEUTILS_NORETURN __attribute__((noreturn))
#elif defined(EMBEUTILS_COMPILER_KEIL)
#define EMBEUTILS_NORETURN
#else
#define EMBEUTILS_NORETURN
#endif

/**
 * @def EMBEUTILS_NODISCARD
 * Warns if the return value of the function is not used.
 */
#if EMBEUTILS_HAS_STANDARD_ATTRIBUTE(nodiscard)
#define EMBEUTILS_NODISCARD [[nodiscard]]
#elif defined(EMBEUTILS_COMPILER_GCC) || defined(EMBEUTILS_COMPILER_CLANG)
#define EMBEUTILS_NODISCARD __attribute__((warn_unused_result))
#elif defined(EMBEUTILS_COMPILER_MSVC)
#define EMBEUTILS_NODISCARD _Check_return_
#else
#define EMBEUTILS_NODISCARD
#endif

/**
 * @def EMBEUTILS_FALLTHROUGH
 * Indicates that the fall through from the previous case label is intentional and should not be diagnosed by a compiler that warns on fallthrough.
 */
#if EMBEUTILS_HAS_STANDARD_ATTRIBUTE(fallthrough)
#define EMBEUTILS_FALLTHROUGH [[fallthrough]]
#elif defined(EMBEUTILS_COMPILER_GCC) || defined(EMBEUTILS_COMPILER_CLANG)
#define EMBEUTILS_FALLTHROUGH __attribute__((fallthrough))
#else
#define EMBEUTILS_FALLTHROUGH
#endif

/**
 * @def EMBEUTILS_INLINE
 * Always inline function.
 */
#if (__STDC_VERSION__ >= 202311L)
#define EMBEUTILS_INLINE [[gnu::always_inline]]
#elif defined(EMBEUTILS_COMPILER_GCC) || defined(EMBEUTILS_COMPILER_CLANG)
#define EMBEUTILS_INLINE __attribute__((always_inline))
#elif defined(EMBEUTILS_COMPILER_MSVC)
#define EMBEUTILS_INLINE __forceinline
#elif defined(EMBEUTILS_COMPILER_KEIL)
#define EMBEUTILS_INLINE __inline
#elif defined(EMBEUTILS_COMPILER_IAR)
#define EMBEUTILS_INLINE __intrinsic
#else
#define EMBEUTILS_INLINE
#endif

/**
 * @def EMBEUTILS_RESTRICT
 * Provides portable mean of using C99 restrict keyword.
 */
#ifdef __cplusplus
#define EMBEUTILS_RESTRICT __restrict
#elif __STDC_VERSION_ >= 199901L
#define EMBEUTILS_RESTRICT restrict
#else
#define EMBEUTILS_RESTRICT
#endif

/**
 * @def EMBEUTILS_UNUSED(x)
 * Informs compiler that the argument is unused.
 *
 * @param[in] x name of the argument to be marked as unused.
 * Usage: void function(int arg1, int EMBEUTILS_UNUSED(arg2)) { ... }
 */
#if EMBEUTILS_HAS_STANDARD_ATTRIBUTE(maybe_unused)
#define EMBEUTILS_UNUSED(x) x [[maybe_unused]]
#elif defined(EMBEUTILS_COMPILER_GCC) || defined(EMBEUTILS_COMPILER_CLANG)
#define EMBEUTILS_UNUSED(x) x __attribute__((unused))
#elif defined(EMBEUTILS_COMPILER_MSVC)
#define EMBEUTILS_UNUSED(x) __pragma(warning(suppress : 4100 4101)) x
#else
#define EMBEUTILS_UNUSED(x) x
#endif

/**
 * @def EMBEUTILS_NONNULL(...)
 * Warns when nullptr is provided as argument on given position.
 *
 * @param[in] ... list of arguments indices to be checked against nullptr. When no argument is provided, ALL of the pointer arguments are marked as
 * non-null.
 *
 * Usage:
 * - void func1(void* dst, void* src) EMBEUTILS_NONNULL() - both dst and src MUST NOT take nullptr. void func2(void* dst, void* src)
 * - void func2(void* dst, void* src) EMBEUTILS_NONNULL(2) - dst may be nullptr
 *
 * @note GNU/Clang compiler checks this only with -Wnonnull flag (which is included in -Wall).
 */
#if EMBEUTILS_HAS_STANDARD_ATTRIBUTE(gnu::nonnull)
#define EMBEUTILS_NONNULL(...) [[gnu::nonnull(__VA_ARGS__)]]
#elif defined(EMBEUTILS_COMPILER_GCC) || defined(EMBEUTILS_COMPILER_CLANG)
#define EMBEUTILS_NONNULL(...) __attribute__((nonnull(__VA_ARGS__)))
#else
#define EMBEUTILS_NONNULL(...)
#endif

/**
 * @def EMBEUTILS_STATIC_ASSERT(...)
 * Compile-time assertion.
 */
#if !defined(EMBEUTILS_STATIC_ASSERT)
#if (__STDC_VERSION__ >= 202311L) || (__cplusplus >= 201103L)
#define EMBEUTILS_STATIC_ASSERT(...) static_assert(__VA_ARGS__)
#elif (__STDC_VERSION__ >= 201112L) || defined(EMBEUTILS_COMPILER_GCC) || defined(EMBEUTILS_COMPILER_CLANG)
#define EMBEUTILS_STATIC_ASSERT(...) _Static_assert(__VA_ARGS__)
#elif defined(EMBEUTILS_COMPILER_MSVC)
#define EMBEUTILS_STATIC_ASSERT(...) __pragma(warning(suppress : 4127)) static_assert(__VA_ARGS__)
#elif defined(EMBEUTILS_COMPILER_KEIL) || defined(EMBEUTILS_COMPILER_IAR)
#define EMBEUTILS_STATIC_ASSERT(...) static_assert(__VA_ARGS__)
#else
#define EMBEUTILS_STATIC_ASSERT(...) struct EMBEUTILS_static_assert_inactive
#endif
#endif

/**
 * @def EMBEUTILS_ALIGNAS(x)
 * Alignment attribute for the structure.
 */
#if !defined(EMBEUTILS_ALIGNAS)
#if (__STDC_VERSION__ >= 202311L) || (__cplusplus >= 201103L)
#define EMBEUTILS_ALIGNAS(x) alignas(x)
#elif __STDC_VERSION__ >= 201112L
#define EMBEUTILS_ALIGNAS(x) _Alignas(x)
#elif defined(EMBEUTILS_COMPILER_GCC) || defined(EMBEUTILS_COMPILER_CLANG)
#define EMBEUTILS_ALIGNAS(x) __attribute__((aligned(x)))
#elif defined(EMBEUTILS_COMPILER_MSVC)
#define EMBEUTILS_ALIGNAS(x) __declspec(align(x))
#elif defined(EMBEUTILS_COMPILER_KEIL)
#define EMBEUTILS_ALIGNAS(x) __align(x)
#elif defined(EMBEUTILS_COMPILER_IAR)
#define EMBEUTILS_ALIGNAS(x) __attribute__((aligned(x)))
#else
#define EMBEUTILS_ALIGNAS(x)
#endif
#endif

/**
 * @def EMBEUTILS_ALIGNOF(x)
 * Alignment query for the structure.
 */
#if !defined(EMBEUTILS_ALIGNOF)
#if (__STDC_VERSION__ >= 202311L) || (__cplusplus >= 201103L)
#define EMBEUTILS_ALIGNOF(x) alignof(x)
#elif __STDC_VERSION__ >= 201112L
#define EMBEUTILS_ALIGNOF(x) _Alignof(x)
#elif defined(EMBEUTILS_COMPILER_GCC) || defined(EMBEUTILS_COMPILER_CLANG)
#define EMBEUTILS_ALIGNOF(x) __alignof__(x)
#elif defined(EMBEUTILS_COMPILER_MSVC)
#define EMBEUTILS_ALIGNOF(x) __alignof(x)
#elif defined(EMBEUTILS_COMPILER_KEIL)
#define EMBEUTILS_ALIGNOF(x) __alignof(x)
#elif defined(EMBEUTILS_COMPILER_IAR)
#define EMBEUTILS_ALIGNOF(x) __alignof__(x)
#else
#define EMBEUTILS_ALIGNOF(x)
#endif
#endif

#endif // EMBEUTILS_COMPILER_SUPPORT_H_
