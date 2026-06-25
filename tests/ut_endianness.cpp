#include <embetech/endianness.h>
#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>

// ---- ENDIANNESS_Reverse ----------------------------------------------------

TEST(ENDIANNESS_Reverse, SingleByte) {
  uint8_t const src = 0xABU;
  uint8_t       dst = 0x00U;
  ENDIANNESS_Reverse(&dst, &src, 1U);
  EXPECT_EQ(dst, 0xABU);
}

TEST(ENDIANNESS_Reverse, FourBytes) {
  uint8_t const src[4] = {0x01U, 0x02U, 0x03U, 0x04U};
  uint8_t       dst[4] = {};
  ENDIANNESS_Reverse(dst, src, sizeof(src));
  EXPECT_EQ(dst[0], 0x04U);
  EXPECT_EQ(dst[1], 0x03U);
  EXPECT_EQ(dst[2], 0x02U);
  EXPECT_EQ(dst[3], 0x01U);
}

TEST(ENDIANNESS_Reverse, SelfInverting) {
  uint8_t const original[4] = {0x11U, 0x22U, 0x33U, 0x44U};
  uint8_t       tmp[4]      = {};
  uint8_t       result[4]   = {};
  ENDIANNESS_Reverse(tmp, original, sizeof(original));
  ENDIANNESS_Reverse(result, tmp, sizeof(tmp));
  EXPECT_EQ(std::memcmp(result, original, sizeof(original)), 0);
}

// ---- NativeToBig / BigToNative ---------------------------------------------
// These tests are host-endian-independent: the byte layout in the output buffer
// is checked against the expected big-endian representation of the value.

TEST(ENDIANNESS_NativeToBig, FourBytes) {
  uint32_t const value = 0x01020304U;
  uint8_t        out[4]{};
  ENDIANNESS_NativeToBig(out, &value, sizeof(value));
  EXPECT_EQ(out[0], 0x01U);
  EXPECT_EQ(out[1], 0x02U);
  EXPECT_EQ(out[2], 0x03U);
  EXPECT_EQ(out[3], 0x04U);
}

TEST(ENDIANNESS_BigToNative, FourBytes) {
  uint8_t const big[4] = {0x01U, 0x02U, 0x03U, 0x04U};
  uint32_t      value{};
  ENDIANNESS_BigToNative(&value, big, sizeof(value));
  EXPECT_EQ(value, 0x01020304U);
}

TEST(ENDIANNESS_BigToNative, RoundTripWithNativeToBig) {
  uint32_t const original = 0xDEADBEEFU;
  uint8_t        buf[4]{};
  uint32_t       result{};
  ENDIANNESS_NativeToBig(buf, &original, sizeof(original));
  ENDIANNESS_BigToNative(&result, buf, sizeof(result));
  EXPECT_EQ(result, original);
}

// ---- NativeToLittle / LittleToNative ---------------------------------------

TEST(ENDIANNESS_NativeToLittle, FourBytes) {
  uint32_t const value = 0x01020304U;
  uint8_t        out[4]{};
  ENDIANNESS_NativeToLittle(out, &value, sizeof(value));
  EXPECT_EQ(out[0], 0x04U);
  EXPECT_EQ(out[1], 0x03U);
  EXPECT_EQ(out[2], 0x02U);
  EXPECT_EQ(out[3], 0x01U);
}

TEST(ENDIANNESS_LittleToNative, FourBytes) {
  uint8_t const little[4] = {0x04U, 0x03U, 0x02U, 0x01U};
  uint32_t      value{};
  ENDIANNESS_LittleToNative(&value, little, sizeof(value));
  EXPECT_EQ(value, 0x01020304U);
}

TEST(ENDIANNESS_LittleToNative, RoundTripWithNativeToLittle) {
  uint32_t const original = 0xDEADBEEFU;
  uint8_t        buf[4]{};
  uint32_t       result{};
  ENDIANNESS_NativeToLittle(buf, &original, sizeof(original));
  ENDIANNESS_LittleToNative(&result, buf, sizeof(result));
  EXPECT_EQ(result, original);
}

// ---- hton / ntoh -----------------------------------------------------------
// Verify that htonN produces network (big-endian) byte order in memory,
// and that ntoh is its exact inverse.

TEST(ENDIANNESS_hton16, NetworkByteOrder) {
  uint16_t const net = ENDIANNESS_hton16(0x0102U);
  uint8_t        bytes[2]{};
  std::memcpy(bytes, &net, sizeof(net));
  EXPECT_EQ(bytes[0], 0x01U);
  EXPECT_EQ(bytes[1], 0x02U);
}

TEST(ENDIANNESS_ntoh16, HostByteOrder) {
  uint8_t  net_bytes[2] = {0x01U, 0x02U};
  uint16_t net{};
  std::memcpy(&net, net_bytes, sizeof(net));
  EXPECT_EQ(ENDIANNESS_ntoh16(net), 0x0102U);
}

TEST(ENDIANNESS_ntoh16, RoundTrip) {
  constexpr uint16_t original = 0x1234U;
  EXPECT_EQ(ENDIANNESS_ntoh16(ENDIANNESS_hton16(original)), original);
}

TEST(ENDIANNESS_hton32, NetworkByteOrder) {
  uint32_t const net = ENDIANNESS_hton32(0x01020304U);
  uint8_t        bytes[4]{};
  std::memcpy(bytes, &net, sizeof(net));
  EXPECT_EQ(bytes[0], 0x01U);
  EXPECT_EQ(bytes[1], 0x02U);
  EXPECT_EQ(bytes[2], 0x03U);
  EXPECT_EQ(bytes[3], 0x04U);
}

TEST(ENDIANNESS_ntoh32, HostByteOrder) {
  uint8_t  net_bytes[4] = {0x01U, 0x02U, 0x03U, 0x04U};
  uint32_t net{};
  std::memcpy(&net, net_bytes, sizeof(net));
  EXPECT_EQ(ENDIANNESS_ntoh32(net), 0x01020304U);
}

TEST(ENDIANNESS_ntoh32, RoundTrip) {
  constexpr uint32_t original = 0x12345678U;
  EXPECT_EQ(ENDIANNESS_ntoh32(ENDIANNESS_hton32(original)), original);
}

TEST(ENDIANNESS_hton64, NetworkByteOrder) {
  uint64_t const net = ENDIANNESS_hton64(0x0102030405060708ULL);
  uint8_t        bytes[8]{};
  std::memcpy(bytes, &net, sizeof(net));
  EXPECT_EQ(bytes[0], 0x01U);
  EXPECT_EQ(bytes[1], 0x02U);
  EXPECT_EQ(bytes[2], 0x03U);
  EXPECT_EQ(bytes[3], 0x04U);
  EXPECT_EQ(bytes[4], 0x05U);
  EXPECT_EQ(bytes[5], 0x06U);
  EXPECT_EQ(bytes[6], 0x07U);
  EXPECT_EQ(bytes[7], 0x08U);
}

TEST(ENDIANNESS_ntoh64, HostByteOrder) {
  uint8_t  net_bytes[8] = {0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U};
  uint64_t net{};
  std::memcpy(&net, net_bytes, sizeof(net));
  EXPECT_EQ(ENDIANNESS_ntoh64(net), 0x0102030405060708ULL);
}

TEST(ENDIANNESS_ntoh64, RoundTrip) {
  constexpr uint64_t original = 0x123456789ABCDEF0ULL;
  EXPECT_EQ(ENDIANNESS_ntoh64(ENDIANNESS_hton64(original)), original);
}
