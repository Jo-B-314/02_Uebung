#include "ParsingException.h"

ParsingException::ParsingException(const std::string& msg)
    : msg_(msg)
{
}

const char* ParsingException::what() const noexcept { return msg_.c_str(); }
