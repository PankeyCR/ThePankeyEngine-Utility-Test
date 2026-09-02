#pragma once

#if defined(pankey_Log) && (defined(isNull_char_Log) || defined(pankey_Global_Log) || defined(pankey_Memory_Allocator_Log))
	#include "Logger_status.hpp"
	#define isNull_charLog(status,method,mns) pankey_Log(status,"isNull_char",method,mns)
#else
	#define isNull_charLog(status,method,mns)
#endif

namespace pankey{

	namespace Utility{

		namespace Test{

			bool isNull(char a_pointer){
				isNull_charLog(pankey_Log_StartMethod, "isNull", "");
				isNull_charLog(pankey_Log_EndMethod, "isNull", "");
				return a_pointer == '\0';
			}

			bool isNull(const char* a_pointer){
				isNull_charLog(pankey_Log_StartMethod, "isNull", "");
				if(a_pointer == nullptr){
					isNull_charLog(pankey_Log_Statement, "isNull", "a_pointer == nullptr");
					isNull_charLog(pankey_Log_EndMethod, "isNull", "");
					return true;
				}
				isNull_charLog(pankey_Log_EndMethod, "isNull", "");
				return a_pointer[0] == '\0';
			}

		}

	}

}