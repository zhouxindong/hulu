#pragma once
#ifndef _HULU_PARSE_INI_PARSER_H_
#define _HULU_PARSE_INI_PARSER_H_

#include "../gvals.h"

#include <string>
#include <vector>

_HULU_BEGIN

/**
 * @brief INI file parser interface
 */
class Ini_parser
{
public:
	virtual ~Ini_parser() noexcept
	{
	}

public:
	/**
	 * @brief get all sections
	 */
	virtual std::vector<std::string> sections() = 0;

	/**
	 * @brief get the value of key
	 */
	virtual const std::pair<bool, std::string> string_value(const char* sec_name, const char* key_name) = 0;
	virtual const std::pair<bool, bool> bool_value(const char* sec_name, const char* key_name) = 0;
	virtual const std::pair<bool, int> int_value(const char* sec_name, const char* key_name) = 0;
	virtual const std::pair<bool, double> double_value(const char* sec_name, const char* key_name) = 0;

public:
	bool ready() const noexcept
	{
		return ready_;
	}

protected:
	bool ready_{ false };
};

_HULU_END

#endif // _HULU_PARSE_INI_PARSER_H_