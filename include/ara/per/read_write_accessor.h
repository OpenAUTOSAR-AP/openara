/**
 * @file read_write_accessor.h
 * @author vin (vin@misday.com)
 * @brief
 * @version 0.1
 * @date 2023-03-30
 *
 * @copyright Copyright (c) OpenAUTOSAR-AP 2023
 */

// R22-11

#pragma once

#include "ara/per/read_accessor.h"

namespace ara
{
namespace per
{
// SWS_PER_00343
/**
 * @brief ReadWriteAccessor is used to read and write file data.
 *
 * It provides the WriteBinary and WriteText methods featuring a Result for controlled, unformatted writing, and the
 * operator<< method for simple formatted writing. It also provides SyncToFile() to flush the buffer of the operating
 * system to the physical storage.
 */
class ReadWriteAccessor : public ReadAccessor
{
    // SWS_PER_00462
    /**
     * @brief The default constructor for ReadWriteAccessor shall not be used.
     */
    ReadWriteAccessor() = delete;

    // SWS_PER_00122
    /**
     * @brief Triggers flushing of the current file content to the physical storage.
     *
     * @return ara::core::Result<void> A Result of void. In case of an error, it contains any of the errors defined
     * below, or a vendor specific error.
     */
    ara::core::Result<void> ReadWriteAccessor::SyncToFile() noexcept;

    // SWS_PER_00428
    /**
     * @brief Reduces the size of the file to ’size’, effectively removing the current content of the file beyond this
     * size.
     *
     * The current file position is unchanged if it is lower than ’size’, or set to the last valid position in the file
     * otherwise. If ’size’ is 0, the current file position will also be set to 0.
     *
     * @param[in] size New size of the file.
     * @return ara::core::Result<void> A Result of void. In case of an error, it contains any of the errors defined
     * below, or a vendor specific error.
     */
    ara::core::Result<void> SetFileSize(std::uint64_t size) noexcept;

    // SWS_PER_00166
    /**
     * @brief Writes the content of a StringView to the file.
     *
     * The time when the content is persisted depends on the implementation of Persistency. SyncToFile can be used to
     * force Persistency to persist the file content.
     *
     * In case of an error, the file content might be corrupted, and the current position might or might not have
     * changed.
     *
     * The expected state of the file for each supported error can be expected to be as follows:
     * kPhysicalStorageFailure: The state of the file is unknown. It could have been entirely destroyed.
     * kEncryptionFailed: The content of the file and the current position will have been updated, but could not be
     * persisted. The persisted file will reflect an older version of the file. kOutOfStorage Space: The content of the
     * file will have been updated, but the part of the operation that exceeded the quota will have been discarded. The
     * current position will be at the end of the file.
     *
     * @param[in] s A StringView containing the characters to be written.
     * @return ara::core::Result<void> A Result of void. In case of an error, it contains any of the errors defined
     * below, or a vendor specific error.
     */
    ara::core::Result<void> WriteText(ara::core::StringView s) noexcept;

    // SWS_PER_00423
    /**
     * @brief Writes the content of a Span of Byte to the file.
     *
     * The time when the content is persisted depends on the implementation of Persistency. SyncToFile can be used to
     * force Persistency to persist the file content.
     *
     * In case of an error, the file content might be corrupted, and the current position might or might not have
     * changed.
     *
     * The expected state of the file for each supported error can be expected to be as follows:
     * kPhysicalStorageFailure: The state of the file is unknown. It could have been entirely destroyed.
     * kEncryptionFailed: The content of the file and the current position will have been updated, but could not be
     * persisted. The persisted file will reflect an older version of the file. kOutOfStorage Space: The content of the
     * file will have been updated, but the part of the operation that exceeded the quota will have been discarded. The
     * current position will be at the end of the file.
     *
     * @param[in] b A Span of Byte containing the bytes to be written.
     * @return ara::core::Result<void> A Result of void. In case of an error, it contains any of the errors defined
     * below, or a vendor specific error.
     */
    ara::core::Result<void> WriteBinary(ara::core::Span<const ara::core::Byte> b) noexcept;

    // SWS_PER_00125
    /**
     * @brief Writes the content of a StringView to the file.
     *
     * This operator is just a comfort feature for non-safety critical applications. If an error occurs during this
     * operation, it is silently ignored.
     *
     * @param s The StringView containing the characters to be written.
     * @return ReadWriteAccessor& The ReadWriteAccessor object.
     */
    ReadWriteAccessor& operator<<(ara::core::StringView s) noexcept;
};
} // namespace per
} // namespace ara
