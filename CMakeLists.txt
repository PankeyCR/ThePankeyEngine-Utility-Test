cmake_minimum_required(VERSION 3.15)

project(PankeyEngine_Utility_Test)

if(NOT TARGET ThePankeyEngine_Utility_Test)

    add_library(ThePankeyEngine_Utility_Test INTERFACE)

    target_include_directories(
        ThePankeyEngine_Utility_Test
          INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}
    )

endif()