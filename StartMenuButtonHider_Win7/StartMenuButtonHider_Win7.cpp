#include "startmenubuttonhider_Win7.h"

using namespace std;

int reg_rw(HKEY hKey = NULL, LPCSTR SubKey = NULL, LPSTR ValueName = NULL, DWORD dwType = REG_DWORD, int data = 0,
	DWORD dwOptions = REG_OPTION_NON_VOLATILE, REGSAM samDesired = KEY_ALL_ACCESS | KEY_WOW64_64KEY) {
	// samDesired 参数需要添加 KEY_WOW64_64KEY ，否则32位程序无法修改64位系统的注册表，会被重定向到 WOW6432Node
	// ValueName、dwType、data 是 RegSetValueEx所需的, 分别是 值的名称、类型、数据

	// 创建或打开一个键
	DWORD dwDisposition; // 定义 dwDisposition 用于接收返回码
	auto result = RegCreateKeyEx(hKey, SubKey, 0, NULL, dwOptions, samDesired, NULL, &hKey, &dwDisposition);
	cout << "" << endl;
	if (ERROR_SUCCESS != result) {
		cout << " 创建注册表失败, 错误代码：" << result << endl;
		return -1;
	}
	else {
		if (dwDisposition == REG_OPENED_EXISTING_KEY) {
			cout << " 已打开一个存在的注册表项: " << hKey << "\\" << SubKey << endl;
		}
		else if (dwDisposition == REG_CREATED_NEW_KEY) {
			cout << " 已新建一个注册表项: " << hKey << "\\" << SubKey << endl;
		}
	}

	// 设置值. 注意, RegSetValue的后两个参数仅适用于 REG_DWORD 类型的值, 其他情况参阅 Win32 api 文档
	// RegSetValueEx 必须与 RegCreateKeyEx 或者 RegOpenKeyEx 连用 (因为需要hKey句柄)
	RegSetValueEx(hKey, ValueName, 0, REG_DWORD, (LPBYTE)&data, sizeof(DWORD));

	// 关闭
	RegCloseKey(hKey);
	return 0;
}


bool is_number(string str)
{
	unsigned int i = 0;
	if (str.c_str()[0] != 45)
	{
		for (i = 0; i < str.length(); i++)
		{
			if (str.c_str()[i] < '0' || str.c_str()[i] > '9')
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		for (i = 1; i < str.length(); i++)
		{
			if (str.c_str()[i] < '0' || str.c_str()[i] > '9')
			{
				return false;
			}
		}
		return true;
	}
}

int menu() {
	int i = -1;
	string str;
	system("cls && color cf");
	cout << " ************* Menu ************* " << endl << endl;
	cout << " 1. 隐藏 关机&重启&睡眠 按钮 (重启后生效)" << endl;
	cout << " 2. 全部恢复 (重启后生效)" << endl;
	cout << " 3. 退出程序" << endl;
	cout << "\n ********************************" << endl << endl;
	cout << " 选择: ";
	cin >> str;
	if (is_number(str)) {
		i = atoi(str.c_str());
	}
	return i;
}

int main()
{
	system("title 隐藏开始菜单按钮 For Windows 7  ( v1.0.0 Built by Hui-Shao / 浅蓝的灯) & color cf & mode con cols=112 lines=32");

	// 若有需要,还可以添加 HideUserTile、HideAppList、HideSignOut 等 (可自行查看注册表)
	static const char* subkeys[] = {
		"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",
	};

	int choice = -1;

	while (1) {
		choice = menu();
		switch (choice)
		{
		default:
			// choice 为1~4 范围内的都是常规的设置选项
			if (choice == 1) {
				reg_rw(HKEY_LOCAL_MACHINE, subkeys[choice - 1], "NoClose", REG_DWORD, 1);
				cout << "\n 选项" << choice << "已完成，按任意键继续..." << endl;
				system("color 3f && pause>nul");
				break;
			}
			else {
				cout << " 请重新选择..." << endl;
				system("ping 127.0.0.1 -n 2 >nul");
				break;
			}
		case(2):
			for (unsigned int i = 0; i < sizeof(subkeys) / sizeof(subkeys[0]); i++) {
				reg_rw(HKEY_LOCAL_MACHINE, subkeys[i], "NoClose", REG_DWORD, 0);
			}
			cout << "\n 选项" << choice << "已完成，按任意键继续..." << endl;
			system("color 3f && pause>nul");
			if (MessageBox(NULL, "是否要立即重启? 记得保存好工作!\n如果重启失败, 可以尝试按下 Alt + F4 进行重启", "重启确认: ", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES) system("shutdown -r -t 0");
			break;
		case(3):
			exit(0);
		}
	}
	return 0;
}
