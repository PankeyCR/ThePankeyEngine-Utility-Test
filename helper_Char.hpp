
#pragma once

#if defined(pankey_Log) && (defined(helper_Char_Log) || defined(pankey_Global_Log) || defined(pankey_Utility_Base_Log))
	#include "Logger_status.hpp"
	#define helper_CharLog(status,method,mns) pankey_Log(status,"helper_Char",method,mns)
#else
	#define helper_CharLog(status,method,mns)
#endif

namespace pankey{

	namespace Utility{

		namespace Test{

			bool isNumber(char a_char){
				helper_CharLog(pankey_Log_StartMethod, "isNumber", "");
				helper_CharLog(pankey_Log_EndMethod, "isNumber", "");
				return a_char > 47 && a_char < 58;
			}

			bool isDecimalPoint(char a_char){
				helper_CharLog(pankey_Log_StartMethod, "isDecimalPoint", "");
				helper_CharLog(pankey_Log_EndMethod, "isDecimalPoint", "");
				return a_char == 46;
			}

			int getNumber(char a_char){
				helper_CharLog(pankey_Log_StartMethod, "getNumber", "");
				if(!isNumber(a_char)){
					return -1;
				}
				helper_CharLog(pankey_Log_EndMethod, "getNumber", "");
				return a_char - 48;
			}

			float getDecimals(float a_value, int a_decimals, bool a_round_result) {
				if (a_decimals < 0) a_decimals = 0;
				if (a_decimals > 6) a_decimals = 6; // float precision limit

				bool is_negative = (a_value < 0);
				if (is_negative) a_value = -a_value;

				int int_part = (int)a_value;
				float frac = a_value - (float)int_part;

				int scale = 1;
				for (int i = 0; i < a_decimals; ++i) scale *= 10;

				float scaled = frac * scale;
				int scaled_int = a_round_result ? (int)(scaled + 0.5f) : (int)(scaled);
				float result = (float)scaled_int / (float)scale;

				return is_negative ? -result : result;
			}
				
		}

	}

}
