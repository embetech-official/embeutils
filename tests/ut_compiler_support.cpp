#include <embetech/compiler_support.h>
#include <gtest/gtest.h>

#include <cstdint>

// ---------- EMBEUTILS_STATIC_ASSERT ----------
EMBEUTILS_STATIC_ASSERT(sizeof(uint8_t) == 1, "uint8_t must be 1 byte");
EMBEUTILS_STATIC_ASSERT(sizeof(uint32_t) == 4, "uint32_t must be 4 bytes");
EMBEUTILS_STATIC_ASSERT(sizeof(uint32_t) >= sizeof(uint8_t));

// ---------- EMBEUTILS_PACK_BEGIN / EMBEUTILS_PACK_END ----------
EMBEUTILS_PACK_BEGIN()
struct PackedStruct {
    uint8_t  a;
    uint32_t b;
    uint8_t  c;
};
EMBEUTILS_PACK_END()

struct UnpackedStruct {
    uint8_t  a;
    uint32_t b;
    uint8_t  c;
};

EMBEUTILS_STATIC_ASSERT(sizeof(PackedStruct) == 6U, "PackedStruct must have no padding");

// ---------- EMBEUTILS_ALIGNAS / EMBEUTILS_ALIGNOF ----------
struct EMBEUTILS_ALIGNAS(16) AlignedStruct {
    uint8_t data[4];  // NOLINT — C-style array intentional for raw alignment test
};

EMBEUTILS_STATIC_ASSERT(EMBEUTILS_ALIGNOF(AlignedStruct) == 16U,
                        "AlignedStruct must be 16-byte aligned");

// EMBEUTILS_WEAK requires external linkage — must stay at file scope, not in anonymous namespace.
EMBEUTILS_WEAK void weak_func() {}

namespace {

// ---------- EMBEUTILS_NORETURN (compile-check only — never called at runtime) ----------
EMBEUTILS_NORETURN void noreturn_func() { for(;;) {} }

// ---------- EMBEUTILS_NODISCARD ----------
EMBEUTILS_NODISCARD int nodiscard_func() { return 42; }

// ---------- EMBEUTILS_INLINE ----------
EMBEUTILS_INLINE inline int always_inline_func(int x) { return x + 1; }

// ---------- EMBEUTILS_NONNULL ----------
void nonnull_func(void *ptr, void *ptr2) EMBEUTILS_NONNULL();
void nonnull_func(void *ptr, void *ptr2) { (void)ptr; (void)ptr2; }

void nonnull_second_func(void *ptr, void *ptr2) EMBEUTILS_NONNULL(2);
void nonnull_second_func(void *ptr, void *ptr2) { (void)ptr; (void)ptr2; }

// ---------- EMBEUTILS_UNUSED ----------
int unused_arg_func(int arg1, int EMBEUTILS_UNUSED(arg2)) { return arg1; }

// ---------- EMBEUTILS_RESTRICT ----------
void restrict_copy(int *EMBEUTILS_RESTRICT dst, const int *EMBEUTILS_RESTRICT src) {
    *dst = *src;
}

// ---------- EMBEUTILS_FALLTHROUGH ----------
int fallthrough_func(int x) {
    int result = 0;
    switch(x) {
        case 0:
            result = 10;
            EMBEUTILS_FALLTHROUGH;
        case 1:
            result += 1;
            break;
        default:
            result = -1;
            break;
    }
    return result;
}

}  // namespace

// ===================== Tests =====================

TEST(CompilerSupport, StaticAssert) {
    SUCCEED(); // reaching here proves EMBEUTILS_STATIC_ASSERT compiled
}

TEST(CompilerSupport, Noreturn) {
    // Compile-check: take the address to prove the attribute was accepted without calling.
    void (*fn)() = noreturn_func;
    (void)fn;
    SUCCEED();
}

TEST(CompilerSupport, PackedSizeof) {
    EXPECT_EQ(sizeof(PackedStruct), 6U);
    EXPECT_GE(sizeof(UnpackedStruct), sizeof(PackedStruct));
}

TEST(CompilerSupport, AlignasAlignof) {
    AlignedStruct s{};
    EXPECT_EQ(reinterpret_cast<uintptr_t>(&s) % 16U, 0U);
    EXPECT_EQ(EMBEUTILS_ALIGNOF(AlignedStruct), 16U);
}

TEST(CompilerSupport, Nodiscard) {
    int val = nodiscard_func();
    EXPECT_EQ(val, 42);
}

TEST(CompilerSupport, AlwaysInline) {
    EXPECT_EQ(always_inline_func(5), 6);
}

TEST(CompilerSupport, UnusedArg) {
    EXPECT_EQ(unused_arg_func(3, 99), 3);
}

TEST(CompilerSupport, Restrict) {
    int a = 7;
    int b = 0;
    restrict_copy(&b, &a);
    EXPECT_EQ(b, 7);
}

TEST(CompilerSupport, Fallthrough) {
    EXPECT_EQ(fallthrough_func(0), 11); // case 0 sets 10, then falls through to += 1
    EXPECT_EQ(fallthrough_func(1), 1);
    EXPECT_EQ(fallthrough_func(2), -1);
}

TEST(CompilerSupport, Nonnull) {
    int x = 0;
    int y = 0;
    nonnull_func(&x, &y);
    nonnull_second_func(nullptr, &y); // only arg2 required non-null
    SUCCEED();
}

TEST(CompilerSupport, Weak) {
    weak_func();
    SUCCEED();
}
