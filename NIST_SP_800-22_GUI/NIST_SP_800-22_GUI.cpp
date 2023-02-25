// NIST_SP_800-22_GUI.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "NIST_SP_800-22_GUI.h"
#include "log.h"
#include "shobjidl.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
HWND hEdit;                                   // 文本框
HWND hNumber;
HWND hButton;

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
int main(int argc, char* argv[]);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_NISTSP80022GUI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NISTSP80022GUI));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NISTSP80022GUI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_NISTSP80022GUI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 800, 600, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

DWORD WINAPI ThreadFunc(LPVOID lpParam) {
    int argc = ((int*)lpParam)[0];
    char** argv = (char**)((int*)lpParam + 1);

    // 在这里编写线程的代码，可以使用argc和argv参数

    main(argc, argv);

    EnableWindow(hButton, TRUE);
    return 0;
}
//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        hButton = CreateWindow(L"Button", L"打开文件并测试", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            10, 10, 150, 30, hWnd, (HMENU)IDB_OPEN, hInst, NULL);
        std::string dir_names[] = { "AlgorithmTesting", "BBS", "CCG", "G-SHA1", "LCG", "MODEXP", "MS", "QCG1", "QCG2", "XOR" };
        for (const auto& dname : dir_names) {
            std::filesystem::create_directories("experiments/" + dname + "/Frequency");
            std::filesystem::create_directories("experiments/" + dname + "/BlockFrequency");
            std::filesystem::create_directories("experiments/" + dname + "/Runs");
            std::filesystem::create_directories("experiments/" + dname + "/LongestRun");
            std::filesystem::create_directories("experiments/" + dname + "/Rank");
            std::filesystem::create_directories("experiments/" + dname + "/FFT");
            std::filesystem::create_directories("experiments/" + dname + "/NonOverlappingTemplate");
            std::filesystem::create_directories("experiments/" + dname + "/OverlappingTemplate");
            std::filesystem::create_directories("experiments/" + dname + "/Universal");
            std::filesystem::create_directories("experiments/" + dname + "/LinearComplexity");
            std::filesystem::create_directories("experiments/" + dname + "/Serial");
            std::filesystem::create_directories("experiments/" + dname + "/ApproximateEntropy");
            std::filesystem::create_directories("experiments/" + dname + "/CumulativeSums");
            std::filesystem::create_directories("experiments/" + dname + "/RandomExcursions");
            std::filesystem::create_directories("experiments/" + dname + "/RandomExcursionsVariant");
        }
        HFONT hFont = CreateFont(
            -16/*高度*/, -8/*宽度*/, 0/*不用管*/, 0/*不用管*/, 400,//设置字体粗细程度一般这个值设为400,
            FALSE/*不带斜体*/, FALSE/*不带下划线*/, FALSE/*不带删除线*/,
            DEFAULT_CHARSET,  //这里我们使用默认字符集，还有其他以 _CHARSET 结尾的常量可用
            OUT_CHARACTER_PRECIS, //输出精度
            CLIP_CHARACTER_PRECIS,  //剪裁精度
            DEFAULT_QUALITY,  //默认输出质量
            FF_DONTCARE,  //不指定字体族*/
            TEXT("微软雅黑")  //字体名
        );
        hEdit = CreateWindow(
            TEXT("EDIT"), //静态文本框的类名
            TEXT("..."),  //控件的文本
            WS_CHILD /*子窗口*/ | WS_VISIBLE /*创建时显示*/ | WS_BORDER /*带边框*/ | SS_LEFT | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | ES_READONLY | ES_WANTRETURN,
            10 /*X坐标*/, 50 /*Y坐标*/, 800 - 35 /*宽度*/, 600 - 120 /*高度*/,
            hWnd,  //父窗口句柄
            (HMENU)1,  //为控件指定一个唯一标识符
            hInst,  //当前程序实例句柄
            NULL
        );
        //设置控件字体
        SendMessage(
            hEdit,  //欲设置字体的控件句柄
            WM_SETFONT,  //消息名（消息类型）
            (WPARAM)hFont,  //字体句柄
            NULL  //传空值即可
        );

        hNumber = CreateWindowEx(WS_EX_CLIENTEDGE, // 扩展风格
            L"EDIT", // 控件类名
            L"1000", // 控件标题
            WS_CHILD | WS_VISIBLE | ES_NUMBER | ES_AUTOHSCROLL, // 控件风格
            355, 10, 60, 30, // 控件位置和大小
            hWnd, // 父窗口句柄
            (HMENU)ID_EDIT, // 控件ID
            hInst, // 程序实例句柄
            NULL); // 指向控件创建数据的指针
        SendMessage(hNumber, EM_LIMITTEXT, 10, 0);

        CreateWindowEx(
            0,                               // 扩展风格
            L"STATIC",                       // 控件类名
            L"Number of bitstreams:",                // 控件文本
            WS_CHILD | WS_VISIBLE,           // 控件风格
            200, 10, 150, 30,             // 控件位置和大小
            hWnd,                      // 父窗口句柄
            (HMENU)IDC_STATIC,                // 控件ID
            hInst,                       // 应用程序实例句柄
            NULL                             // 创建参数
        );

    }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case IDB_OPEN:
                HRESULT hr;
                hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
                    COINIT_DISABLE_OLE1DDE);
                if (SUCCEEDED(hr))
                {
                    IFileOpenDialog* pFileOpen;

                    // Create the FileOpenDialog object.
                    hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
                        IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

                    if (SUCCEEDED(hr))
                    {
                        // Show the Open dialog box.
                        hr = pFileOpen->Show(hWnd);

                        // Get the file name from the dialog box.
                        if (SUCCEEDED(hr))
                        {
                            IShellItem* pItem;
                            hr = pFileOpen->GetResult(&pItem);
                            if (SUCCEEDED(hr))
                            {
                                PWSTR pszFilePath;
                                hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                                // Display the file name to the user.
                                if (SUCCEEDED(hr))
                                {
                                    // Convert WChar to Multibyte
                                    DWORD dBufSize = WideCharToMultiByte(CP_OEMCP, 0, pszFilePath, -1, NULL, 0, NULL, FALSE);
                                    static char* dBuf = new char[dBufSize];
                                    memset(dBuf, 0, dBufSize);
                                    int nRet = WideCharToMultiByte(CP_OEMCP, 0, pszFilePath, -1, dBuf, dBufSize, NULL, FALSE);

                                    if (nRet > 0) {
                                        static char a1[10];
                                        WCHAR buf[10];
                                        GetWindowText(hNumber, buf, sizeof(buf));
                                        int value = _wtoi(buf);
                                        itoa(value, a1, 10);

                                        static char* argv[2];
                                        argv[0] = dBuf;
                                        argv[1] = a1;

                                        static HANDLE hThread = NULL;
                                        DWORD dwThreadId;

                                        static int threadArgs[3];
                                        threadArgs[0] = 2;
                                        memcpy(threadArgs + 1, argv, 2 * sizeof(char*));

                                        if (hThread != NULL) {
                                            CloseHandle(hThread);
                                            hThread = NULL;
                                        }

                                        EnableWindow(hButton, FALSE);
                                        hThread = CreateThread(NULL, 0, ThreadFunc, threadArgs, 0, &dwThreadId);

                                    // MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
                                    }
                                    CoTaskMemFree(pszFilePath);
                                }
                                pItem->Release();
                            }
                        }
                        pFileOpen->Release();
                    }
                    CoUninitialize();
                }
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
