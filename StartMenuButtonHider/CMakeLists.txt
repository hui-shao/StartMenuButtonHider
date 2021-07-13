cmake_minimum_required (VERSION 3.8)
add_executable (StartMenuButtonHider "StartMenuButtonHider.cpp" "StartMenuButtonHider.h" "res/logo.rc")
# 添加管理员UAC
set_target_properties(StartMenuButtonHider PROPERTIES LINK_FLAGS " /MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\" ")

