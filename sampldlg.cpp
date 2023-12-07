// <sampldlg.cpp>
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

#include "pch.h"
#pragma hdrstop

#include "sampldlg.h"

#include "misc.h"

using namespace std;
using namespace owl;

//------------------------------------------------------------
//
/// \class THeaderControl
//
/// �w�b�_�R���g���[�����T�u�N���X��
//

class THeaderControl : public TControl {
public:
    THeaderControl(HWND handle) : TControl(handle) {}
    void EvLButtonDblClk(uint modKeys, const TPoint& point);

DECLARE_RESPONSE_TABLE(THeaderControl);
};

DEFINE_RESPONSE_TABLE1(THeaderControl, TControl)
    EV_WM_LBUTTONDBLCLK,
END_RESPONSE_TABLE;

void THeaderControl::EvLButtonDblClk(uint modKeys, const TPoint& point)
{
    THeaderHitTestInfo info{point}; // HD_HITTESTINFO �Ɠ���
    SendMessage(HDM_HITTEST, 0, TParam2(&info));
    int col = info.iItem;
    // �_�C�A���O�ɃR�}���h�Ƃ��đ��M
    if (auto listViewCtrl = GetParentO())
        if (auto dlg = listViewCtrl->GetParentO()) {
            dlg->PostMessage(WM_COMMAND, CM_LOCAL, col);
            return;
        }
    TControl::EvLButtonDblClk(modKeys, point);
}

//------------------------------------------------------------
//
// class TSampleDialog
//

DEFINE_RESPONSE_TABLE1(TSampleDialog, TDialog)
    EV_LVN_GETDISPINFO(IDC_LISTVIEW, LVNGetDispInfo),
END_RESPONSE_TABLE;

TSampleDialog::TSampleDialog(TWindow* parent, int resourceId)
    : TDialog(parent, resourceId), HeaderControl(nullptr)
{
    ListWindow = new TListViewCtrl{this, IDC_LISTVIEW};
    ListWindow->Attr.Style |= LVS_REPORT;
}

void TSampleDialog::SetupWindow() 
{
    TDialog::SetupWindow();
    //
    ListWindow->ModifyStyle(LVS_NOSORTHEADER, 0);
    ListWindow->ModifyStyle(LVS_NOCOLUMNHEADER, 0);
    // �w�b�_�R���g���[���̃T�u�N���X��
    HeaderControl = new THeaderControl(ListWindow->GetHeaderCtrl());
    //
    for (int i = 0; i < 5; i++) {
        TCHAR title[10];
        _stprintf_s(title, _T("col%d"), i);
        ListWindow->InsertColumn(i, TLvColumn{title, 100});
    }
    for (int i = 0; i < 4; i++) {
        TCHAR title[10];
        _stprintf_s(title, _T("row%d"), i);
        ListWindow->AddItem(TLvItem{title});
    }
}

void TSampleDialog::CleanupWindow()
{
    delete HeaderControl;
    HeaderControl = nullptr;
    //
    TDialog::CleanupWindow();
}

// �\�����e
void TSampleDialog::LVNGetDispInfo(TLvDispInfoNotify& info)
{
    static_assert(is_same<decltype(info.item), LVITEM>::value, "info.item == LVITEM");
    int index = info.item.iItem;
    int sub = info.item.iSubItem;
    static TCHAR buffer[20];
    _stprintf_s(buffer, _T("row#%d,col#%d"), index, sub);
    //
    // LVITEMA structure �̃h�L�������g�� pszText �̍��ł́AWhen
    // responding to an LVN_GETDISPINFO notification, be sure that
    // this pointer remains valid until after the next notification
    // has been received. �Ƃ̂��ƂȂ̂ŁA�ÓI�ϐ��Ɋm�ۂ���������o�b
    // �t�@�̃A�h���X��Ԃ��B
    //
    info.item.pszText = buffer;
}

// �E�B���h�E�v���V�[�W��
TResult TSampleDialog::WindowProc(TMsgId msgId, TParam1 param1, TParam2 param2) 
{
    // �w�b�_�̃_�u���N���b�N�R�}���h���󂯎��
    // param2 ���g�p���Ă���̂ł�����
    if (msgId == WM_COMMAND && param1 == CM_LOCAL) {
        TCHAR msg[80];
        _stprintf_s(msg, _T("�w�b�_�� #%d ���_�u���N���b�N����܂���"), int(param2));
        MessageBox(msg, _T("�_�u���N���b�N"), MB_OK | MB_ICONINFORMATION);
        return 1;
    }
    return TDialog::WindowProc(msgId, param1, param2);
}

//
// end of class TSampleDialog
//
//------------------------------------------------------------

// end of <sampldlg.cpp>
