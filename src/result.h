
/*
MIT License

Copyright (c) 2020 stefanmitic

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef RESULT_H
#define RESULT_H

namespace Result
{
struct nullresult_t
{

};

inline constexpr nullresult_t nullresult {};

template<typename C, typename T, typename = void>
class ResultBase
{
    public:
        virtual bool HasValue() const = 0;

        virtual constexpr bool operator!() const = 0;

        // General member functions
        T Value() const
        {
            return m_value;
        }

        constexpr const T* operator->() const
        {
            return &m_value;
        }
        constexpr T* operator->()
        {
            return &m_value;
        }
        constexpr const T& operator*() const&
        {
            return m_value;
        }
        constexpr T& operator*()&
        {
            return m_value;
        }
        constexpr const T&& operator*() const&&
        {
            return m_value;
        }
        constexpr T&& operator*()&&
        {
            return m_value;
        }

    protected:
        C m_code;
        T m_value;
};

// Enum specialization
template <typename C, typename T>
class Result : public ResultBase<C, T, typename std::enable_if_t<std::is_enum_v<C>>>
{
    public:
        Result(C code, T value)
        {
            this->m_code = code;
            this->m_value = value;
        }

        Result(C code, nullresult_t value)
        {
            this->m_code = code;
        }

        bool HasValue() const
        {
            return this->m_code >= 0;
        }

        constexpr bool operator!() const
        {
            return this->m_code < 0;
        }
};

// Int specilaization
template<typename T>
class Result<int, T> : public ResultBase<int, T>
{
    public:
        Result(int code, T value)
        {
            this->m_code = code;
            this->m_value = value;
        }

        Result(int code, nullresult_t value)
        {
            this->m_code = code;
        }

        bool HasValue() const
        {
            return this->m_code >= 0;
        }

        constexpr bool operator!() const
        {
            return this->m_code < 0;
        }
};

// Bool specilaization
template<typename T>
class Result<bool, T> : public ResultBase<bool, T>
{
    public:
        Result(bool code, T value)
        {
            this->m_code = code;
            this->m_value = value;
        }

        Result(bool code, nullresult_t value)
        {
            this->m_code = code;
        }

        bool HasValue() const
        {
            return this->m_code;
        }

        constexpr bool operator!() const
        {
            return this->m_code;
        }
};
};

#endif // RESULT_H