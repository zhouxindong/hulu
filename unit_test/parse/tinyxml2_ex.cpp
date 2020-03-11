#include "stdafx.h"
#include "CppUnitTest.h"
#include "parse/tinyxml2_ex.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace hulu;
using namespace std;

namespace parse
{		
	TEST_CLASS(Tinyxml2_test)
	{
	public:
		
		TEST_METHOD(Tinyxml2_ctor_test)
		{
			Xml_parser<XMLElement*>* parser = new Tinyxml2("rdv2_config.xml");
			Assert::IsTrue(parser->ready());
			delete parser;

			parser = new Tinyxml2("book.xml");
			Assert::IsTrue(parser->ready());
			delete parser;

			parser = new Tinyxml2("model.config");
			Assert::IsTrue(parser->ready());
			delete parser;

			parser = new Tinyxml2("noexist.xml");
			Assert::IsFalse(parser->ready());
			delete parser;
		}

		TEST_METHOD(Tinyxml2_root_test)
		{
			Xml_parser<XMLElement*>* parser = new Tinyxml2("rdv2_config.xml");
			Assert::IsTrue(parser->ready());

			auto* root = parser->root();
			Assert::IsTrue(std::string(root->Name()) == std::string("CORE_ID"));
			delete parser;
		}

		TEST_METHOD(Tinyxml2_all_test)
		{
			Xml_parser<XMLElement*>* parser = new Tinyxml2("rdv2_config.xml");
			auto elements = parser->all("ID");
			Assert::IsTrue(elements.size() == 15);
			delete parser;

			parser = new Tinyxml2("book.xml");
			elements = parser->all("book");
			Assert::IsTrue(elements.size() == 6);

			elements = parser->all("nonexists");
			Assert::IsTrue(elements.size() == 0);

			elements = parser->all("book", "root");
			Assert::IsTrue(elements.size() == 1);

			elements = parser->all("book", "section1");
			Assert::IsTrue(elements.size() == 2);

			elements = parser->all("book", "section1", "root");
			Assert::IsTrue(elements.size() == 2);

			elements = parser->all("book", "section2");
			Assert::IsTrue(elements.size() == 1);
			
			elements = parser->all("book", "section22", "section2");
			Assert::IsTrue(elements.size() == 2);

			delete parser;
		}

		TEST_METHOD(Tinyxml2_element_test)
		{
			Xml_parser<XMLElement*>* parser = new Tinyxml2("model.config");

			auto elements = parser->all("CLASS", "CLASS_DECLARE");
			Assert::IsTrue(elements.size() == 2);
			elements = parser->all("DATA", "INPUT_DATA");
			Assert::IsTrue(elements.size() == 4);
			elements = parser->all("DATA", "INNER_DATA");
			Assert::IsTrue(elements.size() == 3);
			elements = parser->all("DATA", "OUTPUT_DATA");
			Assert::IsTrue(elements.size() == 16);

			elements = parser->all("new_element");
			Assert::IsTrue(elements.size() == 1);

			auto ele = elements[0];
			Assert::IsTrue(parser->text(ele) == std::string("new element"));
			Assert::IsTrue(parser->int32_attribute(ele, "AGE").first);
			Assert::IsTrue(parser->int32_attribute(ele, "AGE").second == 99);
			Assert::IsTrue(parser->string_attribute(ele, "NAME").first);
			Assert::IsTrue(parser->string_attribute(ele, "NAME").second == std::string("zzz"));
			Assert::IsTrue(parser->bool_attribute(ele, "MALE").first);
			Assert::IsTrue(parser->bool_attribute(ele, "MALE").second);
			Assert::IsTrue(parser->int32_attribute(ele, "AGE").first);
			Assert::IsTrue(parser->int32_attribute(ele, "AGE").second == 99);
			Assert::IsTrue(parser->double_attribute(ele, "HEIGH").first);
			Assert::IsTrue(parser->double_attribute(ele, "HEIGH").second == 33.233);

			Assert::IsFalse(parser->int32_attribute(ele, "noexist").first);
			Assert::IsFalse(parser->string_attribute(ele, "noexist").first);
			Assert::IsFalse(parser->bool_attribute(ele, "noexist").first);
			Assert::IsFalse(parser->double_attribute(ele, "noexist").first);

			delete parser;
		}
	};
}