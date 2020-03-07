#ifndef RESULT_H
#define RESULT_H

namespace Result
{
struct nullresult_t
{

};

inline constexpr nullresult_t nullresult {};

template <typename T>
class Result
{
    public:
        Result(int code, T value)
            : m_code(code), m_value(value)
        {
        }

        Result(int code, nullresult_t value)
            : m_code(code)
        {
        }

        bool HasValue() const
        {
            return m_code >= 0;
        }

        T Value() const
        {
            return m_value;
        }

        constexpr bool operator!() const
        {
            return m_code < 0;
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

    private:
        int m_code;
        T m_value;
};
};

#endif // RESULT_H