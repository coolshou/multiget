
/*
      	文件名	:	taskdetailreport.cpp
        建立日期	:	2006/07/25
        作者		:	liubin
        EMAIL	:	multiget@gmail.com
        版本		:	0.5	
		
  		这个类用于在右下显示已经停止的任务的信息
		
		2006/07/29	新增OnSize，OnColumnResize函数处理窗口变化
 
*/
#include "taskdetailreport.h"
#include "mgapp.h"

//#include <iostream>

using namespace std;

BEGIN_EVENT_TABLE( CTaskDetailReport, wxListView )
EVT_CUSTOM( wxEVT_SIZE, wxID_ANY, CTaskDetailReport::OnSize )
EVT_LIST_COL_END_DRAG( wxID_ANY, CTaskDetailReport::OnColumnResize )
EVT_ERASE_BACKGROUND( CTaskDetailReport::OnErase )
END_EVENT_TABLE()

#define _MGSTR(s) wxGetApp().GetWxStr(s)

CTaskDetailReport::CTaskDetailReport( wxWindow* parent )
        : wxListView( parent, wxID_ANY, wxDefaultPosition,
                      wxSize( 0, 0 ), wxLC_REPORT | wxLC_SINGLE_SEL )
{

    SetBackgroundStyle( wxBG_STYLE_COLOUR );
    wxListItem itemCol;
    itemCol.SetText( _MGSTR( _S_NAME ) );
    itemCol.SetAlign( wxLIST_FORMAT_CENTRE );
    InsertColumn( 0, itemCol );
    SetColumnWidth( 0, 200 );
    itemCol.SetText( _MGSTR( _S_VALUE ) );
    itemCol.SetAlign( wxLIST_FORMAT_LEFT );
    InsertColumn( 1, itemCol );
    SetColumnWidth( 1, 500 );

    SetBackgroundColour( wxColour( 255, 255, 255 ) );
}

/*
struct _TaskAttr
{
    int nID; //系统中分配的唯一任务号
    _TASK_TYPE nStatus; //任务状态，
    int nThread; //当前线程数，只对运行状态中的任务有效
    int nPriority; //任务优先级，只对运行中的任务有效
    std::string sName; //最终解析的文件名
    llong nLen; //文件长度
    float fRatio; //完成度，如果是已完成文件则不参考这个值
    llong nFinish; //完成的字节数
    int nSpeed; //平均速度
    int nTime; //估计剩余时间
    int nError; //发生错误的次数
    std::string sURL; //原始URL
	//std::string sMirrorURL[9]; //9个mirrorURL
    std::string sSavePath; //最后存放的位置
	std::string sSockProxy;
	std::string sFtpProxy;
	std::string sHttpProxy;
	std::string sMD5;
};
*/
void CTaskDetailReport::ShowTaskDetail( _TaskAttr& tsk )
{
    DeleteAllItems();

    wxString name, value;

    name = _MGSTR( _S_TASKID );
    value.Printf( wxT( "%d" ), tsk.nID );
    AddInfo( name, value );

    name = _MGSTR( _S_URL );
    wxString url( tsk.sURL.c_str(), wxConvLocal );
    AddInfo( name, url );

	name = _MGSTR( _S_DETAIL_NOM ); //number of mirror
    value.Printf( wxT( "%d" ), tsk.sMirrorURL.size() );
    AddInfo( name, value );
	
    name = _MGSTR( _S_TASKSTATUS );

    switch ( tsk.nStatus )
    {

        case _STATUS_RUNNING:
        value = _MGSTR( _S_RUNNING );
        break;

        case _STATUS_PAUSE:
        value = _MGSTR( _S_DETAIL_PAUSE );
        break;

        case _STATUS_WAITING:
        value = _MGSTR( _S_WAITING );
        break;

        case _STATUS_WRONG:
        value = _MGSTR( _S_WRONG );
        break;

        case _STATUS_FINISH_SOFT:

        case _STATUS_FINISH_PACK:

        case _STATUS_FINISH_MUSIC:

        case _STATUS_FINISH_ISO:

        case _STATUS_FINISH_MOVIE:

        case _STATUS_FINISH_PUBLISH:

        case _STATUS_FINISH_PICTURE:

        case _STATUS_FINISH_UNKNOW:
        value = _MGSTR( _S_FINISH );
        break;

        case _STATUS_DELETE:
        value = _MGSTR( _S_DELETED );
        break;

        default:
        value = _MGSTR( _S_UNKNOW );
        break;
    }

    AddInfo( name, value );

    name = _MGSTR( _S_THREADNUM );
    value.Printf( wxT( "%d" ), tsk.nThread );
    AddInfo( name, value );

    name = _MGSTR( _S_DETAIL_SAVEPATH );
    wxString spath( tsk.sSavePath.c_str(), wxConvLocal );
    AddInfo( name, spath );

    name = _MGSTR( _S_FILENAME );
    wxString wxFn( tsk.sName.c_str(), wxConvLocal );
    AddInfo( name, wxFn );

    name = _MGSTR( _S_SIZE );
    value.Printf( wxT( "%lld" ), tsk.nLen );
    AddInfo( name, value );

    name = _MGSTR( _S_FINISH );
    value.Printf( wxT( "%lld" ), tsk.nFinish );
    AddInfo( name, value );

    name = _MGSTR( _S_PROGRESS );
    value.Printf( wxT( "%0.4f%%" ), tsk.fRatio * 100 );
    AddInfo( name, value );

    name = _MGSTR( _S_SPEED );
    value.Printf( wxT( "%d bytes/s" ), tsk.nSpeed );
    AddInfo( name, value );

    name = _MGSTR( _S_ERRORTIME );
    value.Printf( wxT( "%d" ), tsk.nError );
    AddInfo( name, value );


    name = _MGSTR( _S_DETAIL_SOCKSPROXY );
    wxString socks( tsk.sSockProxy.c_str(), wxConvLocal );

    if ( socks == wxT( "" ) )
        socks = wxT( "none" );

    AddInfo( name, socks );

    name = _MGSTR( _S_DETAIL_FTPPROXY );

    wxString ftp( tsk.sFtpProxy.c_str(), wxConvLocal );

    if ( ftp == wxT( "" ) )
        ftp = wxT( "none" );

    AddInfo( name, ftp );

    name = _MGSTR( _S_DETAIL_HTTPPROXY );

    wxString http( tsk.sHttpProxy.c_str(), wxConvLocal );

    if ( http == wxT( "" ) )
        http = wxT( "none" );

    AddInfo( name, http );


    name = _MGSTR( _S_AUTOCHECKMD5 );
    value = tsk.bAutoMd5 ? wxT( "YES" ) : wxT( "NO" );
    AddInfo( name, value );

    name = _MGSTR( _S_DETAIL_MD5 );

    wxString md5( tsk.sMD5.c_str(), wxConvLocal );

    if ( md5 == wxT( "" ) )
        md5 = wxT( "none" );

    AddInfo( name, md5 );
}

//增加一个信息行
int CTaskDetailReport::AddInfo( wxString name, wxString value )
{
    wxListItem item;

    int id;
    id = InsertItem( GetItemCount(), item );
    SetItem( id, 0, name );
    SetItem( id, 1, value );

    SetItemBackgroundColour( id, id % 2 ? wxColour( 210, 210, 210 ) : wxColour( 230, 230, 230 ) );
    return id;
}

void CTaskDetailReport::OnSize( wxEvent& event )
{
    //wxSize vs=GetVirtualSize();
    wxSize vs = GetClientSize();
    int fw = GetColumnWidth( 0 );

    if ( vs.x >= fw + 300 )
    {
        SetColumnWidth( 1, vs.x - fw );
    }
    else
    {
        SetColumnWidth( 1, 300 );
    }

    event.Skip();

}

void CTaskDetailReport::OnColumnResize( wxListEvent& event )
{
    int ncol = event.GetColumn();

    if ( ncol == 0 )
    { //第一列被调整

        wxSize vs = GetClientSize();
        int fw = GetColumnWidth( 0 );

        if ( vs.x >= fw + 300 )
        {
            SetColumnWidth( 1, vs.x - fw );
        }
        else
        {
            SetColumnWidth( 1, 300 );
        }
    }

    event.Skip();
}

void CTaskDetailReport::DynamicLang()
{

    wxListItem itemCol;
    itemCol.SetText( _MGSTR( _S_NAME ) );
    itemCol.SetAlign( wxLIST_FORMAT_CENTRE );
    SetColumn( 0, itemCol );

    itemCol.SetText( _MGSTR( _S_VALUE ) );
    itemCol.SetAlign( wxLIST_FORMAT_LEFT );
    SetColumn( 1, itemCol );

    SetItemText( 0, _MGSTR( _S_TASKID ) );
    SetItemText( 1, _MGSTR( _S_URL ) );
    SetItemText( 2, _MGSTR( _S_DETAIL_NOM ) );
    SetItemText( 3, _MGSTR( _S_TASKSTATUS ) );
    SetItemText( 4, _MGSTR( _S_THREADNUM ) );
    SetItemText( 5, _MGSTR( _S_DETAIL_SAVEPATH ) );
    SetItemText( 6, _MGSTR( _S_FILENAME ) );
    SetItemText( 7, _MGSTR( _S_SIZE ) );
    SetItemText( 8, _MGSTR( _S_FINISH ) );
    SetItemText( 9, _MGSTR( _S_PROGRESS ) );
    SetItemText( 10, _MGSTR( _S_SPEED ) );
    SetItemText( 11, _MGSTR( _S_ERRORTIME ) );
    SetItemText( 12, _MGSTR( _S_DETAIL_SOCKSPROXY ) );
    SetItemText( 13, _MGSTR( _S_DETAIL_FTPPROXY ) );
    SetItemText( 14, _MGSTR( _S_DETAIL_HTTPPROXY ) );
    SetItemText( 15, _MGSTR( _S_AUTOCHECKMD5 ) );
    SetItemText( 16, _MGSTR( _S_DETAIL_MD5 ) );

    wxSize vs = GetClientSize();
    int fw = GetColumnWidth( 0 );

    if ( vs.x >= fw + 300 )
    {
        SetColumnWidth( 1, vs.x - fw );
    }
    else
    {
        SetColumnWidth( 1, 300 );
    }


}

void CTaskDetailReport::OnErase( wxEraseEvent& event )
{ //KDE下，白色会变灰色底
	event.Skip();
	/*
    wxPaintDC pdc( this );
    pdc.SetBackground( *wxWHITE_BRUSH );
    pdc.Clear();
	*/
}

