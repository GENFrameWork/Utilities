# --------------------------------------------------------------------
# CompileBuilder: Application for process compiler 
# GEN FrameWork Utilities
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.14.0)
project(compilerbuilder)


set(GEN_DIRECTORY "../../../") 


# --------------------------------------------------------------------
# Activate features/Defines

option(DEBUG_FEATURE                                            "Debug mode"                                              ON )
option(XTRACE_FEATURE                                           "XTrace"                                                  ON )
option(XTRACE_NOINTERNET_FEATURE                                "No need for trace dependencies with Internet"            ON )                  
option(XMEMORY_CONTROL_FEATURE                                  "XMemory Control"                                         ON )
                    
option(APP_FEATURE                                              "Application modules"                                     ON )
option(APP_EXTENDED_FEATURE                                     "Application Extended"                                    ON )
option(APP_CONSOLE_FEATURE                                      "Application Console"                                     ON )
option(APP_LOG_FEATURE                                          "Application Log"                                         ON )
    
option(APP_CFG_GENERAL_FEATURE                                  "Application CFG General"                                 ON )
option(APP_CFG_LOG_FEATURE                                      "Application CFG LOG"                                     ON )
option(APP_CFG_SCRIPTS_FEATURE                                  "Application Scripts List"                                ON )  
    
option(SCRIPT_FEATURE                                           "Scripts"                                                 ON )
option(SCRIPT_G_FEATURE                                         "Script G Language"                                       ON ) 
option(SCRIPT_LUA_FEATURE                                       "Script LUA Language"                                     ON )
option(SCRIPT_JAVASCRIPT_FEATURE                                "Script Javascript Language"                              ON )
option(SCRIPT_LIB_SYSTEM_FEATURE                                "Script Lib System"                                       ON )    
option(SCRIPT_LIB_PROCESS_FEATURE                               "Script Lib Process"                                      ON )    
option(SCRIPT_LIB_LOG_FEATURE                                   "Script Lib Log"                                          ON )    
option(SCRIPT_LIB_CONSOLE_FEATURE                               "Script Lib Console"                                      ON ) 
option(SCRIPT_LIB_CFG_FEATURE                                   "Script Lib Config File"                                  ON )   
 

# --------------------------------------------------------------------
# Config Application Macro

set(APP_CFG_SCRIPTS "-DAPP_CFG=CBUILDER_CFG::GetInstance()")
add_definitions(${APP_CFG_SCRIPTS})


# --------------------------------------------------------------------
# Source code of the GEN in this Application

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_Main.txt") 
                   
                   
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Application")
list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/CompileBuilder.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/CompileBuilder_CFG.cpp")


# --------------------------------------------------------------------
# Create proyect 

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_CreateProject.txt") 


# --------------------------------------------------------------------
# Add Libraries

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_Libraries.txt") 
