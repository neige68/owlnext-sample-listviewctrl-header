// <misc.cpp>
//
// Project owlnext-sample-listviewctrl-header
// Copyright (C) 2023 neige68
//
/// \file
/// \brief misc
//
// Compiler: VC14.2
// Library:  OWL7
//

#include "pch.h"
#pragma hdrstop

#include "misc.h"

//------------------------------------------------------------
//
// class TDebugMonitorStarter
//

//static
TDebugMonitorStarter& TDebugMonitorStarter::Instance()
{
    static TDebugMonitorStarter instance;
    return instance;
};

//
// end of class TDebugMonitorStarter
//
//------------------------------------------------------------

// end of <misc.cpp>
