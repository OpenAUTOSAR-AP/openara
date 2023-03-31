/**
 * \file exec_error_domain.h
 * \author vin (vin@misday.com)
 * \brief
 * \version 0.1
 * \date 2020-12-02
 *
 * \copyright Copyright (c) OpenAUTOSAR-AP 2023
 *
 */

// R22-11

#pragma once

#include "ara/core/error_domain.h"

namespace ara
{
namespace exec
{
// SWS_EM_02281
/**
 * \brief Defines an enumeration class for the Execution Management error codes.
 */
enum class ExecErrc : ara::core::ErrorDomain::CodeType
{
   kGeneralError       = 1, ///< Some unspecified error occurred
   kCommunicationError = 3, ///< Communication error occurred
   kMetaModelError     = 4, ///< Wrong meta model identifier passed to a function
   kCancelled          = 5, ///< Transition to the requested Function Group state was cancelled by a newer request
   kFailed             = 6, ///< Requested operation could not be performed
   kFailedUnexpectedTerminationOnEnter =
      8, ///< Unexpected Termination during transition in Process of target Function Group State happened
   kInvalidTransition = 9, ///< Transition invalid (e.g. report kRunning when already in Running Process State)
   kAlreadyInState =
      10, ///< Transition to the requested Function Group state failed because it is already in requested state
   kInTransitionToSameState = 11, ///< Transition to the requested Function Group state failed because transition to
                                  ///< requested state is already in progress
   kNoTimeStamp  = 12,            ///< DeterministicClient time stamp information is not available
   kCycleOverrun = 13,            ///< Deterministic activation cycle time exceeded
   kIntegrityOrAuthenticityCheckFailed =
      14, ///< Integrity or authenticity check for a Process to be spawned in the requested Function Group state failed
};

// SWS_EM_02282
/**
 * \brief Defines a class for exceptions to be thrown by the Execution Management.
 */
class ExecException: public ara::core::Exception
{
   // SWS_EM_02283
   /**
    * \brief Constructs a new ExecException object containing an error code.
    *
    * \param[in] errorCode     The error code.
    */
   explicit ExecException(ara::core::ErrorCode errorCode) noexcept;
};

// SWS_EM_02290
/**
 * \brief Returns a reference to the global ExecErrorDomain object.
 *
 * \return ara::core::ErrorDomain const&    Return a reference to the global ExecErrorDomain object.
 */
const ara::core::ErrorDomain& GetExecErrorDomain() noexcept;

// SWS_EM_02291
/**
 * \brief Creates an instance of ErrorCode.
 *
 * \param[in] code  Error code number.
 * \param[in] data  Vendor defined data associated with the error.
 *
 * \return ara::core::ErrorCode     An ErrorCode object.
 */
ara::core::ErrorCode MakeErrorCode(ExecErrc code, ara::core::ErrorDomain::SupportDataType data) noexcept;

// SWS_EM_02284
/**
 * \brief Defines a class representing the Execution Management error domain.
 *
 * Unique ID: 0x8000’0000’0000’0202
 */
class ExecErrorDomain final: public ara::core::ErrorDomain
{
   // SWS_EM_02286
   /**
    * \brief Constructs a new ExecErrorDomain object
    */
   ExecErrorDomain() noexcept;

   // SWS_EM_02287
   /**
    * \brief Returns a string constant associated with ExecErrorDomain.
    *
    * \return char const*  The name of the error domain.
    */
   const char* Name() const noexcept override;

   // SWS_EM_02288
   /**
    * \brief Returns the message associated with errorCode.
    *
    * \param[in] errorCode     The error code number.
    *
    * \return char const*      The message associated with the error code.
    */
   const char* Message(CodeType errorCode) const noexcept override;

   // SWS_EM_02289
   /**
    * \brief Creates a new instance of ExecException from errorCode and throws it as a C++ exception.
    *
    * \param[in] errorCode     The error to throw.
    */
   void ThrowAsException(const ara::core::ErrorCode& errorCode) const noexcept(false) override;
};
} // namespace exec
} // namespace ara
