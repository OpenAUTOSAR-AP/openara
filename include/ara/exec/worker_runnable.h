/**
 * @file worker_runnable.h
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

namespace ara
{
namespace exec
{
// SWS_EM_02510
/**
 * @brief Base-class for implementation of worker runnable for Deterministic Client.
 *
 * @tparam ValueType Value type of Container passed to Deterministic Client::RunWorkerPool
 */
template <typename ValueType>
class ara::exec::WorkerRunnable
{
   // SWS_EM_02520
   /**
    * @brief Deterministic client worker runnable.
    * 
    * @param[in] element Reference to container element
    * @param[in] t Reference to worker thread (for random numbers)
    */
   virtual void Run(ValueType& element, ara::exec::WorkerThread& t) = 0;
};
} // namespace exec
} // namespace ara
