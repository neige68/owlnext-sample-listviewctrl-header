-*- coding: utf-8 -*-

# owlnext-sample-listviewctrl-header リストビューコントロールのカラムヘッダのダブルクリックを受け取りたい

TListViewCtrl インスタンスを生成し、その GetHeaderCtrl メンバでカラムヘッダコントロールのウィンドウハンドルを取得し、サブクラス化を行って、左ダブルクリックを検出し、ヒットテストでダブルクリックされたカラムを特定し、親の親であるダイアログにカラム番号を付けてローカルコマンドをポストすることにした。

sampldlg.h, sampldlg.cpp の class TSampleDialog を参照のこと。
