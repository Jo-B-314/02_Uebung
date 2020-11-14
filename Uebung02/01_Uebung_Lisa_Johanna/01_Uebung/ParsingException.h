#ifndef BIOINFOI_PARSING_EXCEPTION_H
#define BIOINFOI_PARSING_EXCEPTION_H

#include <exception>
#include <string>

class ParsingException : public std::exception
{
  public:
	ParsingException(const std::string& msg);
	const char* what() const noexcept override;

  private:
	std::string msg_;
};

#endif //BIOINFOI_PARSING_EXCEPTION_H

