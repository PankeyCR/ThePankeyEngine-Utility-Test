#pragma once

#include "CharPointer.hpp"
#include "helper_Char.hpp"
#include "strlen.hpp"
#include "int_strlen.hpp"
#include "long_strlen.hpp"

#if defined(pankey_Log) && (defined(to_Primitive_CharPointer_Log) || defined(pankey_Global_Log) || defined(pankey_DataStructure_Array_Log))
	#include "Logger_status.hpp"
	#define to_Primitive_CharPointerLog(status,method,mns) pankey_Log(status,"to_Primitive_CharPointer",method,mns)
#else
	#define to_Primitive_CharPointerLog(status,method,mns)
#endif

namespace pankey{

	namespace Utility{

		namespace Test{

			CharPointer toCharPointer(const CharPointer& a_value){
				return a_value;
			}

			bool isBool(const CharPointer& a_array){
				to_Primitive_CharPointerLog(pankey_Log_StartMethod, "isBool", "");
				if(a_array.length() == 1){
					if(a_array.get(0) == '1'){
						to_Primitive_CharPointerLog(pankey_Log_EndMethod, "isBool", "1");
						return true;
					}
					if(a_array.get(0) == '0'){
						to_Primitive_CharPointerLog(pankey_Log_EndMethod, "isBool", "0");
						return true;
					}
				}
				if(a_array.length() == 3){
					if(a_array.get(0) == 'l' && a_array.get(1) == 'o' && a_array.get(2) == 'w'){
						to_Primitive_CharPointerLog(pankey_Log_EndMethod, "isBool", "true");
						return true;
					}
					if(a_array.get(0) == 'L' && a_array.get(1) == 'O' && a_array.get(2) == 'W'){
						to_Primitive_CharPointerLog(pankey_Log_EndMethod, "isBool", "true");
						return true;
					}
				}
				if(a_array.length() == 4){
					if(a_array.get(0) == 'h' && a_array.get(1) == 'i' && a_array.get(2) == 'g' && a_array.get(3) == 'h'){
						to_Primitive_CharPointerLog(pankey_Log_EndMethod, "isBool", "true");
						return true;
					}
					if(a_array.get(0) == 'H' && a_array.get(1) == 'I' && a_array.get(2) == 'G' && a_array.get(3) == 'H'){
						to_Primitive_CharPointerLog(pankey_Log_EndMethod, "isBool", "true");
						return true;
					}
					if(a_array.get(0) == 't' && a_array.get(1) == 'r' && a_array.get(2) == 'u' && a_array.get(3) == 'e'){
						to_Primitive_CharPointerLog(pankey_Log_EndMethod, "isBool", "true");
						return true;
					}
					if(a_array.get(0) == 'T' && a_array.get(1) == 'R' && a_array.get(2) == 'U' && a_array.get(3) == 'E'){
						to_Primitive_CharPointerLog(pankey_Log_EndMethod, "isBool", "TRUE");
						return true;
					}
				}
				if(a_array.length() == 5){
					if(a_array.get(0) == 'f' && a_array.get(1) == 'a' && a_array.get(2) == 'l' && a_array.get(3) == 's' && a_array.get(4) == 'e'){
						to_Primitive_CharPointerLog(pankey_Log_EndMethod, "isBool", "false");
						return true;
					}
					if(a_array.get(0) == 'F' && a_array.get(1) == 'A' && a_array.get(2) == 'L' && a_array.get(3) == 'S' && a_array.get(4) == 'E'){
						to_Primitive_CharPointerLog(pankey_Log_EndMethod, "isBool", "False");
						return true;
					}
				}
				to_Primitive_CharPointerLog(pankey_Log_EndMethod, "isBool", "Not bool");
				return false;
			}
	
			bool isInt(const CharPointer& a_array){ 
				to_Primitive_CharPointerLog(pankey_Log_StartMethod, "isInt", "");
				if(a_array.isEmpty()){
					to_Primitive_CharPointerLog(pankey_Log_EndMethod, "isInt", "isEmpty");
					return false;
				}
				int i_start = 0;
				if(a_array.get(0) == '-'){
					if(a_array.length() == 1){
						to_Primitive_CharPointerLog(pankey_Log_EndMethod, "isNegativeInt", "a_array.length() == 1 && -");
						return false;
					}
					i_start = 1;
				}
				for(int i = i_start; i < a_array.length(); i++){
					char f_char = a_array.get(i);
					if(!pankey::Utility::Test::isNumber(f_char)){
						to_Primitive_CharPointerLog(pankey_Log_EndMethod, "isInt", "Not a float");
						return false;
					}
				}
				to_Primitive_CharPointerLog(pankey_Log_EndMethod, "isInt", "Is a float");
				return true;
			}
			
			bool isPositiveInt(const CharPointer& a_array){ 
				to_Primitive_CharPointerLog(pankey_Log_StartMethod, "isPositiveInt", "");
				if(a_array.isEmpty()){
					to_Primitive_CharPointerLog(pankey_Log_EndMethod, "isPositiveInt", "isEmpty");
					return false;
				}
				if(a_array.get(0) == '-'){
					to_Primitive_CharPointerLog(pankey_Log_EndMethod, "isPositiveInt", "isEmpty");
					return false;
				}
				for(int i = 0; i < a_array.length(); i++){
					char f_char = a_array.get(i);
					if(!pankey::Utility::Test::isNumber(f_char)){
						to_Primitive_CharPointerLog(pankey_Log_EndMethod, "isPositiveInt", "Not a float");
						return false;
					}
				}
				to_Primitive_CharPointerLog(pankey_Log_EndMethod, "isPositiveInt", "Is a float");
				return true;
			}
			
			bool isNegativeInt(const CharPointer& a_array){ 
				to_Primitive_CharPointerLog(pankey_Log_StartMethod, "isNegativeInt", "");
				if(a_array.isEmpty()){
					to_Primitive_CharPointerLog(pankey_Log_EndMethod, "isNegativeInt", "isEmpty");
					return false;
				}
				if(a_array.get(0) != '-'){
					to_Primitive_CharPointerLog(pankey_Log_EndMethod, "isNegativeInt", "isEmpty");
					return false;
				}
				for(int i = 1; i < a_array.length(); i++){
					char f_char = a_array.get(i);
					if(!pankey::Utility::Test::isNumber(f_char)){
						to_Primitive_CharPointerLog(pankey_Log_EndMethod, "isNegativeInt", "Not a float");
						return false;
					}
				}
				to_Primitive_CharPointerLog(pankey_Log_EndMethod, "isNegativeInt", "Is a float");
				return true;
			}

			bool isLong(const CharPointer& a_array){
				to_Primitive_CharPointerLog(pankey_Log_StartMethod, "isLong", "");
				if(a_array.isEmpty()){
					to_Primitive_CharPointerLog(pankey_Log_EndMethod, "isLong", "Not a long");
					return false;
				}
				for(int i = 0; i < a_array.length() - 1; i++){
					char f_char = a_array.get(i);
					if(!pankey::Utility::Test::isNumber(f_char)){
						to_Primitive_CharPointerLog(pankey_Log_EndMethod, "isLong", "Not a long");
						return false;
					}
				}
				to_Primitive_CharPointerLog(pankey_Log_EndMethod, "isLong", "Is a long");
				return true;
			}
					
			CharPointer toCharPointer(int a_value){
				to_Primitive_CharPointerLog(pankey_Log_StartMethod, "toCharPointer", "const int&");
				CharPointer i_array;
				int i_size = pankey::Utility::Test::int_strlen(a_value);
				if(i_size <= 0){
					to_Primitive_CharPointerLog(pankey_Log_EndMethod, "toCharPointer", "");
					return i_array;
				}
				i_array.create(i_size);

				int position = 0;
				bool isNegative = false;
				if(a_value < 0){
					to_Primitive_CharPointerLog(pankey_Log_Statement, "toCharPointer", "negative value");
					to_Primitive_CharPointerLog(pankey_Log_Statement, "toCharPointer", "Position: ");
					to_Primitive_CharPointerLog(pankey_Log_Statement, "toCharPointer", position);
					isNegative = true;
					a_value *= -1;
					i_array.set(position, '-');
					position++;
					i_size--;
				}
				int i_value_reduction = 1;
				int i_reduce_value = 1;
				int i_output_value = 1;
				for(int x = 0; x < i_size; x++){
					int exponent = 1;
					for(int y = 0; y < i_size - x - 1; y++){
						exponent *= 10;
					}
					i_value_reduction = a_value / exponent;
					if(x == 0){
						i_output_value = i_value_reduction;
					}else{
						i_output_value = i_value_reduction - i_reduce_value;
					}
					i_reduce_value = i_value_reduction * 10;
					i_array.set(position, i_output_value + 48);
					position++;
				}
				to_Primitive_CharPointerLog(pankey_Log_EndMethod, "toCharPointer", "");
				return i_array;
			}

			CharPointer toCharPointer(const bool& a_value){
				to_Primitive_CharPointerLog(pankey_Log_StartMethod, "toCharPointer", "const bool&");
				CharPointer i_array;
				i_array.create(1);
				i_array.set(0, (a_value) ? '1' : '0');
				to_Primitive_CharPointerLog(pankey_Log_EndMethod, "toCharPointer", "");
				return i_array;
			}

			CharPointer toCharPointer(const char* a_value){
				to_Primitive_CharPointerLog(pankey_Log_StartMethod, "toCharPointer", "const char*");
				CharPointer i_array;
				if(a_value == nullptr){
					to_Primitive_CharPointerLog(pankey_Log_EndMethod, "toCharPointer", "a_value == nullptr");
					return i_array;
				}
				int i_size = pankey::Utility::Test::strlen(a_value);
				i_array.create(i_size);
				for(int x = 0; x < i_size; x++){
					i_array.set(x, a_value[x]);
				}
				to_Primitive_CharPointerLog(pankey_Log_EndMethod, "toCharPointer", "");
				return i_array;
			}

			CharPointer toCharPointer(const long& a_value){
				to_Primitive_CharPointerLog(pankey_Log_StartMethod, "toCharPointer", "const long&");
				to_Primitive_CharPointerLog(pankey_Log_Statement, "toCharPointer", "a_value");
				to_Primitive_CharPointerLog(pankey_Log_Statement, "toCharPointer", a_value);
				
				int i_size = pankey::Utility::Test::long_strlen(a_value);
				if(i_size <= 0){
					to_Primitive_CharPointerLog(pankey_Log_EndMethod, "toCharPointer", "");
					return CharPointer();
				}
				CharPointer i_array;
				i_array.create(i_size);

				long i_value = a_value;
				int position = 0;
				bool isNegative = false;
				if(i_value < 0){
					isNegative = true;
					i_value *= -1;
					i_size--;
					i_array.set(position, '-');
					position++;
				}
				long n_value = 1;
				long r_value = 1;
				long s_value = 1;
				for(int x = 0; x < i_size; x++){
					long expn = 1;
					for(int y = 0; y < i_size - x - 1; y++){
						expn *= 10;
					}
					n_value = i_value / expn;
					if(x == 0){
						s_value = n_value;
					}else{
						s_value = n_value - r_value;
					}
					r_value = n_value * 10;
					i_array.set(position, s_value + 48);
					position++;
				}
						
				to_Primitive_CharPointerLog(pankey_Log_EndMethod, "toCharPointer", "");
				return i_array;
			}

			CharPointer toCharPointer(float a_value, int a_decimal_size){
				to_Primitive_CharPointerLog(pankey_Log_StartMethod, "toCharPointer", "float, int");

				to_Primitive_CharPointerLog(pankey_Log_Statement, "toCharPointer", "a_value");
				to_Primitive_CharPointerLog(pankey_Log_Statement, "toCharPointer", a_value);
				to_Primitive_CharPointerLog(pankey_Log_Statement, "toCharPointer", "decimal_size");
				to_Primitive_CharPointerLog(pankey_Log_Statement, "toCharPointer", a_decimal_size);
				
				CharPointer i_array = toCharPointer((int)a_value);
				float i_decimals = pankey::Utility::Test::getDecimals(a_value, a_decimal_size, true);
				i_array.set(a_decimal_size, '.');
				if(i_decimals < 0) i_decimals *= -1;

				int i_exp = 1;
				for(int x = 0; x < a_decimal_size; x++)i_exp *= 10;

				int i_int_D = (i_decimals) * i_exp;
				to_Primitive_CharPointerLog(pankey_Log_Statement, "toCharPointer", "i_int_D");
				to_Primitive_CharPointerLog(pankey_Log_Statement, "toCharPointer", i_int_D);

				CharPointer i_int_S = toCharPointer(i_int_D);

				i_array.set(0, i_int_S);

				to_Primitive_CharPointerLog(pankey_Log_EndMethod, "toCharPointer", "");
				return i_array;
			}

			CharPointer toCharPointer(const float& a_value){
				to_Primitive_CharPointerLog(pankey_Log_StartMethod, "toCharPointer", "const float&");
				CharPointer i_array = toCharPointer(a_value, 2);
				to_Primitive_CharPointerLog(pankey_Log_EndMethod, "toCharPointer", "");
				return i_array;
			}

			CharPointer toCharPointer(const char& a_value){
				to_Primitive_CharPointerLog(pankey_Log_StartMethod, "Constructor", "const char& c_char");
				to_Primitive_CharPointerLog(pankey_Log_Statement, "Constructor", "Char:");
				to_Primitive_CharPointerLog(pankey_Log_Statement, "Constructor", a_value);
				CharPointer i_array;
				i_array.create(1);
				i_array.set(0, a_value);
				to_Primitive_CharPointerLog(pankey_Log_EndMethod, "Constructor", "");
				return i_array;
			}

			char toChar(const CharPointer& a_array){
				to_Primitive_CharPointerLog(pankey_Log_StartMethod, "toChar", "const CharPointer&");
				if(a_array.length() > 0){
					to_Primitive_CharPointerLog(pankey_Log_EndMethod, "toChar", "");
					return a_array.get(0);
				}
				to_Primitive_CharPointerLog(pankey_Log_EndMethod, "toChar", "");
				return '\0';
			}

			int toInt(const CharPointer& a_array){
				to_Primitive_CharPointerLog(pankey_Log_StartMethod, "toInt", "");
				if(a_array.isEmpty()){
					to_Primitive_CharPointerLog(pankey_Log_EndMethod, "toInt", "a_array.isEmpty()");
					return 0;
				}
				int i_start = 0;
				if(a_array.get(0) == '-'){
					i_start = 1;
				}
				int output = 0;
				int c_size = a_array.length();
				bool lastDecimals = false;
				for(int x = i_start; x < c_size; x++){
					char f_char = a_array.get(x);
					to_Primitive_CharPointerLog(pankey_Log_StartMethod, "toInt", "f_char");
					to_Primitive_CharPointerLog(pankey_Log_StartMethod, "toInt", f_char);
					if(pankey::Utility::Test::isDecimalPoint(f_char)){
						if(lastDecimals){
							to_Primitive_CharPointerLog(pankey_Log_EndMethod, "toInt", "allready has a decimal point");
							return 0;
						}
						lastDecimals = true;
						continue;
					}
					if(pankey::Utility::Test::isNumber(f_char)){
						if(lastDecimals){
							
						}else{
							to_Primitive_CharPointerLog(pankey_Log_Statement, "toInt", "int part");
							if(x != i_start){
								output *= 10;
							}
							output += (f_char - 48);
							to_Primitive_CharPointerLog(pankey_Log_Statement, "toInt", "output");
							to_Primitive_CharPointerLog(pankey_Log_Statement, "toInt", output);
						}
					}else{
						to_Primitive_CharPointerLog(pankey_Log_EndMethod, "toInt", "");
						return 0;
					}
				}
				if(i_start == 1){
					output *= -1;
				}
				to_Primitive_CharPointerLog(pankey_Log_EndMethod, "toInt", "");
				return output;
			}

			bool toBool(const CharPointer& a_array){
				to_Primitive_CharPointerLog(pankey_Log_StartMethod, "toBool", "const CharPointer&");
				if(a_array.length() == 1){
					if(a_array.get(0) == '1'){
						to_Primitive_CharPointerLog(pankey_Log_EndMethod, "toBool", "1");
						return true;
					}
					if(a_array.get(0) == '0'){
						to_Primitive_CharPointerLog(pankey_Log_EndMethod, "toBool", "0");
						return false;
					}
				}
				if(a_array.length() == 3){
					if(a_array.get(0) == 'l' && a_array.get(1) == 'o' && a_array.get(2) == 'w'){
						to_Primitive_CharPointerLog(pankey_Log_EndMethod, "toBool", "true");
						return false;
					}
					if(a_array.get(0) == 'L' && a_array.get(1) == 'O' && a_array.get(2) == 'W'){
						to_Primitive_CharPointerLog(pankey_Log_EndMethod, "toBool", "true");
						return false;
					}
				}
				if(a_array.length() == 4){
					if(a_array.get(0) == 'h' && a_array.get(1) == 'i' && a_array.get(2) == 'g' && a_array.get(3) == 'h'){
						to_Primitive_CharPointerLog(pankey_Log_EndMethod, "toBool", "true");
						return true;
					}
					if(a_array.get(0) == 'H' && a_array.get(1) == 'I' && a_array.get(2) == 'G' && a_array.get(3) == 'H'){
						to_Primitive_CharPointerLog(pankey_Log_EndMethod, "toBool", "true");
						return true;
					}
					if(a_array.get(0) == 't' && a_array.get(1) == 'r' && a_array.get(2) == 'u' && a_array.get(3) == 'e'){
						to_Primitive_CharPointerLog(pankey_Log_EndMethod, "toBool", "true");
						return true;
					}
					if(a_array.get(0) == 'T' && a_array.get(1) == 'R' && a_array.get(2) == 'U' && a_array.get(3) == 'E'){
						to_Primitive_CharPointerLog(pankey_Log_EndMethod, "toBool", "TRUE");
						return true;
					}
				}
				if(a_array.length() == 5){
					if(a_array.get(0) == 'f' && a_array.get(1) == 'a' && a_array.get(2) == 'l' && a_array.get(3) == 's' && a_array.get(4) == 'e'){
						to_Primitive_CharPointerLog(pankey_Log_EndMethod, "toBool", "false");
						return false;
					}
					if(a_array.get(0) == 'F' && a_array.get(1) == 'A' && a_array.get(2) == 'L' && a_array.get(3) == 'S' && a_array.get(4) == 'E'){
						to_Primitive_CharPointerLog(pankey_Log_EndMethod, "toBool", "False");
						return false;
					}
				}
				to_Primitive_CharPointerLog(pankey_Log_EndMethod, "toBool", "Not bool");
				return false;
			}

		}
		
	}
		
}