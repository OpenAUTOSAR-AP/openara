/**
 * @file read_accessor.h
 * @author vin (vin@misday.com)
 * @brief
 * @version 0.1
 * @date 2023-03-30
 *
 * @copyright Copyright (c) OpenAUTOSAR-AP 2023
 */

// R22-11

#pragma once

#include "ara/core/result.h"

namespace ara
{
namespace per
{
// SWS_PER_00146
/**
 * @brief Specification of origin used in MovePosition.
 */
enum class Origin : std::uint32_t
{
    kBeginning = 0, ///< Seek from the beginning of the file.
    kCurrent   = 1, ///< Seek from the current position.
    kEnd       = 2, ///< Seek from the end of the file.
};

// SWS_PER_00342
/**
 * @brief ReadAccessor is used to read file data.
 *
 * It provides binary and text mode methods for checking or getting the current byte/character (PeekByte/PeekChar,
 * GetByte/GetChar) methods for reading a section of a binary/text file (ReadBinary/ReadText), a method to read a line
 * of text (ReadLine), and methods for checking and setting the current position in the file (GetPosition, SetPosition,
 * MovePosition, IsEof) and for checking the current size of the file (GetSize).
 */
class ReadAccessor
{
    // SWS_PER_00461
    /**
     * @brief The move constructor for ReadAccessor shall not be used.
     */
    ReadAccessor()                               = delete;

    // SWS_PER_00413
    /**
     * @brief The move constructor for ReadAccessor shall not be used.
     */
    ReadAccessor(ReadAccessor&& ra)              = delete;

    // SWS_PER_00415
    /**
     * @brief The copy constructor for ReadAccessor shall not be used.
     *
     */
    ReadAccessor(const ReadAccessor&)            = delete;

    // SWS_PER_00414
    /**
     * @brief The move assignment operator for ReadAccessor shall not be used.
     */
    ReadAccessor& operator=(ReadAccessor&& ra) & = delete;

    // SWS_PER_00416
    /**
     * @brief The copy assignment operator for ReadAccessor shall not be used.
     */
    ReadAccessor& operator=(const ReadAccessor&) = delete;

    // SWS_PER_00417
    /**
     * @brief Destructor for ReadAccessor.
     */
    ~ReadAccessor() noexcept;

    // SWS_PER_00167
    /**
     * @brief Returns the character at the current position of the file.
     *
     * The current position is not changed.
     *
     * @return ara::core::Result<char> A Result containing a character. In case of an error, it contains any of the
     * errors defined below, or a vendor specific error.
     */
    ara::core::Result<char> PeekChar() const noexcept;

    // SWS_PER_00418
    /**
     * @brief Returns the byte at the current position of the file.
     *
     * The current position is not changed.
     *
     * @return ara::core::Result<ara::core::Byte> A Result containing a byte. In case of an error, it contains any of
     * the errors defined below, or a vendor specific error.
     */
    ara::core::Result<ara::core::Byte> PeekByte() const noexcept;

    // SWS_PER_00168
    /**
     * @brief Returns the character at the current position of the file, advancing the current position.
     *
     * In case of an error, the current position is not changed.
     *
     * @return ara::core::Result<char> A Result containing a character. In case of an error, it contains any of the
     * errors defined below, or a vendor specific error.
     */
    ara::core::Result<char> GetChar() noexcept;

    // SWS_PER_00419
    /**
     * @brief Returns the byte at the current position of the file, advancing the current position.
     *
     * In case of an error, the current position is not changed.
     *
     * @return ara::core::Result<ara::core::Byte> A Result containing a byte. In case of an error, it contains any of
     * the errors defined below, or a vendor specific error.
     */
    ara::core::Result<ara::core::Byte> GetByte() noexcept;

    // SWS_PER_00420
    /**
     * @brief Reads all remaining characters into a String, starting from the current position.
     *
     * The returned string may start with an incomplete Unicode code point in case the current read position is in the
     * middle of a code point.
     *
     * The current position is set to the end of the file.
     *
     * In case of an error, the current position is not changed.
     *
     * @return ara::core::Result<ara::core::String> A Result containing a String. In case of an error, it contains any
     * of the errors defined below, or a vendor specific error.
     */
    ara::core::Result<ara::core::String> ReadText() noexcept;

    // SWS_PER_00165
    /**
     * @brief Reads a number of characters into a String, starting from the current position.
     *
     * The returned string may start and/or end with incomplete Unicode code points in case the current read position
     * and/or the last read character (code unit) is in the middle of a code point.
     *
     * The current position is advanced accordingly.
     *
     * If the end of the file is reached, the number of returned characters can be less than the requested number, and
     * the current position is set to the end of the file.
     *
     * In case of an error, the current position is not changed.
     *
     * @param[in] n Number of characters to read.
     * @return ara::core::Result<ara::core::String> A Result containing a String. In case of an error, it contains any
     * of the errors defined below, or a vendor specific error.
     */
    ara::core::Result<ara::core::String> ReadText(std::uint64_t n) noexcept;

    // SWS_PER_00421
    /**
     * @brief Reads all remaining bytes into a Vector of Byte, starting from the current position.
     *
     * The current position is set to the end of the file.
     *
     * In case of an error, the current position is not changed.
     *
     * @return ara::core::Result<ara::core::Vector<ara::core::Byte>> A Result containing a Vector of Byte. In case of an
     * error, it contains any of the errors defined below, or a vendor specific error.
     */
    ara::core::Result<ara::core::Vector<ara::core::Byte>> ReadBinary() noexcept;

    // SWS_PER_00422
    /**
     * @brief Reads a number of bytes into a Vector of Byte, starting from the current position.
     *
     * The current position is advanced accordingly.
     *
     * If the end of the file is reached, the number of returned bytes can be less than the requested number, and the
     * current position is set to the end of the file.
     *
     * In case of an error, the current position is not changed.
     *
     * @param[in] n Number of bytes to read.
     * @return ara::core::Result<ara::core::Vector<ara::core::Byte>> A Result containing a Vector of Byte. In case of an
     * error, it contains any of the errors defined below, or a vendor specific error.
     */
    ara::core::Result<ara::core::Vector<ara::core::Byte>> ReadBinary(std::uint64_t n) noexcept;

    // SWS_PER_00119
    /**
     * @brief Reads a complete line of characters into a String, advancing the current position accordingly.
     *
     * The end of the line is demarcated by the delimiter, or by "\\n" (ASCII 0x0a) if that parameter is omitted. The
     * delimiter itself is not included in the returned String.
     *
     * Only Unicode code points with one character (code unit) can be used as delimiters. The returned string may start
     * with an incomplete Unicode code point in case the current read position is in the middle of a code point.
     *
     * If the end of the file is reached, the remaining characters are returned and the current position is set to the
     * end of the file.
     *
     * In case of an error, the current position is not changed.
     *
     * @param[in] delimiter The character that is used as delimiter.
     * @return ara::core::Result<ara::core::String> A Result containing a String. In case of an error, it contains any
     * of the errors defined below, or a vendor specific error.
     */
    ara::core::Result<ara::core::String> ReadLine(char delimiter = '\n') noexcept;

    // SWS_PER_00424
    /**
     * @brief Returns the current size of a file in bytes.
     *
     * @return std::uint64_t The current size of the file in bytes.
     */
    std::uint64_t GetSize() const noexcept;

    // SWS_PER_00162
    /**
     * @brief Returns the current position relative to the beginning of the file.
     *
     * The returned position may be at the end of the file.
     *
     * @return std::uint64_t The current position in the file in bytes from the beginning of the file.
     */
    std::uint64_t GetPosition() const noexcept;

    // SWS_PER_00163
    /**
     * @brief Sets the current position relative to the beginning of the file.
     *
     * In case of an error, the current position is not changed.
     *
     * @param[in] position Current position in the file in bytes from the beginning of the file.
     * @return ara::core::Result<void> A Result of void. In case of an error, it contains any of the errors defined
     * below, or a vendor specific error.
     */
    ara::core::Result<void> SetPosition(std::uint64_t position) noexcept;

    // SWS_PER_00164
    /**
     * @brief Moves the current position in the file relative to the Origin.
     *
     * In case of an error, the current position is not changed.
     *
     * @param[in] origin Starting point from which to move ’offset’ bytes.
     * @param[in] offset Offset in bytes relative to ’origin’. Can be positive in case of kBeginning and kCurrent and
     * negative in case of kCurrent and kEnd. In case of kCurrent, an offset of zero will not change the current
     * position. In case of kEnd, an offset of zero will set the position to the end of the file.
     * @return ara::core::Result<std::uint64_t> A Result containing the new position in bytes from the beginning of the
     * file. In case of an error, it contains any of the errors defined below, or a vendor specific error.
     */
    ara::core::Result<std::uint64_t> MovePosition(Origin origin, std::int64_t offset) noexcept;

    // SWS_PER_00107
    /**
     * @brief Checks if the current position is at end of file.
     * 
     * @return True if the current position is at the end of the file, false otherwise.
     */
    bool IsEof() const noexcept;
};

} // namespace per
} // namespace ara
