/**
 * \file promise.h
 * \author Vincent WANG (vin@misday.com)
 * \brief 
 * \version 0.1
 * \date 2020-12-04
 * 
 * \copyright Copyright (c) 2020
 * 
 */
// R19-11

#pragma once

namespace ara
{
namespace core
{
    // SWS_CORE_06340
    /**
     * \brief Specialization of class Promise for "void" values.
     * 
     * \tparam E    the type of error
     */
    template<typename E>
    class Promise<void, E> final
    {
        // SWS_CORE_06341
        /**
         * \brief Default constructor.
         * This function shall behave the same as the corresponding std::promise function.
         * 
         */
        Promise();

        // SWS_CORE_06342
        /**
         * \brief Move constructor.
         * This function shall behave the same as the corresponding std::promise function.
         * 
         * \param[in] other     the other instance
         */
        Promise(Promise &&other) noexcept;

        // SWS_CORE_06350
        /**
         * \brief Copy constructor shall be disabled.
         * 
         */
        Promise(Promise const &) = delete;

        // SWS_CORE_06349
        /**
         * \brief Destructor for Promise objects.
         * This function shall behave the same as the corresponding std::promise function.
         * 
         */
        ~Promise();

        // SWS_CORE_06343
        /**
         * \brief Move assignment.
         * This function shall behave the same as the corresponding std::promise function.
         * 
         * \param[in] other     the other instance
         * \return Promise&     *this
         */
        Promise& operator=(Promise &&other) noexcept;

        // SWS_CORE_06351
        /**
         * \brief Copy assignment operator shall be disabled.
         * 
         * \return Promise& 
         */
        Promise& operator=(Promise const &) = delete;

        // SWS_CORE_06352
        /**
         * \brief Swap the contents of this instance with another one’s.
         * This function shall behave the same as the corresponding std::promise function.
         * 
         * \param[in] other     the other instance
         */
        void swap(Promise &other) noexcept;

        // SWS_CORE_06344
        /**
         * \brief Return the associated Future.
         * 
         * The returned Future is set as soon as this Promise receives the result or an error. This method
         * must only be called once as it is not allowed to have multiple Futures per Promise.
         * 
         * \return Future<void, E>  a Future
         */
        Future<void, E> get_future();

        // SWS_CORE_06345
        /**
         * \brief Make the shared state ready.
         * 
         */
        void set_value();

        // SWS_CORE_06353
        /**
         * \brief Move an error into the shared state and make the state ready.
         * 
         * \param[in] error     the error to store
         */
        void SetError(E &&error);

        // SWS_CORE_06354
        /**
         * \brief Copy an error into the shared state and make the state ready.
         * 
         * \param[in] error     the error to store
         */
        void SetError(E const &error);
    };
} // namespace core
} // namespace ara
