/**
 * @file timestamp_provider.h
 * @author vin (vin@misday.com)
 * @brief
 * @version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) OpenAUTOSAR-AP 2023
 */

// R22-11

#pragma once

#include <functional>

namespace ara
{
namespace idsm
{
// SWS_AIDSM_20101
/**
 * @brief Register a callback for providing timestamps to the IdsM .
 *
 * @param callback std::function callback that provides a timestamp to the IdsM
 */
void RegisterTimestampProvider(std::function<Timestamp Type()> callback);
} // namespace idsm
} // namespace ara