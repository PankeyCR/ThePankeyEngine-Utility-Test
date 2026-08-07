#pragma once

#include "CharPointer.hpp"
#include "helper_CharPointer.hpp"
#include "to_Primitive_CharPointer.hpp"

#if defined(pankey_Log) && (defined(TestResult_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
	#include "Logger_status.hpp"
	#define TestResultLog(status,method,mns) pankey_Log(status,"TestResult",method,mns)
#else
	#define TestResultLog(status,method,mns)
#endif

namespace pankey{

	namespace Utility{

		namespace Test{
		
			class TestResult{
				public:
					TestResult(){
						TestResultLog(pankey_Log_StartMethod, "Constructor", "");
						TestResultLog(pankey_Log_Statement, "Constructor", "Default Constructor");
						TestResultLog(pankey_Log_EndMethod, "Constructor", "");
					}
					
					TestResult(const TestResult& c_result){
						TestResultLog(pankey_Log_StartMethod, "Constructor", "");
						TestResultLog(pankey_Log_Statement, "Constructor", "const TestResult&");
						m_test_Error = c_result.m_test_Error;
                        m_info = c_result.m_info;
						m_errors = c_result.m_errors;
						m_expected_errors = c_result.m_expected_errors;
						TestResultLog(pankey_Log_EndMethod, "Constructor", "");
					}
					
					virtual ~TestResult(){
						TestResultLog(pankey_Log_StartMethod, "Destructor", "");
						TestResultLog(pankey_Log_EndMethod, "Destructor", "");
					}
					
					template<class... Args>
					void addInfo(Args... a_error){
						TestResultLog(pankey_Log_StartMethod, "addInfo", "");
                        CharPointer i_info = pankey::Utility::Test::concat(a_error...);
                        m_info = pankey::Utility::Test::concat(m_info, i_info);
						TestResultLog(pankey_Log_EndMethod, "addInfo", "");
					}
					
					virtual void catchError(int a_index, const CharPointer& a_error){
						TestResultLog(pankey_Log_StartMethod, "catchError", "");
						m_test_Error = true;
						CharPointer i_error_line = pankey::Utility::Test::concat(CharPointer("Index: "), toCharPointer(a_index), CharPointer(" | "), a_error);
						m_errors = addLine(m_errors, i_error_line);
						TestResultLog(pankey_Log_EndMethod, "catchError", "");
					}

					virtual void assertTrue(int a_index, const CharPointer& a_error, bool a_assert){
						if(!a_assert){
							this->catchError(a_index, a_error);
						}
					}

					virtual void assertNull(int a_index, const CharPointer& a_error, void* a_assert){
						if(a_assert != nullptr){
							this->catchError(a_index, a_error);
						}
					}

					virtual void assertNotNull(int a_index, const CharPointer& a_error, void* a_assert){
						if(a_assert == nullptr){
							this->catchError(a_index, a_error);
						}
					}

					template<class T>
					void assertLessThen(int a_index, const CharPointer& a_error, T a_assert_1, T a_assert_2){
						if(a_assert_1 >= a_assert_2){
							this->catchError(a_index, a_error);
						}
					}

					template<class T>
					void assertGreaterThen(int a_index, const CharPointer& a_error, T a_assert_1, T a_assert_2){
						if(a_assert_1 <= a_assert_2){
							this->catchError(a_index, a_error);
						}
					}

					template<class T>
					void assertLessEqualThen(int a_index, const CharPointer& a_error, T a_assert_1, T a_assert_2){
						if(a_assert_1 > a_assert_2){
							this->catchError(a_index, a_error);
						}
					}

					template<class T>
					void assertGreaterEqualThen(int a_index, const CharPointer& a_error, T a_assert_1, T a_assert_2){
						if(a_assert_1 < a_assert_2){
							this->catchError(a_index, a_error);
						}
					}

					template<class T>
					void assertInBetween(int a_index, const CharPointer& a_error, T a_assert_1, T a_assert_inbetween_1, T a_assert_inbetween_2){
						if(a_assert_inbetween_1 > a_assert_1 || a_assert_inbetween_2 < a_assert_1){
							this->catchError(a_index, a_error);
						}
					}

					template<class T>
					void assertEqual(int a_index, const CharPointer& a_error, T a_assert_1, T a_assert_2){
						if(a_assert_1 != a_assert_2){
							this->catchError(a_index, a_error);
						}
					}

					template<class T>
					void assertNotEqual(int a_index, const CharPointer& a_error, T a_assert_1, T a_assert_2){
						if(a_assert_1 == a_assert_2){
							this->catchError(a_index, a_error);
						}
					}

					template<class T>
					void assertSafeNotNullValueEqual(int a_index, const CharPointer& a_error, T* a_assert_1, T a_assert_2){
						if(a_assert_1 == nullptr){
							this->catchError(a_index, a_error);
							return;
						}
						if(*a_assert_1 != a_assert_2){
							this->catchError(a_index, a_error);
						}
					}

					template<class T>
					void assertSafeNotNullValueNotEqual(int a_index, const CharPointer& a_error, T* a_assert_1, T a_assert_2){
						if(a_assert_1 == nullptr){
							this->catchError(a_index, a_error);
							return;
						}
						if(*a_assert_1 == a_assert_2){
							this->catchError(a_index, a_error);
						}
					}

					// virtual void expecting(int a_index, const CharPointer& a_error){
					// 	TestResultLog(pankey_Log_StartMethod, "expecting", "");
					// 	CharPointer i_error_line = pankey::Utility::Test::concat(toCharPointer(a_index), CharPointer(" "), a_error);
					// 	m_expected_errors = addLine(m_expected_errors, i_error_line);
                    //     TestResultLog(pankey_Log_EndMethod, "expecting", "");
					// }

					// virtual void expectingTrue(int a_index, const CharPointer& a_error, bool a_assert){
					// 	TestResultLog(pankey_Log_StartMethod, "expectingTrue", "");
					// 	this->expecting(a_index, a_error, a_assert);
					// 	TestResultLog(pankey_Log_EndMethod, "expectingTrue", "");
					// }

					// virtual void expectingTrue(const CharPointer& a_error, bool a_assert){
					// 	TestResultLog(pankey_Log_StartMethod, "expectingTrue", "");
					// 	this->expecting(a_error, a_assert);
					// 	TestResultLog(pankey_Log_EndMethod, "expectingTrue", "");
					// }

					// virtual void assertExpectation(const CharPointer& a_error){
					// 	TestResultLog(pankey_Log_StartMethod, "assertExpectation", "");
					// 	int i_list_index = indexOf(m_expected_errors, a_error);
					// 	if(i_list_index == -1){
					// 		this->catchError(pankey::Utility::Test::concat(CharPointer("Error, no test registered: "), a_error));
					// 		return;
					// 	}
					// 	int i_index = m_expected_indexs.getByIndex(i_list_index);
					// 	int i_assert = m_expected_results.getByIndex(i_list_index);
					// 	if(!i_assert){
					// 		if(i_index == -1){
					// 			this->catchError(a_error);
					// 		}else{
					// 			this->catchError(i_index, a_error);
					// 		}
					// 	}
					// 	TestResultLog(pankey_Log_EndMethod, "assertExpectation", "");
					// }

					// virtual void assertUnexpectation(const CharPointer& a_error){
					// 	TestResultLog(pankey_Log_StartMethod, "assertUnexpectation", "");
					// 	int i_list_index = indexOf(m_expected_errors, a_error);
					// 	if(i_list_index == -1){
					// 		return;
					// 	}
					// 	int i_index = m_expected_indexs.getByIndex(i_list_index);
					// 	int i_assert = m_expected_results.getByIndex(i_list_index);
					// 	if(!i_assert){
					// 		if(i_index == -1){
					// 			this->catchError(pankey::Utility::Test::concat(CharPointer("Error, test has been registered and it shouldnt: "), a_error));
					// 		}else{
					// 			this->catchError(i_index, pankey::Utility::Test::concat(CharPointer("Error, test has been registered and it shouldnt: "), a_error));
					// 		}
					// 	}
					// 	TestResultLog(pankey_Log_EndMethod, "assertUnexpectation", "");
					// }

					// template<class... Args>
					// void assertExpectedSequence(Args... a_errors){
					// 	TestResultLog(pankey_Log_StartMethod, "assertExpectedSequence", "");
					// 	ArrayRawList<CharPointer> i_sequence;
					// 	i_sequence.addPack(a_errors...);

					// 	if(i_sequence.isEmpty()){
					// 		this->catchError(CharPointer("Error, no sequence of test registered: "));
					// 		TestResultLog(pankey_Log_EndMethod, "assertExpectedSequence", "");
					// 		return;
					// 	}
					// 	if(i_sequence.length() == 1){
					// 		this->assertExpectation(i_sequence.getByIndex(0));
					// 		TestResultLog(pankey_Log_EndMethod, "assertExpectedSequence", "");
					// 		return;
					// 	}

					// 	CharPointer i_first_error = i_sequence.getByIndex(0);
					// 	int i_list_index = indexOf(m_expected_errors, i_first_error);
					// 	int i_expected_count = getLineCount(m_expected_errors);
					// 	if(i_list_index == -1 || (i_list_index + i_sequence.length()) > i_expected_count){
					// 		this->assertEqual(CharPointer("Error, not enough test to check: sequence - errors found: "), i_sequence.length(), i_expected_count - i_list_index);
					// 		TestResultLog(pankey_Log_EndMethod, "assertExpectedSequence", "");
					// 		return;
					// 	}
						
					// 	int s = 0;
					// 	for(int x = i_list_index; s < i_sequence.length(); x++){
					// 		CharPointer f_error = getLine(m_expected_errors, x);
					// 		CharPointer f_sequence_error = i_sequence.getByIndex(s);
					// 		if(f_sequence_error != f_error){
					// 			this->catchError(pankey::Utility::Test::concat(CharPointer("Error, no test registered: "), f_error));
					// 			s++;
					// 			continue;
					// 		}
					// 		int i_index = m_expected_indexs.getByIndex(x);
					// 		int i_assert = m_expected_results.getByIndex(x);
					// 		if(!i_assert){
					// 			if(i_index == -1){
					// 				this->catchError(f_error);
					// 			}else{
					// 				this->catchError(i_index, f_error);
					// 			}
					// 		}
					// 		s++;
					// 	}
					// 	TestResultLog(pankey_Log_EndMethod, "assertExpectedSequence", "");
					// }

					virtual bool hasError(){return m_test_Error;}

					virtual bool hasInfo(){return !this->m_info.isEmpty();}
					
					virtual CharPointer getInfo(){
						return m_info;
					}
					
					virtual CharPointer getResult(){
						return m_errors;
					}
					
					virtual void operator=(const TestResult& c_result){
						m_test_Error = c_result.m_test_Error;
						m_info = c_result.m_info;
						m_errors = c_result.m_errors;
						m_expected_errors = c_result.m_expected_errors;
					}
					
					virtual void operator=(TestResult&& c_result){
						m_test_Error = c_result.m_test_Error;
						m_info = c_result.m_info;
						m_errors = c_result.m_errors;
						m_expected_errors = c_result.m_expected_errors;
					}
					
					virtual void clear(){
						m_test_Error = false;
                        m_info.clear();
						m_errors.clear();
						m_expected_errors.clear();
					}
					
				protected:
					bool m_test_Error = false;
					CharPointer m_info;
					CharPointer m_errors;
					CharPointer m_expected_errors;
			};

		}

	}

}
