#include "stdafx.h"
#include "CppUnitTest.h"
#include "parse/inier.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace hulu;
using namespace std;

namespace parse
{
	TEST_CLASS(Ini_reader_test)
	{
	public:

		TEST_METHOD(Ini_reader_sections_test)
		{
			Ini_reader reader("rdv2_config.ini");
			Assert::IsTrue(reader.ready());

			auto sections = reader.sections();
			Assert::IsTrue(2 == sections.size());
			Assert::IsTrue(std::string("VDR") == sections[0]);
			Assert::IsTrue(std::string("cmd") == sections[1]);
		}

		TEST_METHOD(Ini_reader_value_test)
		{
			Ini_reader reader("rdv2_config.ini");
			Assert::IsTrue(reader.ready());

			const char* sec1 = "VDR";
			const char* sec2 = "cmd";

			Assert::IsTrue(174 == reader.int_value(sec1, "VDR_region").second);
			Assert::IsTrue(1811 == reader.int_value(sec1, "VDR_id").second);
			Assert::IsTrue(std::string("224.0.0.155") == reader.string_value(sec1, "VDR_group_ip").second);
			Assert::IsTrue(9000 == reader.int_value(sec1, "VDR_group_port").second);
			Assert::IsTrue(std::string("localhost") == reader.string_value(sec1, "VDR_local_ip").second);
			Assert::IsTrue(9078 == reader.int_value(sec1, "VDR_local_port").second);

			Assert::IsTrue(std::string("运行控制指令") == reader.string_value(sec2, "cmd_name").second);
			Assert::IsTrue(std::string("仿真步长") == reader.string_value(sec2, "cmd_speed_name").second);
			Assert::IsTrue(800 == reader.int_value(sec2, "cmd_load").second);
			Assert::IsTrue(1000 == reader.int_value(sec2, "cmd_init").second);
			Assert::IsTrue(1100 == reader.int_value(sec2, "cmd_start").second);
			Assert::IsTrue(1200 == reader.int_value(sec2, "cmd_freeze").second);
			Assert::IsTrue(1300 == reader.int_value(sec2, "cmd_unfreeze").second);
			Assert::IsTrue(1400 == reader.int_value(sec2, "cmd_set_speed").second);
			Assert::IsTrue(2000 == reader.int_value(sec2, "cmd_finish").second);
			Assert::IsTrue(reader.bool_value(sec2, "cmd_enable").second);
			Assert::IsTrue(993.23 == reader.double_value(sec2, "cmd_interval").second);
		}
	};
}
