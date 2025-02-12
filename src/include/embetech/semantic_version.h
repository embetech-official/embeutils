/**
 * @file
 * @license   ${PROJECT_LICENSE}
 * @copyright ${PROJECT_COPYRIGHT}
 * @version   ${PROJECT_VERSION}
 * @purpose   Embeutils library
 * @brief     A set of simple utilities to manage error handling in a unified way
 */

#ifndef EMBEUTILS_SEMANTIC_VERSION_H_
#define EMBEUTILS_SEMANTIC_VERSION_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SemanticVersion {
  uint8_t major;
  uint8_t minor;
  uint16_t patch;
  uint32_t id;
} SemanticVersion;

/**
 * Compares two semantic version strings and returns the result
 *
 * @param lhs left hand side of the comparison
 * @param rhs right hand side of the comparison
 * @return 1 if lhs > rhs
 * @return 0 if lhs == rhs
 * @return -1 if lhs < rhs
 *
 * @note the id field is ignored in the comparison
 */
static inline int SEMVER_Compare(SemanticVersion lhs, SemanticVersion rhs);

/**
 * Compares two semantic version strings and returns true if lhs is newer than rhs
 *
 * @param lhs left hand side of the comparison
 * @param rhs right hand side of the comparison
 * @return true if lhs > rhs
 */
static inline bool SEMVER_IsNewer(SemanticVersion lhs, SemanticVersion rhs);

// Inline implementation below
static inline int SEMVER_Compare(SemanticVersion lhs, SemanticVersion rhs) {

  if(lhs.major != rhs.major) {
    return (lhs.major > rhs.major) ? 1 : -1;
  }

  if(lhs.minor != rhs.minor) {
    return lhs.minor > rhs.minor ? 1 : -1;
  }

  if(lhs.patch != rhs.patch) {
    return lhs.patch > rhs.patch ? 1 : -1;
  }

  return 0;
}

static inline bool SEMVER_IsNewer(SemanticVersion lhs, SemanticVersion rhs) { return SEMVER_Compare(lhs, rhs) > 0; }

#ifdef __cplusplus
}
#endif

#endif
