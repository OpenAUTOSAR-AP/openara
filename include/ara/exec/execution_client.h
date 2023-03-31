/**
 * \file execution_client.h
 * \author vin (vin@misday.com)
 * \brief
 * \version 0.1
 * \date 2020-12-04
 *
 * \copyright Copyright (c) OpenAUTOSAR-AP 2023
 *
 */

// Base on the AUTOSAR_SWS_ExecutionManagement.pdf
// R22-11

#pragma once

#include "ara/core/result.h"

namespace ara
{
namespace exec
{
// SWS_EM_02000
/**
 * Defines the internal states of a Process (see 7.3.1). Scoped Enumeration of uint8_t .
 */
enum class ExecutionState : uint8_t
{
   kRunning = 0, /* After a Process has been started by Execution Management, it reports ExecutionState kRunning. */
};

// SWS_EM_02001
/**
 * \brief Class to implement operations on Execution Client.
 */
class ExecutionClient final
{
   // SWS_EM_02030
   /**
    * @brief Constructor for ExecutionClient which opens the Execution Management communication channel (e.g. POSIX
    * FIFO) for reporting the Execution State. Each Process shall create an instance of this class to report its state
    */
   ExecutionClient() noexcept;

   // SWS_EM_02002
   /**
    * @brief Destructor of the Execution Client instance .
    */
   ~ExecutionClient() noexcept;

   // SWS_EM_02003
   /**
    * Interface for a Process to report its internal state to Execution Management.
    *
    * \param[in] state Value of the Execution State
    *
    * \return          An instance of ara::core::Result. The instance holds
    *                  an ErrorCode containing either one of the specified
    *                  errors or a void-value.
    */
   ara::core::Result<void> ReportExecutionState(ExecutionState state) const noexcept;
};
} // namespace exec
} // namespace ara
