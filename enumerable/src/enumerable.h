#pragma once
#include <vector>


template<class T>
struct enumerable
{
    enumerable(std::vector<T>&& vec) 
        : vec(std::forward<std::vector<T>>(vec))
    {}
    enumerable(std::vector<T>& vec) 
        : vec(std::forward<std::vector<T>>(vec))
    {}
    enumerable where(std::function<bool(T const&)> fun)
    {
        std::vector<T> res;
        size_t len = vec.size();
        for (size_t i = 0; i < len; ++i)
        {
            if (fun(vec[i]))
            {
                res.push_back(std::move(vec[i]));
            }

        }
        return enumerable<T>(res);
        
    }
    template<class V>
    enumerable<V> select(std::function<V(T const&)> transform)
    {
        std::vector<V> res;
        size_t len = vec.size();
        for (size_t i = 0; i < len; ++i)
        {
            // T elem = std::move(vec[i]);
            res.push_back(std::move(transform(vec[i])));

        }
        return enumerable<V>(res);
    }
    size_t count()
    {
        return vec.size();
    }
    size_t count(std::function<bool(T const&)> predicate)
    {
        size_t len = vec.size();
        size_t res = 0;
        for (size_t i = 0; i < len; ++i)
        {
            if (predicate(vec[i]))
            {
                res++;
            }
        }
        return res;
    }
    bool any()
    {
        return vec.size() > 0;
    }
    bool any(std::function<bool(T const&)> predicate)
    {
        size_t len = vec.size();
        for (size_t i = 0; i < len; ++i)
        {
            if (predicate(vec[i]))
            {
                return true;
            }
        }
        return false;
    }

    std::vector<T> toVector()
    {
        return std::move(vec);
    }
private:
    std::vector<T> vec;
};



template<class T>
enumerable<typename T::value_type> from(T && vec)
{
    return enumerable<typename T::value_type>(std::forward<T>(vec));
}
template<class T>
enumerable<typename T::value_type> from(T & vec)
{
    return enumerable<typename T::value_type>(std::forward<T>(vec));
}