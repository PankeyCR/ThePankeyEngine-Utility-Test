#pragma once

#include "TestResult.hpp"

#if defined(pankey_Log) && (defined(TestRunner_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
	#include "Logger_status.hpp"
	#define TestRunnerLog(status,method,mns) pankey_Log(status,"TestRunner",method,mns)
#else
	#define TestRunnerLog(status,method,mns)
#endif

namespace pankey{

	namespace Utility{

		namespace Test{

			class TestRunner{
				public:
					TestRunner(){
						TestRunnerLog(pankey_Log_StartMethod, "Constructor", "");
						TestRunnerLog(pankey_Log_EndMethod, "Constructor", "");
					}
					~TestRunner(){
						TestRunnerLog(pankey_Log_StartMethod, "Destructor", "");
						TestRunnerLog(pankey_Log_EndMethod, "Destructor", "");
					}

					void omitInfo(bool a_omit){
						m_omit_info = a_omit;
					}

					void test(void(*a_result)(TestResult&)){
						TestRunnerLog(pankey_Log_StartMethod, "run", "");

						TestResult i_result;
						a_result(i_result);
						m_errors = addLine(m_errors, i_result.getResult());

						TestRunnerLog(pankey_Log_EndMethod, "run", "");
					}
					
					void errors(void(*a_error)(int, const CharPointer&)){
						TestRunnerLog(pankey_Log_StartMethod, "result", "");

						iterateLines(m_errors, a_error);

						TestRunnerLog(pankey_Log_EndMethod, "result", "");
					}
					
					void result(void(*a_error)(const CharPointer&)){
						TestRunnerLog(pankey_Log_StartMethod, "result", "");

						if(m_errors.isEmpty()){
							a_error(CharPointer("No Error Found"));
							return;
						}
						
						a_error(CharPointer("Test Failed"));

						TestRunnerLog(pankey_Log_EndMethod, "result", "");
					}

				protected:
					bool m_omit_info = false;
					CharPointer m_errors;
			};

		}

	}

}

