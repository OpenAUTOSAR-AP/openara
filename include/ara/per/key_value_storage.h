/**
 * \file key_value_storage.h
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
// SWS_PER_00052
/**
 * \brief Opens a key-value storage.
 *
 * \param[in] kvs   The shortName path of a PortPrototype typed by a
 *                  PersistencyKeyValueDatabaseInterface.
 * \return ara::core::Result<SharedHandle<KeyValueStorage>>     A Result, containing a SharedHandle, or one of the
 *                                                              errors defined for Persistency in PerErrc.
 * \note
 * \thread safety reentrant
 */
ara::core::Result<SharedHandle<KeyValueStorage>> OpenKeyValueStorage(ara::core::InstanceSpecifier& kvs) noexcept;

// SWS_PER_00333
/**
 * \brief Recover an instance of KeyValueStorage.
 *
 * This method allows to recover a key-value storage when the redundancy checks fail. It will fail
 * with a kResourceBusyError when the key-value storage is currently open.
 *
 * This method does a best-effort recovery of all keys. After recovery, keys might show outdated
 * or initial value, or might be lost.
 *
 * \param[in] kvs   The shortName path of a PortPrototype typed by a
 *                  PersistencyKeyValueDatabaseInterface.
 * \return ara::core::Result<void>  A Result, being either empty or containing one of
 *                                  the errors defined for Persistency in PerErrc.
 * \note
 * \thread safety reentrant
 */
ara::core::Result<void> RecoverKeyValueStorage(ara::core::InstanceSpecifier& kvs) noexcept;

// SWS_PER_00334
/**
 * \brief Resets a Key-Value Storage to the initial state.
 *
 * ResetKeyValueStorage allows to reset a Key-Value Storage to the initial state, containing only key-value pairs which
 * were deployed from the manifest, with their initial values. Afterwards, the Key-Value Storage will appear as if it
 * was newly installed from the current manifest.
 *
 * It will fail with kResourceBusy when the Key-Value Storage is currently open, or when it is modified by a call from
 * another thread to UpdatePersistency, ResetPersistency, RecoverKey ValueStorage, or ResetKeyValueStorage.
 *
 * \param[in] kvs   The shortName path of a PortPrototype typed by a PersistencyKeyValueStorageInterface.
 * \return ara::core::Result<void>  A Result of void. In case of an error, it contains any of the errors defined below,
 * or a vendor specific error.
 */
ara::core::Result<void> ResetKeyValueStorage(ara::core::InstanceSpecifier& kvs) noexcept;

// SWS_PER_00405
/**
 * \brief Returns the space in bytes currently occupied by a Key-Value Storage.
 *
 * The returned size includes all meta data and the space used for redundancy and backups.
 *
 * The returned size is only guaranteed to be accurate if the Key-Value Storage is not opened and no other operation on
 * the Key-Value Storage takes place at the same time.
 *
 * \param[in] kvs   The shortName path of a PortPrototype typed by a
 *                  PersistencyKeyValueDatabaseInterface.
 * \return ara::core::Result<uint64_t> A Result containing the occupied space in bytes. In case of an error, it contains
 * any of the errors defined below, or a vendor specific error.
 *
 * \thread safety reentrant
 */
ara::core::Result<uint64_t> GetCurrentKeyValueStorageSize(ara::core::InstanceSpecifier& kvs) noexcept;

// SWS_PER_00339
/**
 * \brief The key-value storage contains a set of keys with associated values. .
 *
 * \note
 */
class KeyValueStorage final
{
    // SWS_PER_00459
    /**
     * @brief The default constructor for KeyValueStorage shall not be used.
     */
    KeyValueStorage()                                         = delete;

    // SWS_PER_00322
    /**
     * \brief The move constructor for KeyValueStorage shall not be used.
     */
    KeyValueStorage(KeyValueStorage&& kvs)                    = delete;

    // SWS_PER_00324
    /**
     * \brief The copy constructor for KeyValueStorage shall not be used.
     */
    KeyValueStorage(const KeyValueStorage&)                   = delete;

    // SWS_PER_00323
    /**
     * \brief The move assignment operator for KeyValueStorage shall not be used.
     */
    KeyValueStorage& operator=(KeyValueStorage&& kvs) &       = delete;

    // SWS_PER_00325
    /**
     * \brief The copy assignment operator for KeyValueStorage shall not be used.
     */
    KeyValKeyValueStorage& operator=(const KeyValue Storage&) = delete;

    // SWS_PER_00050
    /**
     * \brief Destructor for KeyValueStorage.
     */
    ~KeyValueStorage() noexcept;

    // SWS_PER_00042
    /**
     * \brief Returns a list of all currently available keys of the KeyValueStorage.
     *
     * \return ara::core::Result<ara::core::Vector<ara::core::String>>  A Result, containing a list of available keys,
     * or one of the errors defined for Persistency in PerErrc. \note \thread safety reentrant
     */
    ara::core::Result<ara::core::Vector<ara::core::String>> GetAllKeys() const noexcept;

    // SWS_PER_00043
    /**
     * \brief Checks if a key exists in the KeyValueStorage.
     *
     * \param[in] key   The key that shall be checked.
     * \return ara::core::Result<bool>  A Result containing true if the key could be located or false if it couldn’t. In
     * case of an error, it contains any of the errors defined below, or a vendor specific error.
     */
    ara::core::Result<bool> KeyExists(ara::core::StringView key) const noexcept;

    // SWS_PER_00554
    /**
     * @brief Returns the size (in bytes) of the value assigned to a key of this Key-Value Storage.
     *
     * GetCurrentValueSize may be delayed by an ongoing call from another thread to RemoveAll Keys or
     * DiscardPendingChanges, or to SetValue, RemoveKey, RecoverKey, or ResetKey for the same key-value pair.
     *
     * @param key The key to look up.
     * @return ara::core::Result<std::uint64_t> A Result containing the size of the value in bytes. In case of an error,
     * it contains any of the errors defined below, or a vendor specific error.
     */
    ara::core::Result<std::uint64_t> GetCurrent ValueSize(ara::core::StringView key) const noexcept;

    // SWS_PER_00332
    /**
     * \brief Returns the value assigned to a key of the KeyValueStorage.
     *
     * \tparam T    The type of the value that shall be retrieved.
     * \param[in] key   The key to look up.
     * \return ara::core::Result<T>     A Result, being either the retrieved value or
     *                                  containing one of the errors defined for Persistency
     *                                  in PerErrc.
     * \note
     * \thread safety reentrant
     */
    template <class T>
    ara::core::Result<T> GetValue(ara::core::StringView key) const noexcept;

    // SWS_PER_00044
    /**
     * @brief Returns the value assigned to a key of this KeyValueStorage.
     *
     * This method should only be used to access very large values repeatedly.
     *
     * GetValue may be delayed by an ongoing call from another thread to RemoveAllKeys or Discard PendingChanges, or to
     * SetValue, RemoveKey, RecoverKey, or ResetKey for the same key-value pair.
     *
     * @tparam T The type of the value that shall be retrieved.
     * @param[in] key The key to look up.
     * @param[out] value The retrieved value.
     * @return ara::core::Result<void> A Result of void. In case of an error, it contains any of the errors defined
     * below, or a vendor specific error.
     */
    template <class T>
    ara::core::Result<void> GetValue(ara::core::StringView key, T& value) const noexcept;

    // SWS_PER_00046
    /**
     * \brief Stores a key in the KeyValueStorage. If a value already exists, it is overwritten, independent of
     *  the stored data type.
     *
     * \tparam T    The type of the value that shall be set.
     * \param[in] key   The key to assign the value to.
     * \param[in] value The value to store.
     * \return ara::core::Result<void>  A Result, being empty or containing one of the
     *                                  errors defined for Persistency in PerErrc.
     * \note
     * \thread safety reentrant
     */
    template <class T>
    ara::core::Result<void> SetValue(ara::core::StringView key, const T& value) noexcept;

    // SWS_PER_00047
    /**
     * \brief Removes a key and the associated value from the KeyValueStorage.
     *
     * \param[in] key   The key to be removed.
     * \return ara::core::Result<void>  A Result, being empty or containing one of the
     *                                  errors defined for Persistency in PerErrc.
     * \note
     * \thread safety reentrant
     */
    ara::core::Result<void> RemoveKey(ara::core::StringView key) noexcept;

    // SWS_PER_00427
    /**
     * @brief Recovers a single key-value pair of this Key Value Storage.
     *
     * This method allows to recover a single key-value pair when the redundancy checks fail.
     *
     * This method does a best-effort recovery of the key-value pair. After recovery, the key-value pair might contain
     * outdated or initial content, or might be lost.
     *
     * RecoverKey may be delayed by an ongoing call from another thread to RemoveAllKeys, SyncTo Storage, or
     * DiscardPendingChanges, or to SetValue, GetValue, GetCurrentValueSize, Remove Key, RecoverKey, or ResetKey for the
     * same key-value pair.
     *
     * @param key The key to be recovered.
     * @return ara::core::Result<void> A Result of void. In case of an error, it contains any of the errors defined
     * below, or a vendor specific error.
     */
    ara::core::Result<void> aRecoverKey(ara::core::StringView key) noexcept;

    // SWS_PER_00426
    /**
     * @brief Resets a key of this Key-Value Storage to its initial value.
     *
     * ResetKey allows to reset a single key to its initial value. If the key is currently not available in the
     * Key-Value Storage, it is re-created. Afterwards, the key-value pair will appear in both cases as if it was newly
     * installed from the current manifest.
     *
     * ResetKey will fail with kInitValueNotAvailable when neither design nor deployment define an initial value for the
     * key.
     *
     * ResetKey may be delayed by an ongoing call from another thread to RemoveAllKeys, SyncTo Storage, or
     * DiscardPendingChanges, or to SetValue, GetValue, GetCurrentValueSize, Remove Key, RecoverKey, or ResetKey for the
     * same key-value pair.
     *
     * @param key The key to be reset.
     * @return ara::core::Result<void> A Result of void. In case of an error, it contains any of the errors defined
     * below, or a vendor specific error.
     */
    ara::core::Result<void> ResetKey(ara::core::StringView key) noexcept;

    // SWS_PER_00048
    /**
     * \brief Removes all keys and associated values from the KeyValueStorage.
     *
     * \return ara::core::Result<void>  A Result, being empty or containing one of the
     *                                  errors defined for Persistency in PerErrc.
     * \note
     * \thread safety reentrant
     */
    ara::core::Result<void> RemoveAllKey() noexcept;

    // SWS_PER_00049
    /**
     * \brief Triggers flushing of key-value pairs to the physical storage of the KeyValueStorage.
     *
     * \return ara::core::Result<void>  A Result, being either empty or containing one of
     *                                  the errors defined for Persistency in PerErrc.
     * \note
     * \thread safety reentrant
     */
    ara::core::Result<void> SyncToStorage() noexcept;

    // SWS_PER_00365
    /**
     * \brief Removes all pending changes to the KeyValueStorage since the last call to SyncToStorage() or
     * since the KeyValueStorage was opened using OpenKeyValueStorage().
     *
     * \return ara::core::Result<void>  A Result, being either empty or containing one of
     *                                  the errors defined for Persistency in PerErrc.
     * \note
     * \thread safety reentrant
     */
    ara::core::Result<void> DiscardPendingChanges() noexcept;
};
} // namespace per
} // namespace ara
