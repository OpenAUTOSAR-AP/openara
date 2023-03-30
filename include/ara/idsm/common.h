/**
 * @file common.h
 * @author vin (vin@misday.com)
 * @brief
 * @version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) OpenAUTOSAR-AP 2023
 */

// R22-11

#pragma once

#include <cstdint>

namespace ara
{
namespace idsm
{

// SWS_AIDSM_10201
/**
 * @brief ContextDataType used for sending context data to the IdsM
 */
using ContextDataType = ara::core::Span<std::uint8_t>;

// SWS_AIDSM_10202
/**
 * @brief TimestampType used for setting optional sensor-specific timestamp for events.
 * @note Only 62 least-significant bits are used as timestamp value and stored or transmitted, respectively
 */
using TimestampType = std::uint64_t;

// SWS_AIDSM_10203
/**
 * @brief CountType used for setting optional count for events pre-qualified by sensors .
 */
using CountType = std::uint16_t;

} // namespace idsm
} // namespace ara
