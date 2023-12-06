// <sampldlg.h>
//
// Project owlnext-sample-listviewctrl-header
// Copyright (C) 2023 neige68
//
/// \file
/// \brief sampldlg
//
// Compiler: VC14.2
// Library:  OWL7
//

#ifndef sampldlg_h
#define sampldlg_h

#include <owl/colmnhdr.h>       // owl::THeaderHitTestInfo
#include <owl/commctrl.h>       // owl::TLvDispInfoNotify
#include <owl/listviewctrl.h>   // owl::TListViewCtrl

#include <sstream>              // std::ostringstream

#include "res.rh"               // Resource IDs

//------------------------------------------------------------
//
// \class TSampleDialog
//

class TSampleDialog : public owl::TDialog {

    // *** static ***
    /// ヘッダコントロールの元のウィンドウプロシージャ
    //
    /// これが static データメンバなので、このクラスは複数同時にインスタンス化できないことになる
    static WNDPROC HeaderWndProcOrig;

    /// ヘッダコントロールのウィンドウプロシージャ
    static LRESULT CALLBACK HeaderWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    // *** constructor ***
public:
    TSampleDialog(owl::TWindow* parent, int resourceId);

    // *** OWL override ***
    void SetupWindow() override;
    
    // *** response ***
    /// 表示内容
    void LVNGetDispInfo(owl::TLvDispInfoNotify& info);
    /// ウィンドウプロシージャ
    virtual owl::TResult WindowProc(owl::TMsgId msgId, owl::TParam1 param1, owl::TParam2 param2) override;

    // *** data ***
private:
    owl::TListViewCtrl* ListWindow;
    
DECLARE_RESPONSE_TABLE(TSampleDialog);
};

//------------------------------------------------------------

#endif // sampldlg_h

// end of <sampldlg.h>
