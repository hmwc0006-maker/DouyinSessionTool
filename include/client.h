#pragma once
#include "include/cef_client.h"
#include "include/cef_life_span_handler.h"
#include "include/cef_load_handler.h"
#include <string>

class Client : public CefClient, public CefLifeSpanHandler, public CefLoadHandler {
public:
    Client();
    ~Client() override;
    CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override;
    CefRefPtr<CefLoadHandler> GetLoadHandler() override;
    void OnAfterCreated(CefRefPtr<CefBrowser>) override;
    void OnBeforeClose(CefRefPtr<CefBrowser>) override;
    void OnLoadEnd(CefRefPtr<CefBrowser>, CefRefPtr<CefFrame>, int) override;
private:
    CefRefPtr<CefBrowser> browser_;
    IMPLEMENT_REFCOUNTING(Client);
    DISALLOW_COPY_AND_ASSIGN(Client);
};
