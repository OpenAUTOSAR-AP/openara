/**
 * \file file_storage.h
 * \author vin (vin@misday.com)
 * \brief
 * \version 0.1
 * \date 2020-12-08
 *
 * \copyright Copyright (c) OpenAUTOSAR-AP 2023
 */

// R22-11

#pragma once

#include "ara/core/result.h"

namespace ara
{
namespace per
{
// SWS_PER_00116
/**
 * \brief Opens a File Storage.
 *
 * OpenFileStorage will fail with kResourceBusy when the File Storage is currently being modified by a call from another
 * thread to UpdatePersistency, ResetPersistency, RecoverAllFiles, or ResetAllFiles.
 *
 * Because multiple threads can access the same File Storage concurrently, the File Storage might not be closed when the
 * SharedHandle returned by this function goes out of scope. It will only be closed when all SharedHandles that refer to
 * the same File Storage went out of scope.
 *
 * \param[in] fs The shortName path of a PortPrototype typed by a PersistencyFileProxyInterface.
 * \return ara::core::Result<SharedHandle<FileStorage>> A Result containing a SharedHandle for the File Storage. In case
 * of an error, it contains any of the errors defined below, or a vendor specific error. \note \thread safety reentrant
 */
ara::core::Result<SharedHandle<FileStorage>> OpenFileStorage(const ara::core::InstanceSpecifier& fs) noexcept;

// SWS_PER_00335
/**
 * \brief Recover the whole file storage, including all files.
 *
 * This method allows to recover a file storage when the redundancy checks fail. It will fail with a k
 * ResourceBusyError when the file storage is currently open.
 *
 * This method does a best-effort recovery of all files. After recovery, files might show outdated or
 * initial content, or might be lost.
 *
 * \param[in] fs    The shortName path of a PortPrototype typed by a
 *                  PersistencyFileProxyInterface.
 * \return ara::core::Result<void>  A Result, being either empty or containing one of
 *                                  the errors defined for Persistency in PerErrc.
 * \note
 * \thread safety reentrant
 */
ara::core::Result<void> RecoverAllFiles(const ara::core::InstanceSpecifier& fs) noexcept;

// SWS_PER_00336
/**
 * @brief Resets a File Storage, including all files.
 *
 * ResetAllFiles resets a File Storage to the initial state, containing only the files which were deployed from the
 * manifest, with their initial content. Afterwards, the File Storage will appear as if it was newly installed from the
 * current manifest.
 *
 * It will fail with kResourceBusy when the File Storage is currently open, or when it is modified by a call from
 * another thread to UpdatePersistency, ResetPersistency, RecoverAllFiles, or ResetAll Files.
 *
 * @param fs The shortName path of a PortPrototype typed by a PersistencyFileStorageInterface.
 * @return ara::core::Result<void> A Result of void. In case of an error, it contains any of the errors defined below,
 * or a vendor specific error.
 */
ara::core::Result<void> ResetAllFiles(const ara::core::InstanceSpecifier& fs) noexcept;

// SWS_PER_00406
/**
 * @brief Returns the space in bytes currently occupied by a File Storage.
 *
 * The returned size includes all meta data and the space used for redundancy and backups.
 *
 * The returned size is only guaranteed to be accurate if the File Storage is not opened and no other operation on the
 * File Storage takes place at the same time.
 *
 * @param fs The shortName path of a PortPrototype typed by a PersistencyFileStorageInterface.
 * @return ara::core::Result<std::uint64_t> A Result containing the occupied space in bytes. In case of an error, it
 * contains any of the errors defined below, or a vendor specific error.
 */
ara::core::Result<std::uint64_t> GetCurrentFileStorageSize(const ara::core::InstanceSpecifier& fs) noexcept;

// SWS_PER_00147
/**
 * @brief This enumeration defines how a file shall be opened.
 *
 * The values can be combined (using | and |=) as long as they do not contradict each other.
 *
 */
enum class OpenMode : std::uint32_t
{
    kAtTheBeginning = 1 << 0, ///< Sets the seek position to the beginning of the file when the file is opened. This
                              ///< mode cannot be combined with kAtTheEnd.
    kAtTheEnd = 1 << 1, ///< Sets the seek position to the end of the file when the file is opened. This mode cannot be
                        ///< combined with kAtTheBeginning or kTruncate.
    kTruncate =
        1 << 2, ///< Removes existing content when the file is opened. This mode cannot be combined with kAtTheEnd.
    kAppend = 1 << 3, ///< Append to the end. Always seeks to the end of the file before writing.
};

// SWS_PER_00144
/**
 * @brief Merges two OpenMode modifiers into one.
 *
 * @param left First OpenMode modifiers.
 * @param right Second OpenMode modifiers.
 * @return constexpr OpenMode returns Merged OpenMode modifiers.
 */
constexpr OpenMode operator|(OpenMode left, OpenMode right);

// SWS_PER_00434
/**
 * @brief Merges an OpenMode modifier into this OpenMode.
 *
 * @param left Left OpenMode modifiers.
 * @param right Right OpenMode modifiers.
 * @return OpenMode& returns The modified OpenMode.
 */
OpenMode& operator|=(OpenMode& left, const OpenMode& right);

// SWS_PER_00435
/**
 * @brief This enumeration describes how and when a file was created.
 */
enum class FileCreationState : std::uint32_t
{
    kCreatedDuringInstallion =
        1, ///< The file was created by Persistency after installation of the application or after ResetPersistency.
    kCreatedDuringUpdate   = 2, ///< The file was created by Persistency during an update.
    kCreatedDuringReset    = 3, ///< The file was re-created due to a call to ResetFile or ResetAllFiles.
    kCreatedDuringRecovery = 4, ///< The file was re-created by Persistency after a corruption was detected.
    kCreatedByApplication  = 5, ///< The file was created by the application.
};

// SWS_PER_00436
/**
 * @brief This enumeration describes how and when a file was last modified.
 */
enum class FileModificationState : std::uint32_t
{
    kModifiedDuringUpdate   = 2, ///< The file was last modified by Persistency during an update.
    kModifiedDuringReset    = 3, ///< The file was last modified by Persistency due to a call to ResetFile or
                                 ///< ResetAllFiles.
    kModifiedDuringRecovery = 4, ///< The file was last modified by Persistency after a corruption was detected.
    kModifiedByApplication  = 5, ///< The file was last modified by the application.
};

// SWS_PER_00437
/**
 * @brief This structure contains additional information on a file returned by GetFileInfo.
 */
struct ara::per::FileInfo
{
    // SWS_PER_00441
    std::uint64_t creationTime; ///< Time in nanoseconds since midnight 1970-01-01 UTC at which the file was created.
    // SWS_PER_00442
    std::uint64_t
        modificationTime; ///< Time in nanoseconds since midnight 1970-01-01 UTC at which the file was last modified.
    // SWS_PER_00443
    std::uint64_t
        accessTime; ///< Time in nanoseconds since midnight 1970-01-01 UTC at which the file was last accessed.
    // SWS_PER_00444
    FileCreationState fileCreationState; ///< Information on how and by whom the file was created.
    // SWS_PER_00445
    FileModificationState fileModificationState; ///< Information on how and by whom the file was last modified.
};

// SWS_PER_00340
/**
 * @brief The File Storage contains a set of files identified by their file names.
 */
class ara::per::FileStorage final
{
    // SWS_PER_00460
    /**
     * @brief The default constructor for FileStorage shall not be used.
     */
    FileStorage()                              = delete;

    // SWS_PER_00326
    /**
     * @brief The move constructor for FileStorage shall not be used.
     */
    FileStorage(FileStorage&& fs)              = delete;

    // SWS_PER_00328
    /**
     * @brief The copy constructor for FileStorage shall not be used.
     */
    FileStorage(const FileStorage&)            = delete;

    // SWS_PER_00327
    /**
     * @brief The move assignment operator for FileStorage shall not be used.
     */
    FileStorage& operator=(FileStorage&& fs) & = delete;

    // SWS_PER_00329
    /**
     * @brief The copy assignment operator for FileStorage shall not be used.
     */
    FileStorage& operator=(const FileStorage&) = delete;

    // SWS_PER_00330
    /**
     * @brief Destructor for FileStorage.
     */
    ~FileStorage() noexcept;

    // SWS_PER_00110
    /**
     * @brief Returns a list of all currently available file names of this File Storage.
     *
     * The list of file names is only accurate if no file is added or deleted at the same time.
     *
     * @return ara::core::Result<ara::core::Vector<ara::core::String>> A Result containing a list of available file
     * names. In case of an error, it contains any of the errors defined below, or a vendor specific error.
     */
    ara::core::Result<ara::core::Vector<ara::core::String>> GetAllFileNames() const noexcept;

    // SWS_PER_00111
    /**
     * @brief Deletes a file from this File Storage.
     *
     * This operation will fail with kResourceBusy when the file is currently open.
     *
     * @param fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
     * @return ara::core::Result<void> A Result of void. In case of an error, it contains any of the errors defined
     * below, or a vendor specific error.
     */
    ara::core::Result<void> DeleteFile(ara::core::StringView fileName) noexcept;

    // SWS_PER_00112
    /**
     * @brief Checks if a file exists in this File Storage.
     *
     * The result is only accurate if no file is added or deleted at the same time. E.g. when a file is removed in
     * another thread directly after this function returned "true", the result is not valid anymore.
     *
     * @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
     * @return ara::core::Result<bool> A Result containing true if the file could be located or false if it couldn’t. In
     * case of an error, it contains any of the errors defined below, or a vendor specific error.
     */
    ara::core::Result<bool> FileExists(ara::core::StringView fileName) const noexcept;

    // SWS_PER_00337
    /**
     * @brief Recovers a file of this File Storage.
     *
     * This method allows to recover a single file when the redundancy checks fail.
     *
     * It will fail with kResourceBusy when the file is currently open.
     *
     * This method does a best-effort recovery of the file. After recovery, the file might show outdated or initial
     * content, or might be lost.
     *
     * @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
     * @return ara::core::Result<void> A Result of void. In case of an error, it contains any of the errors defined
     * below, or a vendor specific error.
     */
    ara::core::Result<void> RecoverFile(ara::core::StringView fileName) noexcept;

    // SWS_PER_00338
    /**
     * @brief Resets a file of this File Storage to its initial content.
     *
     * ResetFile allows to reset a single file to its initial content. If the file is currently not available in the
     * File Storage, it is re-created. Afterwards, the file will appear in both cases as if it was newly installed from
     * the current manifest.
     *
     * It will fail with kResourceBusy when the file is currently open, and with kInitValueNotAvailable when neither
     * design nor deployment define an initial content for the file.
     *
     * @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
     * @return ara::core::Result<void> A Result of void. In case of an error, it contains any of the errors defined
     * below, or a vendor specific error.
     */
    ara::core::Result<void> ResetFile(ara::core::StringView fileName) noexcept;

    // SWS_PER_00407
    /**
     * @brief Returns the space in bytes currently occupied by the content of a file of this File Storage.
     *
     * The returned size might be inaccurate if any of the instances of a file is invalid or if another operation on the
     * file takes place at the same time.
     *
     * @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
     * @return ara::core::Result<std::uint64_t> A Result containing the occupied space in bytes. In case of an error, it
     * contains any of the errors defined below, or a vendor specific error.
     */
    ara::core::Result<std::uint64_t> GetCurrentFileSize(ara::core::StringView fileName) const noexcept;

    // SWS_PER_00438
    /**
     * @brief Returns additional information on a file of this File Storage.
     *
     * The returned FileInfo struct contains information about the times when the file was created, last modified, and
     * last accessed, and about how and by whom the file was created and last modified. The modificationTime,
     * accessTime, and fileModificationState returned in the FileInfo are only accurate if the file is currently not
     * open.
     *
     * @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
     * @return ara::core::Result<FileInfo> A Result containing a FileInfo struct. In case of an error, it contains any
     * of the errors defined below, or a vendor specific error.
     */
    ara::core::Result<FileInfo> GetFileInfo(ara::core::StringView fileName) const noexcept;

    // SWS_PER_00375
    /**
     * @brief Opens a file of this File Storage for reading and writing.
     *
     * The file is opened with the seek position set to the beginning (corresponding to kAtTheBeginning).
     *
     * If the file does not exist, it is created.
     *
     * The file will be closed when the returned UniqueHandle goes out of scope.
     *
     * @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
     * @return ara::core::Result<UniqueHandle<ReadWriteAccessor>> A Result containing a UniqueHandle for the file. In
     * case of an error, it contains any of the errors defined below, or a vendor specific error.
     */
    ara::core::Result<UniqueHandle<ReadWriteAccessor>> OpenFileReadWrite(ara::core::StringView fileName) noexcept;

    // SWS_PER_00113
    /**
     * @brief Opens a file of this File Storage for reading and writing with a defined mode.
     *
     * If not otherwise specified by the provided mode, the file is opened with the seek position set to the beginning
     * (corresponding to kAtTheBeginning).
     *
     * If the file does not exist, it is created.
     *
     * The file will be closed when the returned UniqueHandle goes out of scope.
     *
     * @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
     * @param[in] mode Mode with which the file shall be opened.
     * @return ara::core::Result<UniqueHandle<ReadWriteAccessor>> A Result containing a UniqueHandle for the file. In
     * case of an error, it contains any of the errors defined below, or a vendor specific error.
     */
    ara::core::Result<UniqueHandle<ReadWriteAccessor>> OpenFileReadWrite(ara::core::StringView fileName,
                                                                         OpenMode mode) noexcept;

    // SWS_PER_00429
    /**
     * @brief Opens a file of this File Storage for reading and writing with a user provided buffer.
     *
     * If not otherwise specified by the provided mode, the file is opened with the seek position set to the beginning
     * (corresponding to kAtTheBeginning).
     *
     * The provided buffer will be used by the ReadWriteAccessor to implement block-wise reading and writing to speed up
     * multiple small accesses to the file.
     *
     * If the file does not exist, it is created.
     *
     * The file will be closed when the returned UniqueHandle goes out of scope.
     *
     * @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
     * @param[in] mode Mode with which the file shall be opened.
     * @param[in] buffer Memory to be used for block-wise reading/writing.
     * @return ara::core::Result<UniqueHandle<ReadWriteAccessor>> A Result containing a UniqueHandle for the file. In
     * case of an error, it contains any of the errors defined below, or a vendor specific error.
     */
    ara::core::Result<UniqueHandle<ReadWriteAccessor>> OpenFileReadWrite(
        ara::core::StringView fileName, OpenMode mode, ara::core::Span<ara::core::Byte> buffer) noexcept;

    // SWS_PER_00376
    /**
     * @brief Opens a file of this File Storage for reading.
     *
     * The file is opened with the seek position set to the beginning (corresponding to kAtTheBeginning).
     *
     * The file will be closed when the returned UniqueHandle goes out of scope.
     *
     * @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
     * @return ara::core::Result<UniqueHandle<ReadAccessor>> A Result containing a UniqueHandle for the file. In case of
     * an error, it contains any of the errors defined below, or a vendor specific error.
     */
    ara::core::Result<UniqueHandle<ReadAccessor>> OpenFileReadOnly(ara::core::StringView fileName) noexcept;

    // SWS_PER_00114
    /**
     * @brief Opens a file of this File Storage for reading with a defined mode.
     *
     * If not otherwise specified by the provided mode, the file is opened with the seek position set to the beginning
     * (corresponding to kAtTheBeginning).
     *
     * The file will be closed when the returned UniqueHandle goes out of scope.
     *
     * @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
     * @param[in] mode Mode with which the file shall be opened.
     * @return ara::core::Result<UniqueHandle<ReadAccessor>> A Result containing a UniqueHandle for the file. In case of
     * an error, it contains any of the errors defined below, or a vendor specific error.
     */
    ara::core::Result<UniqueHandle<ReadAccessor>> OpenFileReadOnly(ara::core::StringView fileName,
                                                                   OpenMode mode) noexcept;

    // SWS_PER_00430
    /**
     * @brief Opens a file of this File Storage for reading with a user provided buffer.
     *
     * If not otherwise specified by the provided mode, the file is opened with the seek position set to the beginning
     * (corresponding to kAtTheBeginning).
     *
     * The provided buffer will be used by the ReadAccessor to implement block-wise reading to speed up multiple small
     * accesses to the file.
     *
     * The file will be closed when the returned UniqueHandle goes out of scope.
     *
     * @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
     * @param[in] mode Mode with which the file shall be opened.
     * @param[in] buffer Memory to be used for block-wise reading.
     * @return ara::core::Result<UniqueHandle<ReadAccessor>> A Result containing a UniqueHandle for the file. In case of
     * an error, it contains any of the errors defined below, or a vendor specific error.
     */
    ara::core::Result<UniqueHandle<ReadAccessor>> OpenFileReadOnly(ara::core::StringView fileName, OpenMode mode,
                                                                   ara::core::Span<ara::core::Byte> buffer) noexcept;

    // SWS_PER_00377
    /**
     * @brief Opens a file of this File Storage for writing.
     *
     * The file is truncated (corresponding to kTruncate).
     *
     * If the file does not exist, it is created.
     *
     * The file will be closed when the returned UniqueHandle goes out of scope.
     *
     * @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
     * @return ara::core::Result<UniqueHandle<ReadWriteAccessor>> A Result containing a UniqueHandle for the file. In
     * case of an error, it contains any of the errors defined below, or a vendor specific error.
     */
    ara::core::Result<UniqueHandle<ReadWriteAccessor>> OpenFileWriteOnly(ara::core::StringView fileName) noexcept;

    // SWS_PER_00115
    /**
     * @brief Opens a file of this File Storage for writing with a defined mode.
     *
     * If not otherwise specified by the provided mode, the file is truncated (corresponding to kTruncate).
     *
     * If the file does not exist, it is created.
     *
     * The file will be closed when the returned UniqueHandle goes out of scope.
     *
     * @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
     * @param[in] mode Mode with which the file shall be opened.
     * @return ara::core::Result<UniqueHandle<ReadWriteAccessor>> A Result containing a UniqueHandle for the file. In
     * case of an error, it contains any of the errors defined below, or a vendor specific error.
     */
    ara::core::Result<UniqueHandle<ReadWriteAccessor>> OpenFileWriteOnly(ara::core::StringView fileName,
                                                                         OpenMode mode) noexcept;

    // SWS_PER_00431
    /**
     * @brief Opens a file of this File Storage for writing with a user provided buffer.
     *
     * If not otherwise specified by the provided mode, the file is truncated (corresponding to kTruncate).
     *
     * The provided buffer will be used by the ReadWriteAccessor to implement block-wise writing to speed up multiple
     * small accesses to the file.
     *
     * If the file does not exist, it is created.
     *
     * The file will be closed when the returned UniqueHandle goes out of scope.
     *
     * @param[in] fileName File name of the file. May correspond to the PersistencyFile.fileName of a configured file.
     * @param[in] mode Mode with which the file shall be opened.
     * @param[in] buffer Memory to be used for block-wise writing.
     * @return ara::core::Result<UniqueHandle<ReadWriteAccessor>> A Result containing a UniqueHandle for the file. In
     * case of an error, it contains any of the errors defined below, or a vendor specific error.
     */
    ara::core::Result<UniqueHandle<ReadWriteAccessor>> OpenFileWriteOnly(
        ara::core::StringView fileName, OpenMode mode, ara::core::Span<ara::core::Byte> buffer) noexcept;
};

} // namespace per

} // namespace ara
