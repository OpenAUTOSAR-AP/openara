/**
 * @file worker_thread.h
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
// SWS_EM_02530
/**
 * @brief Class to implement worker thread for Deterministic Client .
 */
class WorkerThread
{
   // SWS_EM_02531
   /**
    * @brief Constructor
    */
   WorkerThread();

   // SWS_EM_02532
   /**
    * @brief Destructor
    */
   virtual ~WorkerThread() noexcept;

   // SWS_EM_02540
   /**
    * @brief Returns a deterministic pseudo-random number which is unique for each container element.
    *
    * @return std::uint64_t Deterministic random number
    */
   std::uint64_t GetRandom() noexcept;
};
} // namespace exec
} // namespace ara
