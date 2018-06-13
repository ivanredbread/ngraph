/*******************************************************************************
* Copyright 2018 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include <cmath>

#include "ngraph/type/element_type.hpp"

using namespace ngraph;

const element::Type element::boolean(8, false, true, "char");
const element::Type element::f32(32, true, true, "float");
const element::Type element::f64(64, true, true, "double");
const element::Type element::i8(8, false, true, "int8_t");
const element::Type element::i16(16, false, true, "int16_t");
const element::Type element::i32(32, false, true, "int32_t");
const element::Type element::i64(64, false, true, "int64_t");
const element::Type element::u8(8, false, false, "uint8_t");
const element::Type element::u16(16, false, false, "uint16_t");
const element::Type element::u32(32, false, false, "uint32_t");
const element::Type element::u64(64, false, false, "uint64_t");

element::Type::Type()
    : m_bitwidth{0}
    , m_is_real{0}
    , m_is_signed{0}
    , m_cname{}
{
}

element::Type::Type(size_t bitwidth, bool is_real, bool is_signed, const std::string& cname)
    : m_bitwidth{bitwidth}
    , m_is_real{is_real}
    , m_is_signed{is_signed}
    , m_cname{cname}
{
}

const std::string& element::Type::c_type_string() const
{
    return m_cname;
}

bool element::Type::operator==(const element::Type& other) const
{
    return m_bitwidth == other.m_bitwidth && m_is_real == other.m_is_real &&
           m_is_signed == other.m_is_signed && m_cname == other.m_cname;
}

bool element::Type::operator<(const Type& other) const
{
    size_t v1 = m_bitwidth << 2;
    v1 |= (m_is_real ? 2 : 0);
    v1 |= (m_is_signed ? 1 : 0);

    size_t v2 = other.m_bitwidth << 2;
    v2 |= (other.m_is_real ? 2 : 0);
    v2 |= (other.m_is_signed ? 1 : 0);

    return v1 < v2;
}

size_t element::Type::size() const
{
    return std::ceil(static_cast<float>(m_bitwidth) / 8.0f);
}

namespace ngraph
{
    namespace element
    {
        template <>
        const Type& from<char>()
        {
            return boolean;
        }
        template <>
        const Type& from<bool>()
        {
            return boolean;
        }
        template <>
        const Type& from<float>()
        {
            return f32;
        }
        template <>
        const Type& from<double>()
        {
            return f64;
        }
        template <>
        const Type& from<int8_t>()
        {
            return i8;
        }
        template <>
        const Type& from<int16_t>()
        {
            return i16;
        }
        template <>
        const Type& from<int32_t>()
        {
            return i32;
        }
        template <>
        const Type& from<int64_t>()
        {
            return i64;
        }
        template <>
        const Type& from<uint8_t>()
        {
            return u8;
        }
        template <>
        const Type& from<uint16_t>()
        {
            return u16;
        }
        template <>
        const Type& from<uint32_t>()
        {
            return u32;
        }
        template <>
        const Type& from<uint64_t>()
        {
            return u64;
        }
    }
}

element::Type element::from(const std::string& c_type_string)
{
    if (c_type_string == "char")
    {
        return element::Type(8, false, true, "char");
    }
    else if (c_type_string == "float")
    {
        return element::Type(32, true, true, "float");
    }
    else if (c_type_string == "double")
    {
        return element::Type(64, true, true, "double");
    }
    else if (c_type_string == "int8_t")
    {
        return element::Type(8, false, true, "int8_t");
    }
    else if (c_type_string == "int16_t")
    {
        return element::Type(16, false, true, "int16_t");
    }
    else if (c_type_string == "int32_t")
    {
        return element::Type(32, false, true, "int32_t");
    }
    else if (c_type_string == "int64_t")
    {
        return element::Type(64, false, true, "int64_t");
    }
    else if (c_type_string == "uint8_t")
    {
        return element::Type(8, false, false, "uint8_t");
    }
    else if (c_type_string == "uint16_t")
    {
        return element::Type(16, false, false, "uint16_t");
    }
    else if (c_type_string == "uint32_t")
    {
        return element::Type(32, false, false, "uint32_t");
    }
    else if (c_type_string == "uint64_t")
    {
        return element::Type(64, false, false, "uint64_t");
    }
    throw std::runtime_error("unknown C type '" + c_type_string + "' in element::from");
}

std::ostream& element::operator<<(std::ostream& out, const element::Type& obj)
{
    out << "element::Type(" << obj.m_bitwidth << ", " << obj.m_is_real << ", " << obj.m_is_signed
        << ")";
    return out;
}
