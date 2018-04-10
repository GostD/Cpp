#include "any.h"

utils::bad_any_cast::bad_any_cast(std::string type1, std::string type2)
    : exc_str("Wrong cast from " + type1 + " to " + type2)
{}
const char* utils::bad_any_cast::what() const throw()
{
    return exc_str.c_str();
}

utils::any::any(const any& other)
    : elem(other.elem->get_base())
{}

utils::any::~any()
{
    delete elem;
}

utils::any& utils::any::operator=(any other)
{
    swap(*this, other);
    return *this;
}

bool utils::any::empty()
{
    return !elem;
}