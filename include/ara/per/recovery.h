/**
 * @file recovery.h
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
// SWS_PER_00432
/**
 * @brief Defines the reported recovery actions.
 */
enum class RecoveryReportKind : std::uint32_t
{
   kKeyValueStorageRecoveryFailed =
      1, //< A Key-Value Storage was corrupted, an insufficient number of valid copies existed. storage contains the
         // short-name path of the Key-Value Storage, reported Elements is empty, reportedInstances contains the indices
         // of the affected Key-Value Storage copies.
   kKeyValueStorageRecovered =
      2, //< A Key-Value Storage was corrupted, but a sufficient number of valid copies existed. storage contains the
         // short-name path of the Key-Value Storage, reported Elements is empty, reportedInstances contains the indices
         // of the affected Key-Value Storage copies.
   kKeyRecoveryFailed =
      3, //< A set of key-value pairs was corrupted, an insufficient number of valid copies existed. storage contains
         // the short-name path of the Key-Value Storage, reportedElements contains the list of affected keys,
         // reportedInstances contains the indices of the affected Key-Value Storage or key-value pair copies. In
         // general, the nth key in reportedElements corresponds to the nth index in reportedInstances, i.e. a key may
         // be reported several times if several copies are broken. In case only one key-value pair is affected,
         // reported Elements may be provided containing just this key.
   kKeyRecovered =
      4, //< A set of key-value pairs was corrupted, but a sufficient number of valid copies existed. storage contains
         // the short-name path of the Key-Value Storage, reportedElements contains the list of affected keys,
         // reportedInstances contains the indices of the affected Key-Value Storage or key-value pair copies. In
         // general, the nth key in reportedElements corresponds to the nth index in reportedInstances, i.e. a key may
         // be reported several times if several copies are broken. In case only one key-value pair is affected,
         // reported Elements may be provided containing just this key.
   kFileStorageRecoveryFailed = 5, //< A File Storage was corrupted, an insufficient number of valid copies existed.
                                   // storage contains the short-name path of the File Storage, reported Elements is
                                   // empty, reportedInstances contains the indices of the affected File Storage copies.
   kFileStorageRecovered = 6, //< A File Storage was corrupted, but a sufficient number of valid copies existed. storage
                              // contains the short-name path of the File Storage, reported Elements is empty,
                              // reportedInstances contains the indices of the affected File Storage copies.
   kFileRecoveryFailed =
      7, //< A set of files was corrupted, an insufficient number of valid copies existed. storage contains the
         // short-name path of the File Storage, reported Elements contains the list of affected file names,
         // reportedInstances contains the indices of the affected File Storage or file copies. In general, the nth file
         // name in reportedElements corresponds to the nth index in reportedInstances, i.e. a file name may be reported
         // several times if several copies are broken. In case only one file is affected, reported Elements may be
         // provided containing just this file name.
   kFileRecovered =
      8, //< A set of files was corrupted, but a sufficient number of valid copies existed. storage contains the
         // short-name path of the File Storage, reported Elements contains the list of affected file names,
         // reportedInstances contains the indices of the affected File Storage or file copies. In general, the nth file
         // name in reportedElements corresponds to the nth index in reportedInstances, i.e. a file name may be reported
         // several times if several copies are broken. In case only one file is affected, reported Elements may be
         // provided containing just this file name.
};

// SWS_PER_00433
/**
 * @brief Register a recovery reporting callback with Persistency.
 *
 * This callback can be used in safety-aware applications to detect actions of the Persistency that are related to the
 * correctness of the persisted data and the reliability of the storage.
 *
 * @param[in] recoveryReportCallback The callback function to be called by Persistency to report errors in the stored
 * data that were corrected using the available redundancy. The function will be called with the shortName path of the
 * affected Key-Value Storage or File Storage in storage and information on what has been corrected, placed in the
 * parameters recoveryReportKind, reported Elements, and reportedInstances.
 */
void RegisterRecoveryReportCallback(
   std::function<void(const ara::core::InstanceSpecifier& storage,
                      ara::per::Recovery ReportKind recoveryReportKind,
                      ara::core::Vector<ara::core::String> reportedElements,
                      ara::core::Vector<std::uint8_t> reported Instances)> recoveryReportCallback) noexcept;

} // namespace per
} // namespace ara
