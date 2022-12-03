# --------------------------------------------------------------------
# APPUpdateCreator : Util for installer GEN FrameWork
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.3.0)
project(appupdatecreator)


set(GEN_DIRECTORY "../../../../GENFrameWork") 


# --------------------------------------------------------------------
# Compile Selection
 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Compile.txt") 

# --------------------------------------------------------------------
# Warnings control
 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Warnings.txt") 


# --------------------------------------------------------------------
# Activate features/Defines


option(DEBUG_FEATURE                           "Activate Debug mode"                            true )

option(XTRACE_FEATURE                          "Activate XTrace"                                true )
option(XMEMORY_CONTROL_FEATURE                 "Activate XMemory Control"                       true )
                  
option(APP_FEATURE                             "Activate Application modules"                   true )
option(APP_CONSOLE_FEATURE                     "Activate Application Console"                   true )
option(APP_LOG_FEATURE                         "Activate Application Log"                       true )

option(APP_CFG_GENERAL_FEATURE                 "Activate Application CFG General"               true )  
option(APP_CFG_LOG_FEATURE                     "Activate Application CFG LOG"                   true )

option(DIO_APPLICATIONUPDATE_FEATURE           "Activate Data Input/Output Application Update"  true )



# --------------------------------------------------------------------
# Config Application Macro

set(APP_CFG_APPUPDATECREATOR "-DAPP_CFG=APPUPDATECREATOR_CFG::GetInstance()")
add_definitions(${APP_CFG_APPUPDATECREATOR})


# --------------------------------------------------------------------
# Source code of the GEN in this Application

include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists.txt") 
                   
                   
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Application")
list(APPEND INCLUDES_DIR ${APP_DIRECTORY_APPLICATION})

# --------------------------------------------------------------------
# Source code of the Application

list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/APPUpdateCreator.cpp")
list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/APPUpdateCreator_CFG.cpp")


# --------------------------------------------------------------------
# Create proyect 

include_directories(${INCLUDES_DIR})

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

# --------------------------------------------------------------------
# Add Libraries

include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Librarys.txt") 