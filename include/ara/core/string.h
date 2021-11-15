/**
 * \file string.h
 * \author Vincent WANG (vin@misday.com)
 * \brief 
 * \version 0.1
 * \date 2021-11-12
 * 
 * \copyright Copyright (c) 2021
 * 
 */
// R19-11

#pragma once

#include "string_view.h"

namespace ara
{
namespace core
{
    // SWS_CORE_03000
    template <typename Allocator = IMPLEMENTATION_DEFINED>
    class BasicString
    {
        using size_type = std::size_t;
        using const_iterator = implementation_defined;

        // SWS_CORE_03301
        operator StringView() const noexcept;

        // SWS_CORE_03302
        explicit BasicString(StringView sv);

        // SWS_CORE_03303
        typename <typename T>
        BasicString(T const& t, size_type pos, size_type n);

        // SWS_CORE_03304
        BasicString& operator=(StringView sv);

        // SWS_CORE_03305
        BasicString& assign(StringView sv);

        // SWS_CORE_03306
        template <typename T>
        BasicString& assign(T const& t, size_type pos, size_type n = npos);

        // SWS_CORE_03307
        BasicString& operator+= (StringView sv);

        // SWS_CORE_03308
        BasicString& append(StringView sv);

        // SWS_CORE_03309
        template <typename T>
        BasicString& append(T const& t, size_type pos, size_type n = npos);

        // SWS_CORE_03310
        BasicString& insert(size_type pos, StringView sv);

        // SWS_CORE_03311
        template <typename T>
        BasicString& insert(size_type pos1, T const& t, size_type pos2, size_type n = npos);

        // SWS_CORE_03312
        BasicString& replace(size_type pos1, size_type n1, StringView sv);

        // SWS_CORE_03313
        template <typename T>
        BasicString& replace(size_type pos1, size_type n1, T const& t, size_type pos2, size_type n2 = npos);

        // SWS_CORE_03314
        BasicString& replace(const_iterator i1, const_iterator i2, StringView sv);

        // SWS_CORE_03315
        size_type find(StringView sv, size_type pos = 0) const noexcept;

        // SWS_CORE_03316
        size_type rfind(StringView sv, size_type pos = npos) const noexcept;

        // SWS_CORE_03317
        size_type find_first_of(StringView sv, size_type pos = 0) const noexcept;

        // SWS_CORE_03318
        size_type find_last_of(StringView sv, size_type pos = npos) const noexcept;

        // SWS_CORE_03319
        size_type find_first_not_of(StringView sv, size_type pos = 0) const noexcept;

        // SWS_CORE_03320
        size_type find_last_not_of(StringView sv, size_type pos = npos) const noexcept;

        // SWS_CORE_03321
        int compare(StringView sv) const noexcept;

        // SWS_CORE_03322
        int compare(size_type pos1, size_type n1, StringView sv) const;

        // SWS_CORE_03323
        template <typename T>
        int compare(size_type pos1, size_type n1, T const& t, size_type pos2, size_type n2 = npos) const;

        // SWS_CORE_03296
        template <typename Allocator>
        void swap(BasicString<Allocator>& lhs, BasicString<Allocator>& rhs);

    };

    // SWS_CORE_03001
    using String = BasicString<IMPLEMENTATION_DEFINED>;
}
}
