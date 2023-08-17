# --------------------------------------------------------------------
# CompileBuilder: Application for process compiler 
# GEN FrameWork Utilities
# --------------------------------------------------------------------

 cmake_minimum_required(VERSION 3.6.0)
 project(compilerbuilder)

 set(GEN_DIRECTORY "../../../") 


# --------------------------------------------------------------------
# Compile Selection
 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Platform-Compiler.txt") 


 option(DEBUG_FEATURE                                       "Debug mode"                                                true )
 option(XTRACE_FEATURE                                      "XTrace"                                                    true )
 option(XTRACE_NOINTERNET_FEATURE                           "No need for trace dependencies with Internet"              true )                  
 option(XMEMORY_CONTROL_FEATURE                             "XMemory Control"                                           true )
                  
 option(APP_FEATURE                                         "Application modules"                                       true )
 option(APP_CONSOLE_FEATURE                                 "Application Console"                                       true )
 option(APP_LOG_FEATURE                                     "Application Log"                                           true )

 option(APP_CFG_GENERAL_FEATURE                             "Application CFG General"                                   true )
 option(APP_CFG_LOG_FEATURE                                 "Application CFG LOG"                                       true )
 
 option(SCRIPT_FEATURE                                      "Scripts"                                                   true )
 option(SCRIPT_G_FEATURE                                    "Script G Language"                                         true ) 
 option(SCRIPT_LUA_FEATURE                                  "Script LUA Language"                                       true )
 option(SCRIPT_JAVASCRIPT_FEATURE                           "Script Javascript Language"                                true )
 option(SCRIPT_LIB_SYSTEM_FEATURE                           "Script Lib System"                                         true )    
 option(SCRIPT_LIB_PROCESS_FEATURE                          "Script Lib Process"                                        true )    
 option(SCRIPT_LIB_LOG_FEATURE                              "Script Lib Log"                                            true )    
 option(SCRIPT_LIB_CONSOLE_FEATURE                          "Script Lib Console"                                        true ) 
 option(SCRIPT_LIB_CFG_FEATURE                              "Script Lib Config File"                                    true )   
 

# --------------------------------------------------------------------
# Config Application Macro

 set(APP_CFG_SCRIPTS "-DAPP_CFG=CBUILDER_CFG::GetInstance()")
 add_definitions(${APP_CFG_SCRIPTS})


# --------------------------------------------------------------------
# Source code of the GEN in this Application

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists.txt") 
                   
                   
# --------------------------------------------------------------------
# Directorys of the Application

 set(APP_DIRECTORY_APPLICATION   "../Application")
 list(APPEND INCLUDES_DIR ${APP_DIRECTORY_APPLICATION})

# --------------------------------------------------------------------
# Source code of the Application

 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/CompileBuilder.cpp")
 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/CompileBuilder_CFG.cpp")


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
