/**
 * @file function_group.h
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

#include "ara/core/result.h"

namespace ara
{
namespace exec
{
// SWS_EM_02263
/**
 * @brief Class representing Function Group defined in meta-model (ARXML).
 *
 * @note Once created based on ARXML path, it’s internal value stay bounded to it for entire lifetime of an object.
 *
 */
class FunctionGroup final
{
   // SWS_EM_02323
   /**
    * @brief Named constructor for FunctionGroup.
    *
    * This method shall validate/verify meta-model path passed and perform FunctionGroup object creation.
    *
    * @param[in] metaModelIdentifier stringified meta model identifier (short name path) where path separator is ’/’.
    * @return ara::core::Result<FunctionGroup> an instance of FunctionGroup, or ExecErrc error.
    */
   static ara::core::Result<FunctionGroup> Create(ara::core::StringView metaModelIdentifier) noexcept;

   // SWS_EM_02321
   /**
    * @brief Default constructor.
    *
    * @note Default constructor is deleted in favour of named constructor (Create).
    */
   FunctionGroup() = delete;

   // SWS_EM_02322
   /**
    * @brief Copy constructor.
    *
    * @note To prevent problems with resource allocations during copy operation, this class is non-copyable.
    */
   FunctionGroup(const FunctionGroup& other) = delete;

   // SWS_EM_02328
   /**
    * @brief Move constructor.
    *
    * @param[in] other FunctionGroup instance to move to a newly constructed object.
    */
   FunctionGroup(FunctionGroup&& other) noexcept;

   // SWS_EM_02327
   /**
    * @brief Copy assignment operator.
    *
    * @note To prevent problems with resource allocations during copy operation, this class is non-copyable.
    */
   FunctionGroup& operator=(const Function Group& other) = delete;

   // SWS_EM_02329
   /**
    * @brief Move assignment operator.
    *
    * @param[in] other FunctionGroup instance to move to this object.
    * @return FunctionGroup&
    */
   FunctionGroup& operator=(FunctionGroup&& other) noexcept;

   // SWS_EM_02266
   /**
    * @brief Destructor of the FunctionGroup instance.
    */
   ~FunctionGroup() noexcept;

   // SWS_EM_02267
   /**
    * @brief eq operator to compare with other FunctionGroup instance.
    *
    * @param[in] other FunctionGroup instance to compare this one with.
    * @return true in case both FunctionGroups are representing exactly the same meta-model element, false otherwise.
    */
   bool operator==(const FunctionGroup& other) const noexcept;

   // SWS_EM_02268
   /**
    * @brief uneq operator to compare with other FunctionGroup instance.
    * 
    * @param[in] other FunctionGroup instance to compare this one with.
    * @return false in case both FunctionGroups are representing exactly the same meta-model element, true otherwise.
    */
   bool operator!=(const FunctionGroup& other) const noexcept;
};
} // namespace exec
} // namespace ara
