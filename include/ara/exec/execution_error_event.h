/**
 * @file execution_error_event.h
 * @author vin (vin@misday.com)
 * @brief
 * @version 0.1
 * @date 2023-03-31
 *
 * @copyright Copyright (c) OpenAUTOSAR-AP 2023
 *
 */

// R22-11

#pragma once

#include <cstdint>

namespace ara
{
namespace exec
{
// SWS_EM_02541
/**
 * @brief Represents the execution error.
 */
using ExecutionError = std::uint32_t;

// SWS_EM_02544
/**
 * @brief Represents an execution error event which happens in a Function Group.
 */
struct ExecutionErrorEvent final
{
   // SWS_EM_02545
   ExecutionError executionError; ///< The execution error of the Process which unexpectedly terminated

   // SWS_EM_02546
   FunctionGroup functionGroup; ///< The function group in which the error occurred
};

} // namespace exec
} // namespace ara
