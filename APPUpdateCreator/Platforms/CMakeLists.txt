# --------------------------------------------------------------------
# APPUpdateCreator : Util for installer GEN FrameWork
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.16.0)
project(appupdatecreator)


set(GEN_DIRECTORY "../../../../GEN_FrameWork") 


# --------------------------------------------------------------------
# Activate features/Defines

option(DEBUG_FEATURE                                            "Debug mode"                                              ON )
                            
option(XTRACE_FEATURE                                           "XTrace"                                                  ON )
option(XMEMORY_CONTROL_FEATURE                                  "XMemory Control"                                         ON )
                                              
option(APPFLOW_FEATURE                                          "Application Flow modules"                                ON )
option(APPFLOW_EXTENDED_FEATURE                                 "Application Flow Extended"                               ON )  
option(APPFLOW_EXTENDED_APPLICATIONHEADER_FEATURE               "Application Flow Extended Aplication Header"             ON )  
option(APPFLOW_EXTENDED_APPLICATIONSTATUS_FEATURE               "Application Flow Extended Aplication Status"             ON )  
option(APPFLOW_CONSOLE_FEATURE                                  "Application Flow Console"                                ON )
option(APPFLOW_LOG_FEATURE                                      "Application Flow Log"                                    ON )
                                                                                  
option(APPFLOW_CFG_GENERAL_FEATURE                              "Application Flow CFG General"                            ON )  
option(APPFLOW_CFG_LOG_FEATURE                                  "Application Flow CFG LOG"                                ON )
                            
option(DIO_APPLICATIONUPDATE_FEATURE                            "Data Input/Output Application Update"                    ON )


# --------------------------------------------------------------------
# Config Application Macro

set(APP_CFG_APPUPDATECREATOR "-DAPPFLOW_CFG=APPUPDATECREATOR_CFG::GetInstance()")
add_definitions(${APP_CFG_APPUPDATECREATOR})


# --------------------------------------------------------------------
# Source code of the GEN in this Application

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_Main.txt") 
                   
                   
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Application")
list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})

# --------------------------------------------------------------------
# Source code of the Application

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/APPUpdateCreator.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/APPUpdateCreator_CFG.cpp")


# --------------------------------------------------------------------
# Create proyect 

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_CreateProject.txt") 


# --------------------------------------------------------------------
# Add Libraries

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_Libraries.txt") 