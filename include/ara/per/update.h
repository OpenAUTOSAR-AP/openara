/**
 * @file update.h
 * @author vin (vin@misday.com)
 * @brief
 * @version 0.1
 * @date 2023-03-29
 *
 * @copyright Copyright (c) OpenAUTOSAR-AP 2023
 */

// R22-11

#pragma once

#include "ara/core/instance_specifier.h"
#include "ara/core/result.h"

namespace ara
{
namespace per
{
// SWS_PER_00356
/**
 * @brief Registers an application data update callback with Persistency.
 *
 * The provided callback function will be called by Persistency if an update of stored application
 * data might be necessary. This decision is based on the Executable versions.
 *
 * The version that last accessed Persistency is provided as an argument to the callback, as well
 * as the InstanceSpecifier referring to the updated Key-Value Storage or File Storage. Based on
 * this information, the application can decide which updates are actually necessary, e.g. a
 * migration from any older version could be supported, with different steps required for each of
 * these.
 *
 * The provided function will be called from the context of UpdatePersistency(), OpenKeyValue
 * Storage(), or OpenFileStorage().
 *
 * @param appDataUpdateCallback The callback function to be called by Persistency
 * after an update of persistent data took place. The
 * function will be called with the shortName path of an
 * updated Key-Value Storage or File Storage, and with
 * the Executable version with which the Persistency
 * was last accessed.
 */
void RegisterApplicationDataUpdateCallback(
   std::function<void(const ara::core::InstanceSpecifier& storage, ara::core::String version)>
      appDataUpdateCallback) noexcept;

// SWS_PER_00357
/**
 * @brief Updates all Persistency Key-Value Storages and File Storages after a new manifest was installed.
 *
 * This method can be used to update the persistent data of the application during verification phase.
 *
 * @return ara::core::Result<void> A Result of void. In case of an error, it contains any
 * of the errors defined below, or a vendor specific error.
 */
ara::core::Result<void> UpdatePersistency() noexcept;

// SWS_PER_00358
/**
 * @brief Resets all Key-Value Storages and File Storages by entirely removing their content.
 *
 * The Key-Value Storages and File Storages will be re-created when OpenFileStorage or Open
 * KeyValueStorage is called next time.
 *
 * @return ara::core::Result<void> A Result of void. In case of an error, it contains any
 * of the errors defined below, or a vendor specific error.
 */
ara::core::Result<void> ResetPersistency() noexcept;

} // namespace per
} // namespace ara
