#pragma once

#include "CharPointer.hpp"
#include "strlen.hpp"
#include "int_strlen.hpp"
#include "long_strlen.hpp"

#if defined(pankey_Log) && (defined(helper_CharPointer_Log) || defined(pankey_Global_Log) || defined(pankey_DataStructure_Array_Log))
	#include "Logger_status.hpp"
	#define helper_CharPointerLog(status,method,mns) pankey_Log(status,"helper_CharPointer",method,mns)
#else
	#define helper_CharPointerLog(status,method,mns)
#endif

namespace pankey{

	namespace Utility{

		namespace Test{

			CharPointer concat(const CharPointer& a_text1, const CharPointer& a_text2){
				int i_length1 = a_text1.length();
				int i_length2 = a_text2.length();
				CharPointer i_result;
				i_result.create(i_length1 + i_length2);
				i_result.setAll(' ');
				for(int i = 0; i < i_length1; i++){
					i_result.set(i, a_text1.get(i));
				}
				for(int i = 0; i < i_length2; i++){
					i_result.set(i_length1 + i, a_text2.get(i));
				}
				return i_result;
			}

			template<class... Args>
			CharPointer concat(const Args&... a_texts){
				CharPointer i_array[] = {CharPointer(a_texts)...};
				CharPointer i_total;
				for(const CharPointer& a : i_array){
					i_total = pankey::Utility::Test::concat(i_total, a);
				}
				return i_total;
			}

			CharPointer split(int a_index, char a_delimiter, const CharPointer& a_text){
				if(a_index < 0 || a_text.isEmpty()){
					helper_CharPointerLog(pankey_Log_Error, "split", "a_index < 0 || a_text.isEmpty()");
					return CharPointer();
				}

				int i_part_index = 0;
				int i_start = 0;
				int i_length = a_text.length();

				for(int i_position = 0; i_position <= i_length; i_position++){
					bool i_is_end = (i_position == i_length);
					bool i_is_delimiter = (!i_is_end && a_text.get(i_position) == a_delimiter);

					if(i_is_end || i_is_delimiter){
						if(i_part_index == a_index){
							int i_part_length = i_position - i_start;
							if(i_part_length <= 0){
								return CharPointer();
							}

							CharPointer i_result;
							i_result.create(i_part_length);
							i_result.setAll(' ');
							for(int i_copy = 0; i_copy < i_part_length; i_copy++){
								i_result.set(i_copy, a_text.get(i_start + i_copy));
							}
							return i_result;
						}

						i_part_index++;
						i_start = i_position + 1;
					}
				}

				helper_CharPointerLog(pankey_Log_Error, "split", "a_index out of range");
				return CharPointer();
			}

			// Skips the first a_skip delimiter-separated fields and returns the remaining text.
			CharPointer skipFields(int a_skip, char a_delimiter, const CharPointer& a_text){
				if(a_skip < 0 || a_text.isEmpty()){
					helper_CharPointerLog(pankey_Log_Error, "skipFields", "a_skip < 0 || a_text.isEmpty()");
					return CharPointer();
				}

				if(a_skip == 0){
					return a_text;
				}

				int i_length = a_text.length();
				int i_fields_skipped = 0;
				int i_start = -1;

				for(int i_position = 0; i_position <= i_length; i_position++){
					bool i_is_end = (i_position == i_length);
					bool i_is_delimiter = (!i_is_end && a_text.get(i_position) == a_delimiter);

					if(i_is_end || i_is_delimiter){
						i_fields_skipped++;
						if(i_fields_skipped == a_skip){
							i_start = i_position + 1;
							break;
						}
					}
				}

				if(i_start < 0 || i_start >= i_length){
					return CharPointer();
				}

				int i_result_length = i_length - i_start;
				CharPointer i_result;
				i_result.create(i_result_length);
				i_result.setAll(' ');
				for(int i = 0; i < i_result_length; i++){
					i_result.set(i, a_text.get(i_start + i));
				}

				return i_result;
			}

			// Appends a_text to a_list separated by a single newline when a_list is not empty.
			CharPointer addLine(const CharPointer& a_list, const CharPointer& a_text){
				if(a_list.isEmpty()){
					return a_text;
				}

				int i_old_length = a_list.length();
				int i_new_length = i_old_length + 1 + a_text.length();
				CharPointer i_new_list;
				i_new_list.create(i_new_length);
				i_new_list.setAll(' ');
				for(int i = 0; i < i_old_length; i++){
					i_new_list.set(i, a_list.get(i));
				}
				i_new_list.set(i_old_length, '\n');
				for(int i = 0; i < a_text.length(); i++){
					i_new_list.set(i_old_length + 1 + i, a_text.get(i));
				}
				return i_new_list;
			}

			CharPointer getLine(const CharPointer& a_list, int a_index){
				return split(a_index, '\n', a_list);
			}

			int getLineCount(const CharPointer& a_list){
				if(a_list.isEmpty()){
					return 0;
				}

				int i_count = 1;
				for(int i = 0; i < a_list.length(); i++){
					if(a_list.get(i) == '\n'){
						i_count++;
					}
				}
				return i_count;
			}

			CharPointer append(const CharPointer& a_list, const CharPointer& a_text){
				return addLine(a_list, a_text);
			}

			int indexOf(const CharPointer& a_list, const CharPointer& a_text){
				if(a_list.isEmpty()){
					return -1;
				}

				int i_count = getLineCount(a_list);
				for(int i = 0; i < i_count; i++){
					CharPointer i_line = getLine(a_list, i);
					if(i_line == a_text){
						return i;
					}
				}
				return -1;
			}

			bool contains(const CharPointer& a_list, const CharPointer& a_text){
				return indexOf(a_list, a_text) != -1;
			}

			CharPointer insertAt(const CharPointer& a_list, int a_index, const CharPointer& a_text){
				if(a_index < 0){
					return a_list;
				}

				if(a_list.isEmpty()){
					if(a_index == 0){
						return a_text;
					}
					return a_list;
				}

				int i_count = getLineCount(a_list);
				if(a_index > i_count){
					return a_list;
				}

				CharPointer i_result;
				for(int i = 0; i < i_count; i++){
					if(i == a_index){
						i_result = addLine(i_result, a_text);
					}
					i_result = addLine(i_result, getLine(a_list, i));
				}

				if(a_index == i_count){
					i_result = addLine(i_result, a_text);
				}

				return i_result;
			}

			CharPointer removeAt(const CharPointer& a_list, int a_index){
				if(a_list.isEmpty()){
					return a_list;
				}
				if(a_index < 0){
					return a_list;
				}

				int i_count = getLineCount(a_list);
				if(a_index >= i_count){
					return a_list;
				}

				CharPointer i_result;
				for(int i = 0; i < i_count; i++){
					if(i == a_index){
						continue;
					}
					i_result = addLine(i_result, getLine(a_list, i));
				}
				return i_result;
			}

			CharPointer setAt(const CharPointer& a_list, int a_index, const CharPointer& a_text){
				if(a_list.isEmpty()){
					return a_list;
				}
				if(a_index < 0){
					return a_list;
				}

				int i_count = getLineCount(a_list);
				if(a_index >= i_count){
					return a_list;
				}

				CharPointer i_result;
				for(int i = 0; i < i_count; i++){
					if(i == a_index){
						i_result = addLine(i_result, a_text);
						continue;
					}
					i_result = addLine(i_result, getLine(a_list, i));
				}
				return i_result;
			}

			void iterateLines(const CharPointer& a_list, void(*a_callback)(int, const CharPointer&)){
				if(a_list.isEmpty()){
					return;
				}

				int i_count = getLineCount(a_list);
				for(int i = 0; i < i_count; i++){
					CharPointer i_line = getLine(a_list, i);
					a_callback(i, i_line);
				}
			}
		}
		
	}
		
}