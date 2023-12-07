// <main.cpp>
//
// Project owlnext-sample-listviewctrl-header
// Copyright (C) 2023 neige68
//
// Note: main
//
// Compiler: VC14.2
// Library:  OWL7
//

#include "pch.h"
#pragma hdrstop

#include "sampldlg.h"           // TSampleDialog
#include "version.h"

#include <owl/string.h>         // owl::TString

#include <vector>               // std::vector

#include "res.rh"

//------------------------------------------------------------
//
// ODS - OutputDebugString
//

#ifdef NDEBUG
# define ODS(s) ((void)0)
#else
# define ODS(s)                                         \
    do {                                                \
        TDebugMonitorStarter::Instance();               \
        owl::tostringstream ODS_oss;                    \
        ODS_oss << s << std::endl;                      \
        ::OutputDebugString(ODS_oss.str().c_str());     \
    } while (0)
#endif

class TDebugMonitorStarter {    // デバッグモニタを始動
public:
    static TDebugMonitorStarter& Instance();
private:
    TDebugMonitorStarter() {
        PostMessage(HWND_BROADCAST, RegisterWindowMessage(_T("StartDebugMonitor")), GetCurrentProcessId(), 0);
        OutputDebugString(_T("StartDebugMonitor\r\n"));
    }
};

//static
TDebugMonitorStarter& TDebugMonitorStarter::Instance()
{
    static TDebugMonitorStarter instance;
    return instance;
};

//------------------------------------------------------------
//
// local
//

// システムのエラーメッセージを取得
// inserts は無視(そのまま)
static owl::tstring GetErrorMessage(DWORD id, DWORD dwLanguageId = 0)
{
    TCHAR* buf = 0;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS
                  | FORMAT_MESSAGE_MAX_WIDTH_MASK, 
                  0, id, dwLanguageId, (LPTSTR)&buf, 1, 0);
    owl::tstring result(buf ? buf : _T(""));
    LocalFree(buf);
    return result;
}

static owl::tstring LoadStr(UINT uID, HINSTANCE hInstance = 0)
{
    std::vector<TCHAR> buf(64);
    for (;;) {
        int r = LoadString(hInstance, uID, &buf.at(0), int(buf.size()));
        if (r == 0) {
            if (DWORD e = GetLastError())
                throw std::runtime_error{owl::TString{_T("LoadStr: ") + GetErrorMessage(e)}};
            throw std::runtime_error("LoadStr: no string resource. (id=" + std::to_string(uID) + ", hInstance=" + std::to_string(reinterpret_cast<INT_PTR>(hInstance)) + ")");
        }
        if (size_t(r) < buf.size() - 2) break;
        buf.resize(buf.size() * 2);
    }
    return &buf.at(0);
}

//------------------------------------------------------------
//
// class TVersionInfoDialog - バージョン情報ダイアログ
//

static void CenteringDlgItem(owl::TWindow& parent, int id)
{
    owl::TRect clientRect = parent.GetClientRect();
    HWND hwnd = parent.GetDlgItem(id);
    owl::TRect scRect;
    ::GetWindowRect(hwnd, &scRect);
    owl::TRect ccRect = parent.MapScreenToClient(scRect);
    owl::TScreenDC dc;
    dc.SelectObject(owl::TFont(parent.GetWindowFont()));
    owl::tstring text = parent.GetDlgItemText(id);
    int width = dc.GetTextExtent(text, int(text.length())).cx;
    ::SetWindowPos(hwnd, 0,
                   (clientRect.Width() - width) / 2, ccRect.top, width + 2, ccRect.Height(),
                   SWP_NOZORDER);
}

class TVersionInfoDialog : public owl::TDialog {
public:
    TVersionInfoDialog(TWindow* parent) : owl::TDialog(parent, IDD_VERSION) {}
    void SetupWindow() override {
        owl::TDialog::SetupWindow();
        //
        SetDlgItemText(IDC_PRODUCTNAME, owl::TString(VER_PRODUCTNAME));
        SetDlgItemText(IDC_COPYRIGHT, owl::TString(VER_LEGALCOPYRIGHT));
        // 横方向中央に移動
        CenteringDlgItem(*this, IDC_PRODUCTNAME);
        CenteringDlgItem(*this, IDC_COPYRIGHT);
    };
};

//------------------------------------------------------------
//
// class TMyClientWindow - アプリケーションフレームのクライアントウィンドウ
//

class TMyClientWindow : public owl::TWindow {

    // *** constructor ***
public:
    TMyClientWindow() : owl::TWindow(static_cast<TWindow*>(nullptr)) {}

};

//------------------------------------------------------------
//
// class TMyFrameWindow - アプリケーションのフレームウインドウ
//

class TMyFrameWindow : public owl::TFrameWindow {
public:
    TMyFrameWindow(LPCTSTR title, TWindow* clientWnd)
        : owl::TFrameWindow(/*parent*/nullptr, title, clientWnd) {
        AssignMenu(MAIN_MENU);
    }
};

//------------------------------------------------------------
//
// class TMyApp - アプリケーションクラス
//

class TMyApp : public owl::TApplication {
public:
    TMyApp(LPCTSTR title) : owl::TApplication(title) {}
    virtual void InitMainWindow() override;
    void CmHelpAbout();
    void CmSample();

    DECLARE_RESPONSE_TABLE(TMyApp);
};

DEFINE_RESPONSE_TABLE1(TMyApp, owl::TApplication)
    EV_COMMAND(CM_HELPABOUT, CmHelpAbout),
    EV_COMMAND(CM_SAMPLE, CmSample),
END_RESPONSE_TABLE;

void TMyApp::InitMainWindow() 
{
    TMyFrameWindow* frame = new TMyFrameWindow{GetName(), new TMyClientWindow};
    frame->SetIcon(this, IDI_APP);
    frame->SetIconSm(this, IDI_APP);
    SetMainWindow(frame);
}

void TMyApp::CmHelpAbout()
{
    TVersionInfoDialog(GetMainWindow()).Execute();
}

void TMyApp::CmSample()
{
    TSampleDialog{GetMainWindow(), IDD_SAMPLE}.Execute();
}

//------------------------------------------------------------
//
// OwlMain 
//

int OwlMain(int argc, TCHAR** argv)
{
    owl::tstring title = _T("(title not loaded)");
    int result = -1;
    try {
        title = LoadStr(IDS_APPNAME);
        TMyApp app{title.c_str()};
        result = app.Run();
        ODS("OwlMain|result=" << result);
    }
    catch (const std::exception& x) {
        MessageBox(0, owl::TString{x.what()}, title.c_str(), MB_ICONSTOP | MB_OK);
    }
    catch (...) {
        MessageBox(0, _T("Unexpected exception."), title.c_str(), MB_ICONSTOP | MB_OK);
    }
    return result;
}

//------------------------------------------------------------

// end of <main.cpp>
