// <version.h>
//
// Project owlnext-sample-listviewctrl-header
// Copyright (C) 2023 neige68
//
// Note: version
//
// Compiler: VC14.2
// Library:  OWL7
//

#ifndef version_h
#define version_h

//------------------------------------------------------------
//
// リリース番号
//
#define VER_RELEASE_STR                 "000"
#define VER_RELEASE                     0

#define VER_BUILD_STR                   "" // "" もしくは ".x"
#define VER_BUILD                       0

//
// 製作会社名
//
#define VER_COMPANYNAME                 "neige68"

//
// 製品バージョン
//
#undef VER_PRODUCTVERSION_STR
#undef VER_PRODUCTVERSION
#define VER_PRODUCTVERSION_STR          "0.00"
#define VER_PRODUCTVERSION              0,00,VER_RELEASE,VER_BUILD

//
// 製品名
//
#define VER_PRODUCTNAME                 "Sample"

// ファイルバージョン
#define VER_FILEVERSION_STR             "0.00." VER_RELEASE_STR VER_BUILD_STR
#define VER_FILEVERSION                 0,00,VER_RELEASE,VER_BUILD

// ファイル説明
#define VER_FILEDESCRIPTION             "OWLNext Sample ListViewCtrl Header"

// 著作権
#define VER_LEGALCOPYRIGHT_LASTYEAR     "2023"
#define VER_LEGALCOPYRIGHT              "Copyright (C) " VER_LEGALCOPYRIGHT_LASTYEAR " " VER_COMPANYNAME

//------------------------------------------------------------

#endif // version_h

// end of <version.h>
