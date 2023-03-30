/**
 * @file unique_handle.h
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
// SWS_PER_00359
/**
 * @brief Handle to a ReadAccessor or ReadWriteAccessor.
 *
 * A UniqueHandle is returned by the functions OpenFileReadOnly(), OpenFileWriteOnly(), and OpenFileReadWrite().
 *
 * @tparam T
 */
template <typename T>
class UniqueHandle final
{
public:
   // SWS_PER_00371
   /**
    * @brief Move constructor for UniqueHandle.
    *
    * The source handle object is invalidated and cannot be used anymore.
    *
    * The operator bool() shall be used to check the state of a handle object before using any other operators of the
    * handle object.
    *
    * @param[in] uh The UniqueHandle object to be moved.
    */
   UniqueHandle(UniqueHandle&& uh) noexcept;

   // SWS_PER_00373
   /**
    * @brief The copy constructor for UniqueHandle shall not be used.
    *
    */
   UniqueHandle(const UniqueHandle&) = delete;

   // SWS_PER_00372
   /**
    * @brief Move assignment operator for UniqueHandle.
    *
    * The source handle object is invalidated and cannot be used anymore.
    *
    * The operator bool() shall be used to check the state of a handle object before using any other operators of the
    * handle object.
    *
    * @param[in] uh The UniqueHandle object to be moved.
    * @return UniqueHandle& The moved UniqueHandle object.
    */
   UniqueHandle& operator=(UniqueHandle&& uh) & noexcept;

   // SWS_PER_00374
   /**
    * @brief The copy assignment operator for UniqueHandle shall not be used.
    *
    * @param Handle
    * @return UniqueHandle&
    */
   UniqueHandle& operator=(const Unique Handle&) = delete;

   // SWS_PER_00399
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

   // SWS_PER_00360
   /**
    * @brief Non-constant arrow operator.
    *
    * @return T*
    */
   T* operator->() noexcept;

   // SWS_PER_00361
   /**
    * @brief Constant arrow operator.
    *
    * @return const T*
    */
   const T* operator->() const noexcept;

   // SWS_PER_00400
   /**
    * @brief Non-constant dereference operator.
    *
    * @return T&
    */
   T& operator*() noexcept;

   // SWS_PER_00401
   /**
    * @brief Constant dereference operator.
    *
    * @return const T&
    */
   const T& operator*() const noexcept;
};
} // namespace per
} // namespace ara
