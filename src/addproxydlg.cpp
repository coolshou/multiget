/***************************************************************************
*            addproxydlg.cpp
*
*  Wed Oct 25 21:48:58 2006
*  Copyright  2006  liubin, China
*  Email multiget@gmail.com
****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#include "addproxydlg.h"
#include "proxydlg.h"
#include "mgapp.h"
#include <wx/sizer.h>
#include <wx/valgen.h>

#define  _MGSTR(s) wxGetApp().GetWxStr(s)

CAddProxy::CAddProxy( CProxyDlg* parent )
        : wxDialog( parent, wxID_ANY, _MGSTR( _S_PROXYDLG_ADDPROXY ), wxDefaultPosition, wxSize( 400, 300 ) /*,wxRESIZE_BORDER*/ )
{
    m_pParent = parent;
    m_port = 0;
    Init();
}

CAddProxy::~CAddProxy()
{}

void CAddProxy::Init()
{
    wxBoxSizer * all = new wxBoxSizer( wxVERTICAL );
    wxBoxSizer* name = new wxStaticBoxSizer( wxHORIZONTAL, this, _MGSTR( _S_ADDPROXYDLG_PROXYNAME ) );

    name->Add(
        new wxTextCtrl( this, -1, wxT( "" ), wxDefaultPosition, wxDefaultSize, 0, wxGenericValidator( &m_name ) ),
        100, wxALL );
    all->Add( name, 0, wxEXPAND );

    wxBoxSizer* mid = new wxBoxSizer( wxHORIZONTAL );
    wxBoxSizer* arg = new wxStaticBoxSizer( wxVERTICAL, this, _MGSTR( _S_ADDPROXYDLG_PROXYARGS ) );
    arg->AddSpacer( 5 );
    arg->Add( new wxStaticText( this, -1, _MGSTR( _S_ADDPROXYDLG_SERVER ) ) );
    arg->Add( new wxTextCtrl( this, -1, wxT( "" ), wxDefaultPosition, wxSize( 180, 25 ), 0, wxGenericValidator( &m_server ) ), 0, wxALL );
    arg->Add( new wxStaticText( this, -1, _MGSTR( _S_ADDPROXYDLG_PORT ) ) );
    arg->Add( new wxTextCtrl( this, -1, wxT( "" ), wxDefaultPosition, wxSize( 180, 25 ), 0, wxGenericValidator( &m_port ) ), 0, wxALL );
    arg->Add( new wxStaticText( this, -1, _MGSTR( _S_ADDPROXYDLG_USER ) ) );
    arg->Add( new wxTextCtrl( this, -1, wxT( "" ), wxDefaultPosition, wxSize( 180, 25 ), 0, wxGenericValidator( &m_user ) ), 0, wxALL );
    arg->Add( new wxStaticText( this, -1, _MGSTR( _S_ADDPROXYDLG_PASS ) ) );
    arg->Add( new wxTextCtrl( this, -1, wxT( "" ), wxDefaultPosition, wxSize( 180, 25 ), 0, wxGenericValidator( &m_pass ) ), 0, wxALL );
    arg->SetMinSize( 200, 200 );
    mid->Add( arg, 0, wxEXPAND );
    mid->AddSpacer( 20 );

    wxString choices[ 6 ] =
        {
            wxT( "socks auto version" ),
            wxT( "socks version 4" ),
            wxT( "socks version 4a" ),
            wxT( "socks version 5 " ),
            wxT( "ftp proxy" ),
            wxT( "http proxy" )
        };
    mid->Add(
        new wxRadioBox( this, -1, _MGSTR( _S_ADDPROXYDLG_PROXYTYPE ), wxDefaultPosition, wxSize( 180, 200 ), 6, choices, 0, wxRA_SPECIFY_ROWS, wxGenericValidator( &m_type ) ),
        0,
        wxEXPAND | wxALIGN_RIGHT );

    all->Add( mid, 0, wxEXPAND );


    wxBoxSizer* but = new wxBoxSizer( wxHORIZONTAL );


    but->Add( new wxButton( this, wxID_CANCEL, wxT( "Cancel" ) ), 0, wxALL, 5 );
    but->Add( new wxButton( this, wxID_OK, wxT( "OK" ) ), 0, wxALL, 5 );
    all->Add( but, 0, wxALIGN_RIGHT );

    SetSizer( all );
}

