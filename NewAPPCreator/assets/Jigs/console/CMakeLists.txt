# --------------------------------------------------------------------
# BinConnPro : Example of console GEN FrameWork (Binary protocol example)
# --------------------------------------------------------------------

 cmake_minimum_required(VERSION 3.14.0)
 project(binconnpro)


 set(GEN_DIRECTORY "../../../../") 


# --------------------------------------------------------------------
# Compile Selection
 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Platform-Compiler.txt") 


# --------------------------------------------------------------------
# Activate features/Defines

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Default.txt") 

 set(DEBUG_FEATURE                           true    CACHE BOOL "Activate Debug mode"                            FORCE)
 set(XTRACE_FEATURE                          true    CACHE BOOL "Activate XTrace"                                FORCE)
 set(XMEMORY_CONTROL_FEATURE                 true    CACHE BOOL "Activate XMemory Control"                       FORCE)
                  
 set(APP_FEATURE                             true    CACHE BOOL "Activate Application modules"                   FORCE)
 set(APP_CHECKRESOURCESHARDWARE_FEATURE      true    CACHE BOOL "Activate Application Check Resources Hardwar"   FORCE)
 set(APP_CONSOLE_FEATURE                     true    CACHE BOOL "Activate Application Console"                   FORCE)
 set(APP_INTERNETSERVICES_FEATURE            true    CACHE BOOL "Activate Application Internet Services"         FORCE)
 set(APP_LOG_FEATURE                         true    CACHE BOOL "Activate Application Log"                       FORCE)

 set(APP_CFG_GENERAL_FEATURE                 true    CACHE BOOL "Activate Application CFG General"               FORCE)  
 set(APP_CFG_LOG_FEATURE                     true    CACHE BOOL "Activate Application CFG LOG"                   FORCE)
 set(APP_CFG_INTERNETSERVICES_FEATURE        true    CACHE BOOL "Activate Application CFG Internet services"     FORCE)      
 

# --------------------------------------------------------------------
# Config Application Macro

 set(APP_CFG_BINCONNPRO "-DAPP_CFG=BINCONNPRO_CFG::GetInstance()")
 add_definitions(${APP_CFG_BINCONNPRO})


# --------------------------------------------------------------------
# Source code of the GEN in this Application

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists.txt") 
                   
                   
# --------------------------------------------------------------------
# Directorys of the Application

 set(APP_DIRECTORY_APPLICATION   "../Application")
 list(APPEND INCLUDES_DIR ${APP_DIRECTORY_APPLICATION})


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
 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Warnings.txt") 


# --------------------------------------------------------------------
# Create proyect 

 include_directories(${INCLUDES_DIR})

 add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})


# --------------------------------------------------------------------
# Add Libraries

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Libraries.txt") 