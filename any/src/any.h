#pragma once
#include <string>
#include <typeinfo>


namespace utils
{
    struct bad_any_cast
        : std::exception
    {
        bad_any_cast(std::string type1, std::string type2);
        const char* what() const throw();
        std::string exc_str;
    };
    struct any
    {
        any()
            : elem(nullptr)
        {}
        template<typename T>
        any(T value)
            : elem(new hold<T>(value))
        {}
        any(const any& other);
        ~any();
        any& operator=(any other);
        bool empty();

        template<typename U>
        friend U* any_cast(any* src)
        {
            if (typeid(U) == src->elem->type_info())
            {
                return &static_cast<hold<U>*>(src->elem)->value;
            }
            else
            {
                return nullptr;
            }
        }
       
        template<typename U>
        friend const U* any_cast(const any* src)
        {
            if (typeid(U) == src->elem->type_info())
            {
                return &static_cast<hold<U>*>(src->elem)->value;
            }
            else
            {
                return nullptr;
            }
        }
        template<typename U>
        friend U any_cast(any& src)
        {
            if (typeid(U) == src.elem->type_info())
            {
                typedef typename std::remove_reference<U>::type no_ref;
                return static_cast<hold<no_ref>*>(src.elem)->value;
            }
            else
            {
                throw bad_any_cast(typeid(U).name(), src.elem->type_info().name());
            }
        }
        template<typename U>
        friend const U any_cast(const any& src)
        {
            if (typeid(U) == src.elem->type_info())
            {
                typedef typename std::remove_reference<U>::type no_ref;
                return static_cast<hold<no_ref>*>(src.elem)->value;
            }
            else
            {
                throw bad_any_cast(typeid(U).name(), src.elem->type_info().name());
            }
        }
        friend void swap(any& left, any& right)
        {
            std::swap(left.elem, right.elem);
        }

    private:
        struct base
        {
            virtual ~base() = default;
            virtual const std::type_info& type_info() const = 0;
            virtual base* get_base() = 0;
        };
        template<typename T>
        struct hold
            : base
        {
            hold(T value)
                : value(value)
            {}
            const std::type_info& type_info() const
            {
                return typeid(value);
            }
            base* get_base()
            {
                return new hold<T>(value);
            }
            T value;
        };
        base* elem;
    };
}