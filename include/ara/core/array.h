/**
 * \file array.h
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

namespace ara
{
namespace core
{
    // SWS_CORE_01201
    template <typename T, std::size_t N>
    class Array
    {

    };

    // SWS_CORE_01296
    template <typename T, std::size_t N>
    void swap(Array<T, N>& lhs, Array<T, N>& rhs);
}
}
