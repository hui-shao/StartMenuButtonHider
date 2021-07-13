cmake_minimum_required (VERSION 3.8)
add_executable (StartMenuButtonHider_Win7 "StartMenuButtonHider_Win7.cpp" "StartMenuButtonHider_Win7.h" "res/logo.rc")
# 添加管理员UAC
set_target_properties(StartMenuButtonHider_Win7 PROPERTIES LINK_FLAGS " /MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\" ")

