#include "app.h"

App::App() {}
App::~App() {}

void App::OnBeforeCommandLineProcessing(
    const CefString& process_type,
    CefRefPtr<CefCommandLine> command_line) {
    command_line->AppendSwitch("disable-gpu-compositing");
    command_line->AppendSwitch("disable-gpu");
    command_line->AppendSwitch("no-proxy-server");
}
