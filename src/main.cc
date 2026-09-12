#include <windows.h>
#include <string>
#include "include/cef_app.h"
#include "include/cef_browser.h"
#include "app.h"
#include "client.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int) {
    CefMainArgs main_args(hInstance);

    int exit_code = CefExecuteProcess(main_args, nullptr, nullptr);
    if (exit_code >= 0) {
        return exit_code;
    }

    CefSettings settings;
    settings.no_sandbox = true;
    settings.multi_threaded_message_loop = false;

    std::wstring cache_path = L"DouyinSessionTool_Profile";
    CefString(&settings.cache_path).FromWString(cache_path);
    CefString(&settings.log_file).FromWString(L"debug.log");
    settings.log_severity = LOGSEVERITY_INFO;

    CefRefPtr<App> app(new App());

    if (!CefInitialize(main_args, settings, app.get(), nullptr)) {
        return 1;
    }

    WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = DefWindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = L"DouyinSessionTool";
    RegisterClassEx(&wc);

    HWND hWnd = CreateWindowEx(0, L"DouyinSessionTool", L"Douyin Session Tool",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 1200, 700,
        NULL, NULL, hInstance, NULL);

    CefWindowInfo window_info;
    window_info.SetAsChild(hWnd, CefRect(0, 0, 850, 700));

    CefBrowserSettings browser_settings;
    CefRefPtr<Client> client(new Client());

    CefBrowserHost::CreateBrowser(window_info, client, L"https://www.douyin.com",
        browser_settings, nullptr, nullptr);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        CefDoMessageLoopWork();
    }

    CefShutdown();
    return 0;
}
