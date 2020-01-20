#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <string>
#include <vector>
using namespace std;
#define ID_TB_EXPRESSION 	0
#define ID_BTN_1		1
#define ID_BTN_2		2
#define ID_BTN_3		3
#define ID_BTN_4		4
#define ID_BTN_5		5
#define ID_BTN_6		6
#define ID_BTN_7		7
#define ID_BTN_8		8
#define ID_BTN_9		9
#define ID_BTN_0		10
#define ID_BTN_COMMA		11
#define ID_BTN_EQUAL		12
#define ID_BTN_BACKSPACE	13
#define ID_BTN_DIV		14
#define ID_BTN_MUL		15
#define ID_BTN_SUB		16
#define ID_BTN_ADD		17
#define ID_BTN_MEMORY_SAVE	18
#define ID_BTN_MEMORY_READ	19
#define ID_BTN_CLEAR		20

HWND tbExpression,
btn1, btn2, btn3, btn4, btn5, btn6, btn7, btn8, btn9, btn0,
btnComma, btnEqual, btnBackSpace, btnDiv, btnMul, btnSub, btnAdd,
btnMemorySave, btnMemoryRead, btnClear;
int margin = 2,
tbWidth = 408, tbHeight = 30,
btnWidth = 80, btnHeight = 50;
const int STRING_LENGTH = 50;
WCHAR buf[STRING_LENGTH];
WCHAR memory[STRING_LENGTH];
vector<string> operands = vector<string>();
vector<char> operators = vector<char>();
bool operatorIsLast = false;
bool pointCharIsLast = false;
bool exFraseWasPrinted = false;
bool isCommaSet = false;



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void InsertToExpression(const LPCWSTR wc);
void BackSpaceInExpression();
void ClearExpression();
void Equal();
bool TryParseInt(const string s);
bool TryParseDouble(const string s);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Create the window.

	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Calculator",					// Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, 450, 310,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if (hwnd == NULL) {
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

	// Run the message loop.

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	int XOffsetY1 = 10;
	int XOffsetY2 = 10 + btnWidth + margin;
	int XOffsetY3 = 10 + btnWidth * 2 + margin * 2;
	int XOffsetY4 = 10 + btnWidth * 3 + margin * 3;
	int XOffsetY5 = 10 + btnWidth * 4 + margin * 4;

	int YOffsetX1 = 10 + tbHeight + margin;
	int YOffsetX2 = 10 + tbHeight + btnHeight + margin * 2;
	int YOffsetX3 = 10 + tbHeight + btnHeight * 2 + margin * 3;
	int YOffsetX4 = 10 + tbHeight + btnHeight * 3 + margin * 4;

	switch (uMsg) {
		case WM_CREATE:

			tbExpression = CreateWindow(L"edit", L"0",
										WS_VISIBLE | WS_CHILD | WS_BORDER,
										10, 10, tbWidth, tbHeight,
										hwnd, (HMENU)ID_TB_EXPRESSION, NULL, NULL);

			btn7 = CreateWindow(L"button", L"7",
								WS_VISIBLE | WS_CHILD | WS_BORDER,
								XOffsetY1, YOffsetX1, btnWidth, btnHeight,
								hwnd, (HMENU)ID_BTN_7, NULL, NULL);

			btn8 = CreateWindow(L"button", L"8",
								WS_VISIBLE | WS_CHILD | WS_BORDER,
								XOffsetY2, YOffsetX1, btnWidth, btnHeight,
								hwnd, (HMENU)ID_BTN_8, NULL, NULL);

			btn9 = CreateWindow(L"button", L"9",
								WS_VISIBLE | WS_CHILD | WS_BORDER,
								XOffsetY3, YOffsetX1, btnWidth, btnHeight,
								hwnd, (HMENU)ID_BTN_9, NULL, NULL);

			btnDiv = CreateWindow(L"button", L"/",
								  WS_VISIBLE | WS_CHILD | WS_BORDER,
								  XOffsetY4, YOffsetX1, btnWidth, btnHeight,
								  hwnd, (HMENU)ID_BTN_DIV, NULL, NULL);

			btnBackSpace = CreateWindow(L"button", L"<-",
										WS_VISIBLE | WS_CHILD | WS_BORDER,
										XOffsetY5, YOffsetX1, btnWidth, btnHeight,
										hwnd, (HMENU)ID_BTN_BACKSPACE, NULL, NULL);

			btn4 = CreateWindow(L"button", L"4",
								WS_VISIBLE | WS_CHILD | WS_BORDER,
								XOffsetY1, YOffsetX2, btnWidth, btnHeight,
								hwnd, (HMENU)ID_BTN_4, NULL, NULL);

			btn5 = CreateWindow(L"button", L"5",
								WS_VISIBLE | WS_CHILD | WS_BORDER,
								XOffsetY2, YOffsetX2, btnWidth, btnHeight,
								hwnd, (HMENU)ID_BTN_5, NULL, NULL);

			btn6 = CreateWindow(L"button", L"6",
								WS_VISIBLE | WS_CHILD | WS_BORDER,
								XOffsetY3, YOffsetX2, btnWidth, btnHeight,
								hwnd, (HMENU)ID_BTN_6, NULL, NULL);

			btnMul = CreateWindow(L"button", L"Х",
								  WS_VISIBLE | WS_CHILD | WS_BORDER,
								  XOffsetY4, YOffsetX2, btnWidth, btnHeight,
								  hwnd, (HMENU)ID_BTN_MUL, NULL, NULL);

			btnClear = CreateWindow(L"button", L"C",
									WS_VISIBLE | WS_CHILD | WS_BORDER,
									XOffsetY5, YOffsetX2, btnWidth, btnHeight,
									hwnd, (HMENU)ID_BTN_CLEAR, NULL, NULL);

			btn1 = CreateWindow(L"button", L"1",
								WS_VISIBLE | WS_CHILD | WS_BORDER,
								XOffsetY1, YOffsetX3, btnWidth, btnHeight,
								hwnd, (HMENU)ID_BTN_1, NULL, NULL);

			btn2 = CreateWindow(L"button", L"2",
								WS_VISIBLE | WS_CHILD | WS_BORDER,
								XOffsetY2, YOffsetX3, btnWidth, btnHeight,
								hwnd, (HMENU)ID_BTN_2, NULL, NULL);

			btn3 = CreateWindow(L"button", L"3",
								WS_VISIBLE | WS_CHILD | WS_BORDER,
								XOffsetY3, YOffsetX3, btnWidth, btnHeight,
								hwnd, (HMENU)ID_BTN_3, NULL, NULL);

			btnSub = CreateWindow(L"button", L"-",
								  WS_VISIBLE | WS_CHILD | WS_BORDER,
								  XOffsetY4, YOffsetX3, btnWidth, btnHeight,
								  hwnd, (HMENU)ID_BTN_SUB, NULL, NULL);

			btnMemorySave = CreateWindow(L"button", L"MS",
										 WS_VISIBLE | WS_CHILD | WS_BORDER,
										 XOffsetY5, YOffsetX3, btnWidth, btnHeight,
										 hwnd, (HMENU)ID_BTN_MEMORY_SAVE, NULL, NULL);

			btn0 = CreateWindow(L"button", L"0",
								WS_VISIBLE | WS_CHILD | WS_BORDER,
								XOffsetY1, YOffsetX4, btnWidth, btnHeight,
								hwnd, (HMENU)ID_BTN_0, NULL, NULL);

			btnComma = CreateWindow(L"button", L",",
									WS_VISIBLE | WS_CHILD | WS_BORDER,
									XOffsetY2, YOffsetX4, btnWidth, btnHeight,
									hwnd, (HMENU)ID_BTN_COMMA, NULL, NULL);

			btnEqual = CreateWindow(L"button", L"=",
									WS_VISIBLE | WS_CHILD | WS_BORDER,
									XOffsetY3, YOffsetX4, btnWidth, btnHeight,
									hwnd, (HMENU)ID_BTN_EQUAL, NULL, NULL);

			btnAdd = CreateWindow(L"button", L"+",
								  WS_VISIBLE | WS_CHILD | WS_BORDER,
								  XOffsetY4, YOffsetX4, btnWidth, btnHeight,
								  hwnd, (HMENU)ID_BTN_ADD, NULL, NULL);

			btnMemoryRead = CreateWindow(L"button", L"MR",
										 WS_VISIBLE | WS_CHILD | WS_BORDER,
										 XOffsetY5, YOffsetX4, btnWidth, btnHeight,
										 hwnd, (HMENU)ID_BTN_MEMORY_READ, NULL, NULL);
			break;

		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case ID_BTN_0:
					InsertToExpression(L"0");
					break;

				case ID_BTN_1:
					InsertToExpression(L"1");
					break;

				case ID_BTN_2:
					InsertToExpression(L"2");
					break;

				case ID_BTN_3:
					InsertToExpression(L"3");
					break;

				case ID_BTN_4:
					InsertToExpression(L"4");
					break;

				case ID_BTN_5:
					InsertToExpression(L"5");
					break;

				case ID_BTN_6:
					InsertToExpression(L"6");
					break;

				case ID_BTN_7:
					InsertToExpression(L"7");
					break;

				case ID_BTN_8:
					InsertToExpression(L"8");
					break;

				case ID_BTN_9:
					InsertToExpression(L"9");
					break;

				case ID_BTN_BACKSPACE:
					BackSpaceInExpression();
					break;

				case ID_BTN_CLEAR:
					ClearExpression();
					break;

				case ID_BTN_DIV:
					InsertToExpression(L"/");
					break;

				case ID_BTN_MUL:
					InsertToExpression(L"*");
					break;

				case ID_BTN_SUB:
					InsertToExpression(L"-");
					break;

				case ID_BTN_ADD:
					InsertToExpression(L"+");
					break;

				case ID_BTN_COMMA:
					InsertToExpression(L".");
					break;

				case ID_BTN_EQUAL:
					Equal();
					break;
				case ID_BTN_MEMORY_SAVE:
					Equal();
					if (!exFraseWasPrinted) GetWindowText(tbExpression, (LPWSTR)memory, STRING_LENGTH);
					GetWindowText(tbExpression, buf, STRING_LENGTH);
					break;
				case ID_BTN_MEMORY_READ:
					if (wstring(buf) == L"0" && memory != L"") {
						SetWindowText(tbExpression, L"");
						SetWindowText(tbExpression, memory);
					}
					else {
						SetWindowText(tbExpression, (wstring(buf) + memory).c_str());
					}
					GetWindowText(tbExpression, buf, STRING_LENGTH);
					break;
			}
			return 0;

		case WM_KEYDOWN:
			switch (wParam) {
				case 0x30:
				case VK_NUMPAD0:
					SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(ID_BTN_0, BN_CLICKED), (LPARAM)btn0);
					break;

				case 0x31:
				case VK_NUMPAD1:
					SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(ID_BTN_1, BN_CLICKED), (LPARAM)btn1);
					break;

				case 0x32:
				case VK_NUMPAD2:
					SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(ID_BTN_2, BN_CLICKED), (LPARAM)btn2);
					break;

				case 0x33:
				case VK_NUMPAD3:
					SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(ID_BTN_3, BN_CLICKED), (LPARAM)btn3);
					break;

				case 0x34:
				case VK_NUMPAD4:
					SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(ID_BTN_4, BN_CLICKED), (LPARAM)btn4);
					break;

				case 0x35:
				case VK_NUMPAD5:
					SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(ID_BTN_5, BN_CLICKED), (LPARAM)btn5);
					break;

				case 0x36:
				case VK_NUMPAD6:
					SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(ID_BTN_6, BN_CLICKED), (LPARAM)btn6);
					break;

				case 0x37:
				case VK_NUMPAD7:
					SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(ID_BTN_7, BN_CLICKED), (LPARAM)btn7);
					break;

				case 0x38:
				case VK_NUMPAD8:
					SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(ID_BTN_8, BN_CLICKED), (LPARAM)btn8);
					break;

				case 0x39:
				case VK_NUMPAD9:
					SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(ID_BTN_9, BN_CLICKED), (LPARAM)btn9);
					break;

				case VK_BACK:
					SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(ID_BTN_BACKSPACE, BN_CLICKED), (LPARAM)btnBackSpace);
					break;

				case VK_ESCAPE:
					SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(ID_BTN_CLEAR, BN_CLICKED), (LPARAM)btnClear);
					break;
			}
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);



			FillRect(hdc, &ps.rcPaint, HBRUSH(COLOR_WINDOW + 1));

			EndPaint(hwnd, &ps);
		}
					 return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void InsertToExpression(LPCWSTR wc) {
	if (exFraseWasPrinted) {
		exFraseWasPrinted = false;
		SetWindowText(tbExpression, L"0");
	}
	GetWindowText(tbExpression, buf, STRING_LENGTH);
	if (wstring(buf) == L"0") {
		if (wc == L"1" || wc == L"2" || wc == L"3" || wc == L"4" || wc == L"5" || wc == L"6" || wc == L"7" || wc == L"8" || wc == L"9") {
			SetWindowText(tbExpression, wc);
		}
		else if (wc == L".") {
			SetWindowText(tbExpression, (wstring(buf) + wc).c_str());
		}
		else if (wc == L"/" || wc == L"*" || wc == L"-" || wc == L"+") {
			SetWindowText(tbExpression, (wstring(buf) + wc).c_str());
		}
	}
	else {
		WCHAR bufLastChar = wstring(buf)[wstring(buf).size() - 1];
		if (bufLastChar == (WCHAR)'0' || bufLastChar == (WCHAR)'1' || bufLastChar == (WCHAR)'2' || bufLastChar == (WCHAR)'3' || bufLastChar == (WCHAR)'4' || bufLastChar == (WCHAR)'5' ||
			bufLastChar == (WCHAR)'6' || bufLastChar == (WCHAR)'7' || bufLastChar == (WCHAR)'8' || bufLastChar == (WCHAR)'9') {
			if (wc == L"0" || wc == L"1" || wc == L"2" || wc == L"3" || wc == L"4" || wc == L"5" || wc == L"6" || wc == L"7" || wc == L"8" || wc == L"9") {
				SetWindowText(tbExpression, (wstring(buf) + wc).c_str());
			}
			else if (wc == L"." && isCommaSet) {
				SetWindowText(tbExpression, (wstring(buf) + wc).c_str());
				isCommaSet = true;
			}
			else if (wc == L"/" || wc == L"*" || wc == L"-" || wc == L"+") {
				SetWindowText(tbExpression, (wstring(buf) + wc).c_str());
			}
		}
		else if (bufLastChar == (WCHAR)L'.') {
			if (wc == L"0" || wc == L"1" || wc == L"2" || wc == L"3" || wc == L"4" || wc == L"5" || wc == L"6" || wc == L"7" || wc == L"8" || wc == L"9") {
				SetWindowText(tbExpression, (wstring(buf) + wc).c_str());
			}
			else if (wc == L"/" || wc == L"*" || wc == L"-" || wc == L"+") {
				SetWindowText(tbExpression, (wstring(buf) + L"0" + wc).c_str());
			}
		}
		else if (bufLastChar == (WCHAR)'/' || bufLastChar == (WCHAR)'*' || bufLastChar == (WCHAR)'-' || bufLastChar == (WCHAR)'+') {
			if (wc == L"0" || wc == L"1" || wc == L"2" || wc == L"3" || wc == L"4" || wc == L"5" || wc == L"6" || wc == L"7" || wc == L"8" || wc == L"9") {
				SetWindowText(tbExpression, (wstring(buf) + wc).c_str());
			}
			else if (wc == L".") {
				SetWindowText(tbExpression, (wstring(buf) + L"0" + wc).c_str());
			}
			else if (wc == L"/" || wc == L"*" || wc == L"-" || wc == L"+") {
				wstring temp = wstring(buf);
				temp.pop_back();
				temp += wc;
				SetWindowText(tbExpression, temp.c_str());
			}
		}
	}
	GetWindowText(tbExpression, buf, STRING_LENGTH);
}

void BackSpaceInExpression() {
	// if textBox.text.length == 0 : do nothing
	// else : delete last char
	using namespace std;
	wstring temp;

	GetWindowText(tbExpression, buf, STRING_LENGTH);
	temp = wstring(buf);
	if (temp != L"0" && temp.size() > 0) {
		temp.pop_back();
		if (temp.empty()) {
			temp = L"0";
		}
		SetWindowText(tbExpression, temp.c_str());
	}
}

void ClearExpression() {
	SetWindowText(tbExpression, L"0");
	operands.clear();
	operators.clear();
	GetWindowText(tbExpression, buf, STRING_LENGTH);
	operatorIsLast = false;
}

bool TryParseInt(const string s) {
	return to_string(stoi(s)) == s;
}

bool TryParseDouble(const string s) {
	return to_string(stod(s)) == s;
}

void Equal() {
	vector<string> operands = vector<string>();
	vector<char> operators = vector<char>();
	double operand;
	double result = 0;
	bool operatorCharLast = false;
	wstring ws = wstring(buf);
	string expr = string(ws.begin(), ws.end());
	char symbol;
	LPCWSTR ZERO_DIV_EX_FRASE = L"cannot be divided by zero";

	for (int i = 0; i < expr.size(); i++) {
		symbol = expr[i];
		switch (symbol) {
			case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '.':
				if (operands.empty()) {
					operands.push_back(string(1, symbol));
				}
				else if (operatorCharLast) {
					operands.push_back(string(1, symbol));
				}
				else {
					operands[operands.size() - 1] += symbol;
				}
				operatorCharLast = false;
				break;
			case '/': case '*': case '-': case '+':
				operatorCharLast = true;
				operators.push_back(symbol);
				break;
		}
	}
	if (operands.empty()) return;
	else result = stod(operands[0]);
	for (int i = 1; i < operands.size(); i++) {
		switch (operators[i - 1]) {
			case '/':
				if (stod(operands[i]) == 0) {
					SetWindowText(tbExpression, ZERO_DIV_EX_FRASE);
					exFraseWasPrinted = true;
					return;
				}
				result /= stod(operands[i]);
				break;
			case '*':
				result *= stod(operands[i]);
				break;
			case '-':
				result -= stod(operands[i]);
				break;
			case '+':
				result += stod(operands[i]);
				break;
		}
	}
	string sTemp;
	if ((double)(int)(result) == result) {
		sTemp = to_string((int)result);
	}
	else {
		sTemp = to_string(result);
	}
	wstring wsTemp = wstring(sTemp.begin(), sTemp.end());
	SetWindowText(tbExpression, wsTemp.c_str());
}
