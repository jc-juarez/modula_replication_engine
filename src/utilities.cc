#include <stdexcept>

//
// Throws an standard exception with the specified string.
//
inline
void
throw_exception(
    const std::string&& p_string)
{
    throw std::runtime_error(p_string.c_str());
}