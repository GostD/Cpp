#include <iostream>
using namespace std;

template<class T>
struct wrapper
{
    explicit wrapper(T &&value)
        : val(std::forward<T>(value))
    {
    	cout << "constructor" << endl;
    }
 
    wrapper(const wrapper &) = delete;
    wrapper &operator=(const wrapper &) = delete;
 
    wrapper(wrapper &&other) noexcept
    {
        check_state();
        swap(other.val, val);
        other.valid = false;
 
        cout << "move constructor" << endl;
    }
 
    T& value()
    {
    	return val;
    }
 
    T value() const
    {
    	return val;
    }
 
private:
    T val;
    bool valid = true;
 
    void check_state()
    {
        if (!valid) throw 42;
    }
};