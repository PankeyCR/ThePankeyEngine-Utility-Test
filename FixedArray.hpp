#pragma once

#if defined(pankey_Log) && (defined(FixedArray_Log) || defined(pankey_Global_Log) || defined(pankey_DataStructure_Array_Log))
	#include "Logger_status.hpp"
	#define FixedArrayLog(status,method,mns) pankey_Log(status,"FixedArray",method,mns)
#else
	#define FixedArrayLog(status,method,mns)
#endif

namespace pankey{

	namespace Utility{

		namespace Test{

			template<typename T, int S>
			class FixedArray {
				public:
					bool add(const T& a_value) {

						if(m_count >= S) {
							return false;
						}

						m_data[m_count] = a_value;
						++m_count;

						return true;
					}

					int size() const {
						return m_count;
					}

					T& operator[](int a_index) {
						return m_data[a_index];
					}

					const T& operator[](int a_index) const {
						return m_data[a_index];
					}
				
				protected:
					T m_data[S];
					int m_count = 0;
			};

		}

	}

}