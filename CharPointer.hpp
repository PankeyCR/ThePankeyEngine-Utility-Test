#pragma once

#include "strlen.hpp"
#include "isNull_char.hpp"

#if defined(pankey_Log) && (defined(CharPointer_Log) || defined(pankey_Global_Log) || defined(pankey_DataStructure_Array_Log))
	#include "Logger_status.hpp"
	#define CharPointerLog(status,method,mns) pankey_Log(status,"CharPointer",method,mns)
#else
	#define CharPointerLog(status,method,mns)
#endif

namespace pankey{

	namespace Utility{

		namespace Test{

			class CharPointer{
				public:
					CharPointer() {
						CharPointerLog(pankey_Log_StartMethod, "Contructor", "const char*");
						CharPointerLog(pankey_Log_EndMethod, "Contructor", "");
					}
					CharPointer(const char* a_pointer) {
						CharPointerLog(pankey_Log_StartMethod, "Contructor", "const char*");
						int i_length = pankey::Utility::Test::strlen(a_pointer);
						create(a_pointer, i_length);
						CharPointerLog(pankey_Log_EndMethod, "Contructor", "");
					}

					CharPointer(const char* a_pointer, int a_length) {
						CharPointerLog(pankey_Log_StartMethod, "Contructor", "const char*,int");
						create(a_pointer, a_length);
						CharPointerLog(pankey_Log_EndMethod, "Contructor", "");
					}

					CharPointer(const CharPointer& a_charpointer){
						CharPointerLog(pankey_Log_StartMethod, "Contructor", "const CharPointer&");
						create(a_charpointer.m_pointer, a_charpointer.m_length);
						CharPointerLog(pankey_Log_EndMethod, "Contructor", "");
					}

					CharPointer(CharPointer&& a_charpointer){
						CharPointerLog(pankey_Log_StartMethod, "Contructor", "CharPointer&&");
						m_pointer = a_charpointer.m_pointer;
						m_length = a_charpointer.m_length;
						a_charpointer.m_pointer = nullptr;
						a_charpointer.m_length = 0;
						CharPointerLog(pankey_Log_EndMethod, "Contructor", "");
					}

					virtual ~CharPointer(){
						CharPointerLog(pankey_Log_StartMethod, "Destructor", "");
						clear();
						CharPointerLog(pankey_Log_EndMethod, "Destructor", "");
					}

					virtual void clear(){
						CharPointerLog(pankey_Log_StartMethod, "clear", "");
						if(m_pointer == nullptr){
							return;
						}
						delete[] m_pointer;
						m_pointer = nullptr;
						m_length = 0;
						CharPointerLog(pankey_Log_EndMethod, "clear", "");
					}

					virtual void create(int a_length){
						CharPointerLog(pankey_Log_StartMethod, "create", "");
						if(a_length < 0){
							CharPointerLog(pankey_Log_Error, "create", "a_length < 0");
							CharPointerLog(pankey_Log_EndMethod, "create", "");
							return;
						}
						if(a_length > 2147483646){
							CharPointerLog(pankey_Log_Error, "create", "a_length too large");
							CharPointerLog(pankey_Log_EndMethod, "create", "");
							return;
						}
						clear();
						m_pointer = new char[a_length + 1];
						m_length = a_length;
						m_pointer[a_length] = '\0';
						CharPointerLog(pankey_Log_EndMethod, "create", "");
					}

					void create(const char* a_pointer, int a_length){
						CharPointerLog(pankey_Log_StartMethod, "create", "");
						if(a_pointer == nullptr){
							CharPointerLog(pankey_Log_Error, "create", "a_pointer == nullptr");
							CharPointerLog(pankey_Log_EndMethod, "create", "");
							return;
						}
						if(a_length < 0){
							CharPointerLog(pankey_Log_Error, "create", "a_length < 0");
							CharPointerLog(pankey_Log_EndMethod, "create", "");
							return;
						}
						const int i_source_length = pankey::Utility::Test::strlen(a_pointer);
						const int i_copy_length = a_length < i_source_length ? a_length : i_source_length;
						this->create(i_copy_length);
						if(m_pointer != nullptr){
							copy(a_pointer, i_copy_length);
						}
						CharPointerLog(pankey_Log_EndMethod, "create", "");
					}

					void copy(const char* a_pointer, int a_length){
						CharPointerLog(pankey_Log_StartMethod, "copy", "");
						if(m_pointer == nullptr || a_pointer == nullptr){
							CharPointerLog(pankey_Log_Error, "copy", "m_pointer == nullptr || a_pointer == nullptr");
							CharPointerLog(pankey_Log_EndMethod, "copy", "");
							return;
						}
						if(a_length <= 0 || m_length != a_length){
							CharPointerLog(pankey_Log_Error, "copy", "a_length <= 0 || m_length != a_length");
							CharPointerLog(pankey_Log_EndMethod, "copy", "");
							return;
						}
						for(int x = 0; x < a_length; x++){
							CharPointerLog(pankey_Log_Statement, "copy", "iteration:");
							CharPointerLog(pankey_Log_Statement, "copy", x);
							CharPointerLog(pankey_Log_Statement, "copy", "value:");
							CharPointerLog(pankey_Log_Statement, "copy", a_pointer[x]);
							m_pointer[x] = a_pointer[x];
						}
						CharPointerLog(pankey_Log_EndMethod, "copy", "");
					}

					bool isEmpty() const {
						if(m_pointer == nullptr){
							return true;							
						}
						if(m_length <= 0){
							return true;
						}
						return m_pointer[0] == '\0';
					}
					
					const bool isNull()const{
						return pankey::Utility::Test::isNull(m_pointer);
					}
					
					const char* get() const {
						return m_pointer;
					}
					
					const char get(int a_index) const {
						if(pankey::Utility::Test::isNull(m_pointer)){
							return '\0';
						}
						if(a_index < 0 || a_index >= m_length){
							return '\0';
						}
						return m_pointer[a_index];
					}
					
					void set(int a_index, char a_char){
						if(a_index < 0 || a_index >= m_length || pankey::Utility::Test::isNull(m_pointer)){
							return;
						}
						m_pointer[a_index] = a_char;
					}
					
					void set(int a_index, const CharPointer& a_array){
						if(a_index < 0 || a_index + a_array.length() > m_length || pankey::Utility::Test::isNull(m_pointer)){
							return;
						}
						for(int x = 0; x < a_array.length() && a_index + x < m_length; x++){
							m_pointer[a_index + x] = a_array.get(x);
						}
					}
					
					void setAll(char a_char){
						if(m_pointer == nullptr){
							return;
						}
						for(int x = 0; x < m_length; x++){
							m_pointer[x] = a_char;
						}
					}

					operator bool() const {
						return m_pointer == nullptr;
					}

					const char* operator()() const {
						return m_pointer;
					}

					virtual int length()const{
						return m_length;
					}

					CharPointer& operator=(const CharPointer& a_charpointer){
						CharPointerLog(pankey_Log_StartMethod, "operator=", "const CharPointer&");
						this->clear();
						create(a_charpointer.m_pointer, a_charpointer.m_length);
						CharPointerLog(pankey_Log_EndMethod, "operator=", "");
						return *this;
					}

					bool operator==(const CharPointer& a_charpointer){
						CharPointerLog(pankey_Log_StartMethod, "operator==", "");
						if(m_pointer == a_charpointer.m_pointer){
							CharPointerLog(pankey_Log_Statement, "operator==", "m_pointer == a_pointer");
							CharPointerLog(pankey_Log_EndMethod, "operator==", "");
							return true;
						}
						if(m_pointer == nullptr && a_charpointer.m_pointer == nullptr){
							CharPointerLog(pankey_Log_Statement, "operator==", "m_pointer == nullptr && a_pointer == nullptr");
							CharPointerLog(pankey_Log_EndMethod, "operator==", "");
							return true;
						}
						if(m_pointer == nullptr || a_charpointer.m_pointer == nullptr){
							CharPointerLog(pankey_Log_Statement, "operator==", "m_pointer == nullptr || a_pointer == nullptr");
							CharPointerLog(pankey_Log_EndMethod, "operator==", "");
							return false;
						}
						int i_length = pankey::Utility::Test::strlen(a_charpointer.m_pointer);
						if(m_length != i_length){
							CharPointerLog(pankey_Log_Statement, "operator==", "m_length != i_length");
							CharPointerLog(pankey_Log_EndMethod, "operator==", "");
							return false;
						}
						for(int x = 0; x < m_length; x++){
							if(m_pointer[x] != a_charpointer.m_pointer[x]){
								return false;
							}
						}
						CharPointerLog(pankey_Log_EndMethod, "operator==", "");
						return true;
					}

					bool operator==(const char* a_pointer){
						CharPointerLog(pankey_Log_StartMethod, "operator==", "");
						if(m_pointer == a_pointer){
							CharPointerLog(pankey_Log_Statement, "operator==", "m_pointer == a_pointer");
							CharPointerLog(pankey_Log_EndMethod, "operator==", "");
							return true;
						}
						if(m_pointer == nullptr && a_pointer == nullptr){
							CharPointerLog(pankey_Log_Statement, "operator==", "m_pointer == nullptr && a_pointer == nullptr");
							CharPointerLog(pankey_Log_EndMethod, "operator==", "");
							return true;
						}
						if(m_pointer == nullptr || a_pointer == nullptr){
							CharPointerLog(pankey_Log_Statement, "operator==", "m_pointer == nullptr || a_pointer == nullptr");
							CharPointerLog(pankey_Log_EndMethod, "operator==", "");
							return false;
						}
						int i_length = pankey::Utility::Test::strlen(a_pointer);
						if(m_length != i_length){
							CharPointerLog(pankey_Log_Statement, "operator==", "m_length != i_length");
							CharPointerLog(pankey_Log_EndMethod, "operator==", "");
							return false;
						}
						for(int x = 0; x < m_length; x++){
							if(m_pointer[x] != a_pointer[x]){
								return false;
							}
						}
						CharPointerLog(pankey_Log_EndMethod, "operator==", "");
						return true;
					}

					bool operator!=(const CharPointer& a_charpointer){
						CharPointerLog(pankey_Log_StartMethod, "operator!=", "");
						if(m_pointer == a_charpointer.m_pointer){
							CharPointerLog(pankey_Log_Statement, "operator!=", "m_pointer == a_pointer");
							CharPointerLog(pankey_Log_EndMethod, "operator!=", "");
							return false;
						}
						if(m_pointer == nullptr && a_charpointer.m_pointer == nullptr){
							CharPointerLog(pankey_Log_Statement, "operator!=", "m_pointer == nullptr && a_pointer == nullptr");
							CharPointerLog(pankey_Log_EndMethod, "operator!=", "");
							return false;
						}
						if(m_pointer == nullptr || a_charpointer.m_pointer == nullptr){
							CharPointerLog(pankey_Log_Statement, "operator!=", "m_pointer == nullptr || a_pointer == nullptr");
							CharPointerLog(pankey_Log_EndMethod, "operator!=", "");
							return true;
						}
						int i_length = pankey::Utility::Test::strlen(a_charpointer.m_pointer);
						if(m_length != i_length){
							CharPointerLog(pankey_Log_Statement, "operator!=", "m_length != i_length");
							CharPointerLog(pankey_Log_EndMethod, "operator!=", "");
							return true;
						}
						for(int x = 0; x < m_length; x++){
							if(m_pointer[x] != a_charpointer.m_pointer[x]){
								return true;
							}
						}
						CharPointerLog(pankey_Log_EndMethod, "operator!=", "");
						return false;
					}

					bool operator!=(const char* a_pointer){
						CharPointerLog(pankey_Log_StartMethod, "operator!=", "");
						if(m_pointer == a_pointer){
							CharPointerLog(pankey_Log_Statement, "operator!=", "m_pointer == a_pointer");
							CharPointerLog(pankey_Log_EndMethod, "operator!=", "");
							return false;
						}
						if(m_pointer == nullptr && a_pointer == nullptr){
							CharPointerLog(pankey_Log_Statement, "operator!=", "m_pointer == nullptr && a_pointer == nullptr");
							CharPointerLog(pankey_Log_EndMethod, "operator!=", "");
							return false;
						}
						if(m_pointer == nullptr || a_pointer == nullptr){
							CharPointerLog(pankey_Log_Statement, "operator!=", "m_pointer == nullptr || a_pointer == nullptr");
							CharPointerLog(pankey_Log_EndMethod, "operator!=", "");
							return true;
						}
						int i_length = pankey::Utility::Test::strlen(a_pointer);
						if(m_length != i_length){
							CharPointerLog(pankey_Log_Statement, "operator!=", "m_length != i_length");
							CharPointerLog(pankey_Log_EndMethod, "operator!=", "");
							return true;
						}
						for(int x = 0; x < m_length; x++){
							if(m_pointer[x] != a_pointer[x]){
								return true;
							}
						}
						CharPointerLog(pankey_Log_EndMethod, "operator!=", "");
						return false;
					}
					
				protected:
					char* m_pointer = nullptr;
					int m_length = 0;
			};

		}

	}

}