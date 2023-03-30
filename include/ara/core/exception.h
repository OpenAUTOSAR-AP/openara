/**
 * \file exception.h
 * \author vin (vin@misday.com)
 * \brief
 * \version 0.1
 * \date 2020-12-04
 *
 * \copyright Copyright (c) OpenAUTOSAR-AP 2023
 */

// R22-11

#pragma once

#include "error_code.h"

namespace ara
{
namespace core
{
// SWS_CORE_00601
/**
 * \brief Base type for all AUTOSAR exception types.
 */
class Exception: public exception
{
public:
   // SWS_CORE_00611
   /**
    * \brief Construct a new Exception object with a specific ErrorCode.
    *
    * \param[in] err   the ErrorCode
    */
   explicit Exception(ErrorCode err) noexcept;

   // SWS_CORE_00615
   /**
    * @brief Move constructor from another instance.
    *
    * @param[in] other the other instance
    */
   Exception(Exception&& other) = default;

   // SWS_CORE_00616
   /**
    * @brief Move assignment operator from another instance.
    *
    * @param[in] other the other instance
    * @return Exception&
    */
   Exception& operator=(Exception&& other) &= default;

   // SWS_CORE_00617
   /**
    * @brief Destructs the Exception object.
    */
   virtual ~Exception() = default;

   // SWS_CORE_00612
   /**
    * \brief Return the explanatory string.
    *
    * This function overrides the virtual function std::exception::what. All guarantees about the
    * lifetime of the returned pointer that are given for std::exception::what are preserved.
    *
    * \return char const*  a null-terminated string
    */
   const char* what() const noexcept override;

   // SWS_CORE_00613
   /**
    * \brief Return the embedded ErrorCode that was given to the constructor.
    *
    * \return ErrorCode const&     reference to the embedded ErrorCode
    */
   const ErrorCode& Error() const noexcept;

   // SWS_CORE_00614
   /**
    * @brief Copy assignment operator from another instance.
    * This function is "protected" in order to prevent some opportunities for accidental slicing.
    *
    * @param[in] other the other instance
    * @return Exception& *this
    */
   Exception& operator=(const Exception const& other) = default;

   // SWS_CORE_00618
   /**
    * @brief Copy constructor from another instance.
    * This function is "protected" in order to prevent some opportunities for accidental slicing.
    *
    * @param[in] other the other instance
    */
   Exception(const Exception& other) = default;
};
} // namespace core

} // namespace ara
