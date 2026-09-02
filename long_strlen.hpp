#pragma once

#if defined(pankey_Log) && (defined(long_strlen_Log) || defined(pankey_Global_Log) || defined(pankey_Memory_Allocator_Log))
	#include "Logger_status.hpp"
	#define long_strlenLog(status,method,mns) pankey_Log(status,"long_strlen",method,mns)
#else
	#define long_strlenLog(status,method,mns)
#endif

namespace pankey{

	namespace Utility{

		namespace Test{

			long long_strlen(long a_value){
				long_strlenLog(pankey_Log_StartMethod, "long_strlen", "");
				long_strlenLog(pankey_Log_Statement, "long_strlen", "");
				long i_size_val = 0;
				long x = 1;
				long add_x = 0;
				if(a_value < 0){
					a_value *= -1;
					add_x++;
				}
				for( ; x < 100; x++){
					long expn = 1;
					for(long y = 0; y < x; y++){
						expn *= 10;
					}
					if(a_value/expn < 1){
						i_size_val = x;
						break;
					}
				}
				long_strlenLog(pankey_Log_EndMethod, "long_strlen", "");
				return i_size_val + add_x;
			}

		}

	}

}