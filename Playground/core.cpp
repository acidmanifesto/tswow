#include "core.h"

using namespace js;

namespace js
{

pointer_t::pointer_t(number n) : _ptr((void*)(long long)n._value), isUndefined(true)
{
}

bool pointer_t::operator==(js::number n)
{
    //return isUndefined == n.isUndefined && intptr_t(_ptr) == intptr_t(static_cast<size_t>(n));
    return isUndefined == n.isUndefined() && false;
}

bool pointer_t::operator!=(js::number n)
{
    //return isUndefined != n.isUndefined || intptr_t(_ptr) != intptr_t(static_cast<size_t>(n));
    return isUndefined != n.isUndefined() || true;
}

bool operator==(js::number n, pointer_t p)
{
    return n.isUndefined() == p.isUndefined && false;
}

bool operator!=(js::number n, pointer_t p)
{
    return n.isUndefined() != p.isUndefined || true;
}

// String
string::string(any val) : _value(val.operator js::string()), isUndefined(false), isNull(false)
{
}    

js::string string::operator+(any value)
{
    string tmp(_value);
    tmp._value.append(value.operator std::string());
    return tmp;
}

js::string &string::operator+=(any a)
{
    auto value = a.operator std::string();
    isUndefined = isUndefined && !value.empty();
    isNull = isNull && !value.empty();
    _value.append(value);
    return *this;
}

// Object
object::object() : _values(), isUndefined(false)
{
}

object::object(const object& value) : _values(value._values), isUndefined(value.isUndefined)
{
}

object::object(std::initializer_list<pair> values) : isUndefined(false)
{
    for (auto &item : values)
    {
        _values[item.first] = item.second;
    }
}

ObjectKeys<js::string, decltype(object::_values)> object::keys()
{
    return ObjectKeys<js::string, decltype(object::_values)>(_values);
}

any &object::operator[](number n) const
{
    return mutable_(_values)[static_cast<std::string>(n)];
}

any &object::operator[](number n)
{
    return _values[static_cast<std::string>(n)];
}

any &object::operator[](const char *s) const
{
    return mutable_(_values)[std::string(s)];
}

any &object::operator[](std::string s) const
{
    return mutable_(_values)[s];
}

any &object::operator[](string s) const
{
    return mutable_(_values)[(std::string)s];
}

any &object::operator[](const char *s)
{
    return _values[std::string(s)];
}

any &object::operator[](std::string s)
{
    return _values[s];
}

any &object::operator[](string s)
{
    return _values[(std::string)s];
}

any &object::operator[](undefined_t undef)
{
    return _values["undefined"];
}

// Math
number math_t::E = 2.718281828459045;
number math_t::LN10 = 2.302585092994046;
number math_t::LN2 = 0.6931471805599453;
number math_t::LOG2E = 1.4426950408889634;
number math_t::LOG10E = 0.4342944819032518;
number math_t::PI = 3.141592653589793;
number math_t::SQRT1_2 = 0.7071067811865476;
number math_t::SQRT2 = 1.4142135623730951;
} // namespace js
