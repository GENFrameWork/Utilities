# --------------------------------------------------------------------
# BinConnPro : Example of console GEN FrameWork (Binary protocol example)
# --------------------------------------------------------------------

 cmake_minimum_required(VERSION 3.16.0)
 project(binconnpro)


 set(GEN_DIRECTORY "../../../../") 


# --------------------------------------------------------------------
# Compile Selection
 include("${GEN_DIRECTORY}/Common/cmake/GEN_CMakeLists_Platform-Compiler.txt") 


# --------------------------------------------------------------------
# Activate features/Defines

 include("${GEN_DIRECTORY}/Common/cmake/GEN_CMakeLists_Default.txt") 

 set(DEBUG_FEATURE                                true    CACHE BOOL "Debug mode"                                         ON )
 set(XTRACE_FEATURE                               true    CACHE BOOL "XTrace"                                             ON )
 set(XMEMORY_CONTROL_FEATURE                      true    CACHE BOOL "XMemory Control"                                    ON )
                  
 set(APPFLOW_FEATURE                              true    CACHE BOOL "Application Flow modules"                           ON )
 set(APPFLOW_CHECKRESOURCESHARDWARE_FEATURE       true    CACHE BOOL "Application Flow Check Resources Hardwar"           ON )
 set(APPFLOW_CONSOLE_FEATURE                      true    CACHE BOOL "Application Flow Console"                           ON )
 set(APPFLOW_INTERNETSERVICES_FEATURE             true    CACHE BOOL "Application Flow Internet Services"                 ON )
 set(APPFLOW_LOG_FEATURE                          true    CACHE BOOL "Application Flow Log"                               ON )
                                                                                          
 set(APPFLOW_CFG_GENERAL_FEATURE                  true    CACHE BOOL "Application Flow CFG General"                       ON )  
 set(APPFLOW_CFG_LOG_FEATURE                      true    CACHE BOOL "Application Flow CFG LOG"                           ON )
 set(APPFLOW_CFG_INTERNETSERVICES_FEATURE         true    CACHE BOOL "Application Flow CFG Internet services"             ON )      
 

# --------------------------------------------------------------------
# Config Application Macro

 set(APP_CFG_BINCONNPRO "-DAPPFLOW_CFG=BINCONNPRO_CFG::GetInstance()")
 add_definitions(${APP_CFG_BINCONNPRO})


# --------------------------------------------------------------------
# Source code of the GEN in this Application

 include("${GEN_DIRECTORY}/Common/cmake/GEN_CMakeLists.txt") 
                   
                   
# --------------------------------------------------------------------
# Directorys of the Application

 set(APP_DIRECTORY_APPLICATION   "../Application")
 list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/BinConnPro.cpp")
 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/BinConnPro_CFG.cpp")
 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/BinConnPro_ApplicationData.cpp")
 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/BinConnPro_ConnectionsManager.cpp")
 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/BinConnPro_Protocol.cpp")
 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/BinConnPro_Protocol_Device.cpp")


# --------------------------------------------------------------------
# Warnings control
 include("${GEN_DIRECTORY}/Common/cmake/GEN_CMakeLists_Warnings.txt") 


# --------------------------------------------------------------------
# Create proyect 

 include_directories(${GEN_INCLUDES_DIR_LIST})

 add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})


# --------------------------------------------------------------------
# Add Libraries

 include("${GEN_DIRECTORY}/Common/cmake/GEN_CMakeLists_Libraries.txt") 