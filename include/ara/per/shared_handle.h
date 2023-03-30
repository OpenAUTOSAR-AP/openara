/**
 * @file shared_handle.h
 * @author vin (vin@misday.com)
 * @brief
 * @version 0.1
 * @date 2023-03-29
 *
 * @copyright Copyright (c) OpenAUTOSAR-AP 2023
 */

// R22-11

#pragma once

namespace ara
{
namespace per
{
// SWS_PER_00362
/**
 * @brief Handle to a File Storage or Key-Value Storage.
 *
 * A SharedHandle is returned by the functions OpenFileStorage() and OpenKeyValueStorage() and can be passed between
 * threads as needed.
 *
 * It provides the abstraction that is necessary to allow thread-safe implementation of OpenFile Storage() and
 * OpenKeyValueStorage().
 *
 * @tparam T
 */
template <typename T>
class SharedHandle final
{
public:
   // SWS_PER_00367
   /**
    * @brief Move constructor for SharedHandle.
    *
    * The source handle object is invalidated and cannot be used anymore.
    *
    * The operator bool() shall be used to check the state of a handle object before using any other operators of the
    * handle object.
    *
    * @param[in] sh The SharedHandle object to be moved.
    */
   SharedHandle(SharedHandle&& sh) noexcept;

   // SWS_PER_00369
   /**
    * @brief Copy constructor for SharedHandle.
    *
    * @param[in] sh The SharedHandle object to be copied.
    */
   SharedHandle(const SharedHandle& sh) noexcept;

   // SWS_PER_00368
   /**
    * @brief Move assignment operator for SharedHandle.
    *
    * The source handle object is invalidated and cannot be used anymore.
    *
    * The operator bool() shall be used to check the state of a handle object before using any other operators of the
    * handle object.
    *
    * @param[in] sh The SharedHandle object to be moved.
    * @return SharedHandle& The moved SharedHandle object.
    */
   SharedHandle& operator=(SharedHandle&& sh) & noexcept;

   // SWS_PER_00370
   /**
    * @brief Copy assignment operator for SharedHandle.
    *
    * @param[in] sh The SharedHandle object to be copied.
    * @return SharedHandle& The copied SharedHandle object.
    */
   SharedHandle& operator=(const Shared Handle& sh) & noexcept;

   // SWS_PER_00398
   /**
    * @brief Handle state.
    *
    * True if the handle represents a valid object of the templated class, False if the handle is empty (e.g. after a
    * move operation).
    *
    * Using other operators than bool() of an empty handle will result in undefined behavior.
    *
    * @return true
    * @return false
    */
   explicit operator bool() const noexcept;

   // SWS_PER_00363
   /**
    * @brief Non-constant arrow operator.
    *
    * @return T*
    */
   T* operator->() noexcept;

   // SWS_PER_00364
   /**
    * @brief Constant arrow operator.
    *
    * @return const T*
    */
   const T* operator->() const noexcept;

   // SWS_PER_00402
   /**
    * @brief Non-constant dereference operator.
    *
    * @return T&
    */
   T& operator*() noexcept;

   // SWS_PER_00403
   /**
    * @brief Constant dereference operator.
    *
    * @return const T&
    */
   const T& operator*() const noexcept;
};
} // namespace per
} // namespace ara
