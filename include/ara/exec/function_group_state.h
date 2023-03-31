/**
 * @file function_group_state.h
 * @author vin (vin@misday.com)
 * @brief
 * @version 0.1
 * @date 2023-03-31
 *
 * @copyright Copyright (c) OpenAUTOSAR-AP 2023
 */

// R22-11

#pragma once

#include "ara/core/result.h"

namespace ara
{
namespace exec
{
// SWS_EM_02269
/**
 * @brief Class representing Function Group State defined in meta-model (ARXML).
 *
 * @note Once created based on ARXML path, it’s internal value stay bounded to it for entire lifetime of an object.
 */
class ara::exec::FunctionGroupState final
{
   // SWS_EM_02326
   /**
    * @brief Named constructor for FunctionGroupState.
    *
    * This method shall validate/verify meta-model path passed and perform FunctionGroupState object creation.
    *
    * @param[in] functionGroup the FunctionGroup instance the state shall be connected with.
    * @param[in] metaModelIdentifier stringified meta model identifier (short name path) where path separator is ’/’.
    * @return ara::core::Result<FunctionGroupState> an instance of FunctionGroupState, or ExecError Domain error.
    */
   static ara::core::Result<FunctionGroupState> Create(const FunctionGroup& functionGroup,
                                                       ara::core::String View metaModelIdentifier) noexcept;

   // SWS_EM_02324
   /**
    * @brief Default constructor.
    *
    * @note Default constructor is deleted in favour of named constructor (Create).
    */
   FunctionGroupState() = delete;

   // SWS_EM_02325
   /**
    * @brief Copy constructor.
    *
    * @note To prevent problems with resource allocations during copy operation, this class is non-copyable.
    */
   FunctionGroupState(const FunctionGroup State& other) = delete;

   // SWS_EM_02331
   /**
    * @brief Move constructor.
    *
    * @param[in] other FunctionGroupState instance to be moved to a newly constructed object.
    */
   FunctionGroupState(FunctionGroupState&& other) noexcept;

   // SWS_EM_02330
   /**
    * @brief Copy assignment operator.
    *
    * @note To prevent problems with resource allocations during copy operation, this class is non-copyable.
    */
   FunctionGroupState& operator=(const FunctionGroupState& other) = delete;

   // SWS_EM_02332
   /**
    * @brief Move assignment operator.
    *
    * @param[in] other FunctionGroupState instance to move to this object.
    * @return FunctionGroupState&
    */
   FunctionGroupState& operator=(Function GroupState&& other) noexcept;

   // SWS_EM_02272
   /**
    * @brief Destructor of the FunctionGroupState instance.
    */
   ~FunctionGroupState() noexcept;

   // SWS_EM_02273
   /**
    * @brief eq operator to compare with other FunctionGroupState instance.
    *
    * @param[in] other FunctionGroupState instance to compare this one with.
    * @return true in case both FunctionGroupStates are representing exactly the same meta-model element,
    * @return false otherwise
    */
   bool operator==(const FunctionGroup State& other) const noexcept;

   // SWS_EM_02274
   /**
    * @brief uneq operator to compare with other FunctionGroupState instance.
    *
    * @param[in] other FunctionGroupState instance to compare this one with.
    * @return false in case both FunctionGroupStates are representing exactly the same meta-model element, true otherwise.
    */
   bool operator!=(const FunctionGroup State& other) const noexcept;
};
} // namespace exec
} // namespace ara
