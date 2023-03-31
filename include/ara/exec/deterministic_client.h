/**
 * \file deterministic_client.h
 * \author vin (vin@misday.com)
 * \brief
 * \version 0.1
 * \date 2020-12-04
 *
 * \copyright Copyright (c) OpenAUTOSAR-AP 2023
 *
 */

// Base on the AUTOSAR_SWS_ExecutionManagement.pdf
// AUTOSAR AP R19-11

#pragma once

#include "ara/core/result.h"

namespace ara
{
namespace exec
{
// SWS_EM_02201
/**
 * @brief Defines the return codes for WaitForActivation operations. Scoped Enumeration of uint32_t .
 */
enum class ActivationReturnType : std::uint32_t
{
   kRegisterServices = 0, ///< application shall register communication services(this must be the only occasion for
                          ///< performing service registering)
   kServiceDiscovery = 1, ///< application shall do communication service discovery (this must be the only occasion for
                          ///< performing service discovery)
   kInit      = 2,        ///< application shall initialize its internal data structures (once)
   kRun       = 3,        ///< application shall perform its normal operation
   kTerminate = 4,        ///< deterministic execution shall terminate
};

// SWS_EM_02202
/**
 * Defines the return codes for "get activation timestamp" operations. Scoped Enumeration of uint8_t .
 */
enum class ActivationTimeStampReturnType : uint8_t
{
   kSuccess      = 0,
   kNotAvailable = 1,
};

// SWS_EM_02210
/**
 * Class to implement operations on Deterministic Client .
 */
class DeterministicClient final
{
   // SWS_EM_02203
   /**
    * @brief Time stamp of deterministic cycles .
    */
   using TimeStamp = std::chrono::time_ point<ara::core::SteadyClock>;

   // SWS_EM_02211
   /**
    * @brief Constructor for DeterministicClient which opens the Execution Management communication channel (e.g. POSIX
    * FIFO) to access a wait point for cyclic execution, a worker pool, deterministic random numbers and time stamps .
    */
   DeterministicClient() noexcept;

   // SWS_EM_02215
   /**
    * @brief Destructor of the Deterministic Client instance .
    */
   ~DeterministicClient() noexcept;

   // SWS_EM_02217
   /**
    * @brief Blocks and returns with a process control value when the next activation is triggered by the Runtime .
    *
    * @return ara::core::Result<ActivationReturnType> Process control value (or error) In the absence of an error, the
    * return value contains the activation state defined by ara::exec::ActivationReturnType.
    */
   ara::core::Result<ActivationReturnType> WaitForActivation() noexcept;

   // SWS_EM_02221
   /**
    * @brief Run a deterministic worker pool.
    *
    * Uses a pool of Deterministic workers to call a method WorkerRunnable::Run for every element of the container. The
    * sequential iteration is guaranteed by using the container’s increment operator. The API provides the guarantee
    * that no other iteration scheme is used.
    *
    * This function shall not participate in overload resolution unless ValueType is compatible with
    * Container::value_type.
    *
    * @tparam ValueType Element type of container
    * @tparam Container Container for which method WorkerRunnable::Run is invoked for each element
    * @param[in] runnableObj Object derived from WorkerRunnable that provides a method called Run(...), which will be
    * called on every container element
    * @param[in] container C++ container which supports a standard iterator interface with - begin() - end() -
    * operator*() operator++
    * @return ara::core::Result<void>
    */
   template <typename ValueType, typename Container>
   ara::core::Result<void> RunWorkerPool(WorkerRunnable<ValueType>& runnableObj, Container& container) noexcept;

   // SWS_EM_02225
   /**
    * @brief Return deterministic sequence of random numbers.
    *
    * This returns the next in a sequence of ‘Deterministic’ random numbers. Deterministic’ means, that the returned
    * random numbers are identical within redundant DeterministicClient::WaitFor Activation() cycles, which are used
    * within redundantly executed Processes.
    *
    * @return std::uint64_t uint64_t 64 bit uniform distributed pseudo random number
    */
   std::uint64_t GetRandom() const noexcept;

   // SWS_EM_02226
   /**
    * @brief Seed random number generator used for redundantly executed deterministic clients.
    *
    * @param[in] seed Random number seed to DeterministicClient::Set RandomSeed.
    */
   void SetRandomSeed(std::uint64_t seed) noexcept;

   // SWS_EM_02231
   /**
    * @brief TimeStamp of activation point.
    *
    * This method provides the timestamp that represents the point in time when the activation was triggered by
    * DeterministicClient::WaitForActivation() with return value kRun. Subsequent calls within an activation cycle will
    * always provide the same value. The same value will also be provided within redundantly executed Processes
    *
    * @return ara::core::Result<TimeStamp> TimeStamp of current activation cycle
    */
   ara::core::Result<TimeStamp> GetActivationTime() noexcept;

   // SWS_EM_02236
   /**
    * @brief Timestamp of next activation point.
    *
    * This method provides the timestamp that represents the point in time when the next activation will be triggered by
    * DeterministicClient::WaitForActivation() with return value kRun. Subsequent calls within an activation cycle will
    * always provide the same value. The same value will also be provided within redundantly executed Process
    *
    * @return ara::core::Result<TimeStamp> TimeStamp of next activation cycle
    */
   ara::core::Result<TimeStamp> GetNextActivationTime() noexcept;
};
} // namespace exec
} // namespace ara
