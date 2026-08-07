#pragma once

#if defined(pankey_Log) && (defined(strlen_Log) || defined(pankey_Global_Log) || defined(pankey_Memory_Allocator_Log))
	#include "Logger_status.hpp"
	#define strlenLog(status,method,mns) pankey_Log(status,"strlen",method,mns)
#else
	#define strlenLog(status,method,mns)
#endif

namespace pankey{

	namespace Utility{

		namespace Test{

			int strlen(const char* a_pointer, int a_max_size){
				strlenLog(pankey_Log_StartMethod, "strlen", "");
				if(a_pointer == nullptr){
					strlenLog(pankey_Log_Statement, "strlen", "length:");
					strlenLog(pankey_Log_EndMethod, "strlen", 0);
					strlenLog(pankey_Log_EndMethod, "strlen", "a_pointer == nullptr");
					return 0;
				}
				for(int x = 0; x < a_max_size; x++){
					char f_value = a_pointer[x];
					if(f_value == '\0'){
						strlenLog(pankey_Log_Statement, "strlen", "length:");
						strlenLog(pankey_Log_EndMethod, "strlen", x);
						strlenLog(pankey_Log_EndMethod, "strlen", "f_value == endvalue");
						return x;
					}
				}
				strlenLog(pankey_Log_Statement, "strlen", "length:");
				strlenLog(pankey_Log_EndMethod, "strlen", 0);
				strlenLog(pankey_Log_EndMethod, "strlen", "");
				return 0;
			}

			static int strlen(const char* a_pointer){
				return strlen(a_pointer, 100000);
			}

			static bool isEmpty(const char* a_pointer){
				strlenLog(pankey_Log_StartMethod, "strlen", "");
				if(a_pointer == nullptr){
					strlenLog(pankey_Log_EndMethod, "strlen", "a_pointer == nullptr");
					return true;
				}
				int i_length = strlen(a_pointer);
				if(i_length == 0){
					strlenLog(pankey_Log_EndMethod, "strlen", "i_length == 0");
					return true;
				}
				strlenLog(pankey_Log_EndMethod, "strlen", "");
				return false;
			}

		}

	}

}