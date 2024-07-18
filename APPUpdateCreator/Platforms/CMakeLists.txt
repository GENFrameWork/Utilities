# --------------------------------------------------------------------
# APPUpdateCreator : Util for installer GEN FrameWork
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.14.0)
project(appupdatecreator)


set(GEN_DIRECTORY "../../../../GENFrameWork") 


# --------------------------------------------------------------------
# Activate features/Defines

option(DEBUG_FEATURE                                          "Activate Debug mode"                                     ON )
                            
option(XTRACE_FEATURE                                         "Activate XTrace"                                         ON )
option(XMEMORY_CONTROL_FEATURE                                "Activate XMemory Control"                                ON )
                                              
option(APP_FEATURE                                            "Activate Application modules"                            ON )
option(APP_CONSOLE_FEATURE                                    "Activate Application Console"                            ON )
option(APP_LOG_FEATURE                                        "Activate Application Log"                                ON )
                            
option(APP_CFG_GENERAL_FEATURE                                "Activate Application CFG General"                        ON )  
option(APP_CFG_LOG_FEATURE                                    "Activate Application CFG LOG"                            ON )
                            
option(DIO_APPLICATIONUPDATE_FEATURE                          "Activate Data Input/Output Application Update"           ON )


# --------------------------------------------------------------------
# Config Application Macro

set(APP_CFG_APPUPDATECREATOR "-DAPP_CFG=APPUPDATECREATOR_CFG::GetInstance()")
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