/**
 * @file per_error_domain.h
 * @author vin (vin@misday.com)
 * @brief
 * @version 0.1
 * @date 2023-03-29
 *
 * @copyright Copyright (c) OpenAUTOSAR-AP 2023
 */

// R22-11

#pragma once

#include "ara/core/error_domain.h"

namespace ara
{
namespace per
{
// SWS_PER_00311
/**
 * @brief Defines the errors for Persistency.
 *
 * The enumeration values 0 - 255 are reserved for AUTOSAR assigned errors, the
 * stack provider is free to define additional errors starting from 256.
 */
enum class PerErrc : ara::core::ErrorDomain::CodeType
{
    kStorageNotFound        = 1, //< The requested Key-Value Storage or File Storage is
                                 //< not configured in the AUTOSAR model.
    kKeyNotFound            = 2, //< The provided key cannot be not found in the Key-Value Storage.
    kIllegalWriteAccess     = 3, //< Synchronizing a Key-Value Pair of the Key-Value Storage failed, or
                                 //< opening a file of the File Storage for writing or changing failed,
                                 //< because the Key-Value Storage or File Storage is configured
                                 //< read-only.
    kPhysicalStorageFailure = 4, ///< An error occurred when accessing the physical storage, e.g. because of a corrupted
                                 ///< file system or corrupted hardware, or because of insufficient access rights.
    kIntegrityCorrupted     = 5, ///< The structural integrity of the Key-Value Storage or File Storage
                                 ///< could not be established. This can happen when the internal
                                 ///< structure of a Key-Value Storage or the meta data of a File
                                 ///< Storage is corrupted.
    kValidationFailed = 6, ///< The validation of redundancy measures failed for a single key-value pair, for the whole
                           ///< Key-Value Storage, for a single file, or for the whole File Storage.
    kEncryptionFailed = 7, ///< The encryption or decryption failed for a single key-value pair, for the whole Key-Value
                           ///< Storage, for a single file, or for the whole File Storage.
    kDataTypeMismatch = 8, ///< The provided data type does not match the stored data type.
    kInitValueNotAvailable = 9,  ///< The operation could not be performed because no initial value is available.
    kResourceBusy          = 10, ///< The operation could not be performed because the resource is currently busy.
    kOutOfStorageSpace     = 12, ///< The physical storage space was exceeded.
    kFileNotFound          = 13, ///< The requested file name cannot be not found in the File Storage.
    kInvalidPosition = 15, ///< SetPosition tried to move to a position that is not reachable (i.e. which is smaller
                           ///< than zero or greater than the current size of the file).
    kIsEof           = 16, ///< The application tried to read from the end of the file or from an empty file.
    kInvalidOpenMode = 17, ///< Opening a file failed because the requested combination of OpenModes is invalid.
    kInvalidSize     = 18, ///< SetFileSize tried to set a new size that is bigger than the current file size.
    kTooManyFiles    = 19, ///< The maximum number of files was exceeded.
    kQuotaExceeded   = 20, ///< The allocated storage quota was exceeded.
    kAuthenticationFailed = 21, ///< Calculating or checking of the MAC failed for a single key-value pair, for the
                                ///< whole Key-Value Storage, for a single file, or for the whole File Storage.
};

// SWS_PER_00352
/**
 * @brief Returns the global PerErrorDomain object.
 *
 * @return constexpr const ara::core::ErrorDomain& The global PerErrorDomain object.
 */
constexpr const ara::core::ErrorDomain& GetPerDomain() noexcept;

// SWS_PER_00351
/**
 * @brief Creates an error code.
 *
 * @param[in] code Error code number.
 * @param[in] data Vendor defined data associated with the error.
 * @return constexpr ara::core::ErrorCode
 */
constexpr ara::core::ErrorCode MakeErrorCode(PerErrc code, ara::core::ErrorDomain::SupportDataType data) noexcept;

// SWS_PER_00354
/**
 * @brief Exception type thrown by Persistency.
 */
class PerException : public ara::core::Exception
{
    // SWS_PER_00355
    /**
     * @brief Construct a new Persistency exception object containing an error code.
     *
     * @param errorCode The error code.
     */
    explicit PerException(ara::core::ErrorCode errorCode) noexcept;
};

// SWS_PER_00312
/**
 * @brief Defines the error domain for Persistency.
 *
 * Unique ID: 0x8000’0000’0000’0101
 */
class PerErrorDomain final : public ara::core::ErrorDomain
{
    // SWS_PER_00411
    /**
     * @brief Alias for the error code value enumeration.
     */
    using Errc      = PerErrc;

    // SWS_PER_00412
    /**
     * @brief Alias for the exception base class.
     */
    using Exception = PerException;

    // SWS_PER_00313
    /**
     * @brief Creates a PerErrorDomain instance.
     */
    PerErrorDomain() noexcept;

    // SWS_PER_00314
    /**
     * @brief Returns the name of the error domain.
     *
     * @return const char* The name of the error domain.
     */
    const char* Name() const noexcept override;

    // SWS_PER_00315
    /**
     * @brief Returns the message associated with the error code.
     *
     * @param errorCode The error code number.
     * @return const char* The message associated with the error code.
     */
    const char* Message(CodeType errorCode) const noexcept override;

    // SWS_PER_00350
    /**
     * @brief Throws the exception associated with the error code.
     * 
     * @param errorCode The error to throw.
     */
    void ThrowAsException(const ara::core::ErrorCode& errorCode) const override;
};

} // namespace per
} // namespace ara
