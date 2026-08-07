#pragma once

#if defined(pankey_Log) && (defined(int_strlen_Log) || defined(pankey_Global_Log) || defined(pankey_Memory_Allocator_Log))
	#include "Logger_status.hpp"
	#define int_strlenLog(status,method,mns) pankey_Log(status,"int_strlen",method,mns)
#else
	#define int_strlenLog(status,method,mns)
#endif

namespace pankey{

	namespace Utility{

		namespace Test{

			int int_strlen(int a_value){
				int_strlenLog(pankey_Log_StartMethod, "int_strlen", "");
				int_strlenLog(pankey_Log_Statement, "int_strlen", "");
				int i_size_val = 0;
				int x = 1;
				int add_x = 0;
				if(a_value < 0){
					a_value *= -1;
					add_x++;
				}
				for( ; x < 100; x++){
					int expn = 1;
					for(int y = 0; y < x; y++){
						expn *= 10;
					}
					if(a_value/expn < 1){
						i_size_val = x;
						break;
					}
				}
				int_strlenLog(pankey_Log_EndMethod, "int_strlen", "");
				return i_size_val + add_x;
			}

		}

	}

}