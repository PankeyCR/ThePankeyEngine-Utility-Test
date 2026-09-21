#pragma once

#include "TestRunner.hpp"
#include "FixedArray.hpp"

#if defined(pankey_Log) && (defined(TestRegistry_Log) || defined(pankey_Global_Log) || defined(pankey_DataStructure_Array_Log))
	#include "Logger_status.hpp"
	#define TestRegistryLog(status,method,mns) pankey_Log(status,"TestRegistry",method,mns)
#else
	#define TestRegistryLog(status,method,mns)
#endif

namespace pankey{

	namespace Utility{

		namespace Test{

			using TestFunction = void (*)(TestRunner&);

			class TestRegistry {
				public:
					bool add(TestFunction a_function) {
						return m_tests.add(a_function);
					}

					void run(TestRunner& a_runner) {
						for(int i = 0; i < m_tests.size(); ++i) {
							m_tests[i](a_runner);
						}
					}
				protected:
					FixedArray<TestFunction, 256> m_tests;
			};

			TestRegistry& pankey_test_registry(){
				static TestRegistry a_registry;
				return a_registry;
			}

			void pankey_register_test(TestFunction a_function){
				pankey_test_registry().add(a_function);
			}

		}

	}

}

#define PANKEY_TEST_REGISTER(FUNCTION) \
	static bool pankey_test_registered_##__LINE__ = \
		(pankey::Utility::Test::pankey_register_test(FUNCTION), true);

