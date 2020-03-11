#pragma once

#ifndef _HULU_PARSE_XML_PARSER_H_
#define _HULU_PARSE_XML_PARSER_H_

#include "../gvals.h"

#include <vector>
#include <utility>

_HULU_BEGIN

/**
* @brief XML parser interface
* @param _Element: element Type stored in vector
*/
template <typename _Element>
class Xml_parser
{
public:
	typedef Xml_parser<_Element> Type;
	typedef _Element Element_type;

public:
	virtual ~Xml_parser() noexcept {}

public:
	/**
	 * @brief parse xml from a text
	 */
	virtual bool parse_text(char const* xml_text) = 0;

	/**
	 * @brief get the root element of XML
	 */
	virtual Element_type root() = 0;

public:	// get elements			
	/**
	 * @brief get all elements with the special ele_name
	 * @param <ele_name>
	 */
	virtual std::vector<Element_type> all(char const* ele_name) = 0;

	/**
	 * @brief get all elements with the ele_name and its parent's ele_name
	 * @param <parent>
				<ele_name>
	 */
	virtual std::vector<Element_type> all(char const* ele_name, char const* parent) = 0;

	/**
	 * @breif get all elements with the ele_name and its parent' ele_name and its parent' parent' ele_name
	 * @param <pparent>
				<parent>
				   <ele_name>
	 */
	virtual std::vector<Element_type> all(char const* ele_name, char const* parent, char const* pparent) = 0;

	/**
	 * @brief get all the directly childs for special element
	 * @param child_name: only the childs with exact ele_name, nullptr no consider the child's name
	 */
	virtual std::vector<Element_type> childs(Element_type ele, char const* child_name = nullptr) = 0;

public:	// get the data of a element
	/**
	 * @brief get the text of element
	 */
	virtual char const* text(Element_type ele) = 0;

	/**
	 * @brief get the attribute value of element
	 */
	virtual std::pair<bool, int32_t> int32_attribute(Element_type ele, const char* attr_name) = 0;
	virtual std::pair<bool, std::string> string_attribute(Element_type ele, const char* attr_name) = 0;
	virtual std::pair<bool, bool> bool_attribute(Element_type ele, const char* attr_name) = 0;
	virtual std::pair<bool, double> double_attribute(Element_type ele, const char* attr_name) = 0;

public:
	bool ready() const noexcept { return ready_; }

protected:
	bool ready_{ false };
};

_HULU_END

#endif // _HULU_PARSE_XML_PARSER_H_