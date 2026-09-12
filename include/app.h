#pragma once
#include "include/cef_app.h"

class App : public CefApp, public CefCommandLineHandler {
public:
    App();
    ~App() override;
    CefRefPtr<CefCommandLineHandler> GetCommandLineHandler() override { return this; }
    void OnBeforeCommandLineProcessing(const CefString&, CefRefPtr<CefCommandLine>) override;
    IMPLEMENT_REFCOUNTING(App);
    DISALLOW_COPY_AND_ASSIGN(App);
};
