#include "client.h"

Client::Client() {}
Client::~Client() {}

CefRefPtr<CefLifeSpanHandler> Client::GetLifeSpanHandler() { return this; }
CefRefPtr<CefLoadHandler> Client::GetLoadHandler() { return this; }

void Client::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    browser_ = browser;
}

void Client::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
    CefQuitMessageLoop();
}

void Client::OnLoadEnd(CefRefPtr<CefBrowser> browser,
                       CefRefPtr<CefFrame> frame,
                       int httpStatusCode) {
    if (frame->IsMain()) {
        std::string js =
            "(function(){"
            "var c=document.cookie;"
            "var r={"
            "logged_in:c.indexOf('sessionid=')>=0,"
            "sessionid:c.indexOf('sessionid=')>=0,"
            "sid_guard:c.indexOf('sid_guard=')>=0,"
            "passport_csrf_token:c.indexOf('passport_csrf_token=')>=0,"
            "uid_tt:c.indexOf('uid_tt=')>=0,"
            "sid_tt:c.indexOf('sid_tt=')>=0,"
            "s_v_web_id:c.indexOf('s_v_web_id=')>=0,"
            "ttwid:c.indexOf('ttwid=')>=0,"
            "odin_tt:c.indexOf('odin_tt=')>=0,"
            "x_tt_token:c.indexOf('x_tt_token=')>=0"
            "};"
            "return JSON.stringify(r);"
            "})()";
        frame->ExecuteJavaScript(js, frame->GetURL(), 0);
    }
}
