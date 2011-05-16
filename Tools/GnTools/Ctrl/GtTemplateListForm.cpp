// GtTemplateListForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"

#include "GnTools.h"

#include "GtTemplateListForm.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "GnToolsDoc.h"
#include "GnToolsView.h"
#include <GtObjectManager.h>
#include "GtOpenDialog.h"
#include "GtNewObjectDlg.h"



IMPLEMENT_DYNAMIC(GtTemplateListForm, GtToolBarForm)

GtTemplateListForm::GtTemplateListForm() : mLastSelectItem(-1)
{
}

GtTemplateListForm::~GtTemplateListForm()
{
}


BEGIN_MESSAGE_MAP(GtTemplateListForm, GtToolBarForm)
	ON_WM_CREATE()
	ON_COMMAND(ID_BT_DELTEMPLATE, &GtTemplateListForm::OnBtDeltemplate)
	ON_COMMAND(ID_BT_NEWTEMPLATE, &GtTemplateListForm::OnBtNewtemplate)
	ON_COMMAND(ID_BT_OPENTEMPLATE, &GtTemplateListForm::OnBtOpentemplate)
END_MESSAGE_MAP()


// GtTemplateListForm 메시지 처리기입니다.
int GtTemplateListForm::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (GtToolBarForm::OnCreate(lpCreateStruct) == -1)
		return -1;

	//AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//afxGlobalData.Is32BitIcons() ? IDB_AFXBARRES_NEW32 : IDB_AFXBARRES_NEW
	mToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_TEMPLATELISTVIEWTOOLBAR);
	mToolBar.LoadToolBar(IDR_TEMPLATELISTVIEWTOOLBAR, 0, 0, TRUE);	
	mToolBar.CleanUpLockedImages();	
	mToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_TEMPLATELISTVIEWTOOLBAR_HC : IDR_TEMPLATELISTVIEWTOOLBAR, 0, 0, TRUE);	
	mToolBar.SetPaneStyle(mToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	mToolBar.SetPaneStyle(mToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	mToolBar.SetOwner(this);

	
	// 모든 명령은 부모 프레임이 아닌 이 컨트롤을 통해 라우팅됩니다.
	mToolBar.SetRouteCommandsViaFrame(FALSE);
	mListCtrl.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|LVS_REPORT|LVS_EDITLABELS|LVS_SINGLESEL,
		CRect(10,10,400,200), this, ID_CTRL_TEMPLATELIST);
	mListCtrl.ModifyStyle(0, LVS_SMALLICON);
	mpMainWnd = &mListCtrl;

	SetVisibleCaptionBar(true);
	mToolBar.RemoveButton(4);
	mToolBar.RemoveButton(3);

	gchar filePath[GN_MAX_PATH];
	GtToolSettings::MakeSaveFilePath( "templatelist.lst", NULL, filePath, GN_MAX_PATH );
	LoadTemplateList( filePath );
	return 0;
}

void GtTemplateListForm::OnBtOpentemplate()
{
	//// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//GtOpenDialog fileDlg(true);
	//if( fileDlg.DoFileDialog() == IDOK )
	//{
	//	POSITION pos = fileDlg.GetStartPosition();
	//	while(pos)
	//	{
	//		CString strPath = fileDlg.GetNextPathName(pos);
	//		
	//	}
	//}

	gchar filePath[GN_MAX_PATH];
	GtToolSettings::MakeSaveFilePath( "templatelist.lst", NULL, filePath, GN_MAX_PATH );
	SaveTemplateList( filePath );
}

void GtTemplateListForm::OnBtNewtemplate()
{	
	GtNewObjectDlg dlg;
	if( dlg.DoModal() == IDCANCEL )
		return;

	CString itemName = dlg.GetObjectName();
	if( itemName.GetLength() <= 0 )
		return;
	
	AddItem( itemName, GtActorObject::GTPLANEACTORTYPE, true );
	GtObject* object = GetActorObject( itemName );
	GnAssert( object );
	object->SetNewItem( true );

	GtObjectMessage info;
	info.mpObject = object;
	info.mpSender = this;
	SendMediateMessage( GTMG_NEWOBJECT, &info );

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	
	//mListCtrl.DeleteAllItems();
	//mListCtrl.cur
	// Use the LV_ITEM structure to insert the items
	//LVITEM lvi;
	//CString strItem;
	//for (int i = 0; i < m_nItems; i++)
	//{
	//	// Insert the first item
	//	lvi.mask =  LVIF_IMAGE | LVIF_TEXT;
	//	strItem.Format(_T("Item %i"), i);

	//	lvi.iItem = i;
	//	lvi.iSubItem = 0;
	//	lvi.pszText = (LPTSTR)(LPCTSTR)(strItem);
	//	lvi.iImage = i%8;		// There are 8 images in the image list
	//	m_cListCtrl.InsertItem(&lvi);

	//	// Set subitem 1
	//	strItem.Format(_T("%d"), 10*i);
	//	lvi.iSubItem =1;
	//	lvi.pszText = (LPTSTR)(LPCTSTR)(strItem);
	//	m_cListCtrl.SetItem(&lvi);

	//	// Set subitem 2
	//	strItem.Format(_T("%s"), COleDateTime::GetCurrentTime().Format(_T("Created: %I:%M:%S %p, %m/%d/%Y")));
	//	lvi.iSubItem =2;
	//	lvi.pszText = (LPTSTR)(LPCTSTR)(strItem);
	//	m_cListCtrl.SetItem(&lvi);

	//}

	//// Remove whatever style is there currently
	//m_cListCtrl.ModifyStyle(LVS_ICON | LVS_LIST | LVS_REPORT | LVS_SMALLICON ,0);

	//// Switch the tab mode
	//switch (m_cTabListMode.GetCurSel())
	//{
	//case 0: // Icon mode
	//	m_cListCtrl.ModifyStyle(0, LVS_ICON);
	//	break;
	//case 1:	// Small icons
	//	m_cListCtrl.ModifyStyle(0, LVS_SMALLICON);
	//	break;
	//case 2: // List mode
	//	m_cListCtrl.ModifyStyle(0, LVS_LIST);
	//	break;
	//case 3:	// Details mode
	//	m_cListCtrl.ModifyStyle(0, LVS_REPORT);

	//	break;
	//}
}


void GtTemplateListForm::OnBtDeltemplate()
{
	CList<int> selectList;

	POSITION p = mListCtrl.GetFirstSelectedItemPosition();
	while (p)
	{
		selectList.AddHead( mListCtrl.GetNextSelectedItem(p) );
	}

	while( selectList.IsEmpty() == false )
	{
		mListCtrl.DeleteItem( selectList.GetHead() );
		mTemplateList.RemoveAt( selectList.GetHead() );
		selectList.RemoveHead();
	}
}

void GtTemplateListForm::ReciveNotiyfiMessage(WPARAM wParam, LPARAM lParam)
{
	if( wParam == ID_CTRL_TEMPLATELIST )
	{
		LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(lParam);
		if( pNMItemActivate == NULL )
			return;
		switch( pNMItemActivate->hdr.code )
		{
		case NM_CLICK:
			{

			}
			break;
		case LVN_ITEMCHANGING:
			{
			}
			break;
		case LVN_ITEMCHANGED:
			{
				if( pNMItemActivate->iItem == -1 || mLastSelectItem == pNMItemActivate->iItem )
					return;

				mLastSelectItem = pNMItemActivate->iItem;

				CString itemText = mListCtrl.GetItemText( pNMItemActivate->iItem, 0 );
				GtObject* object = GetActorObject(itemText);
				if( object == NULL )
					return;

				if( object->EnableLoadGnObject() )
					object->LoadStream();

				GtObjectMessage info;
				info.mpObject = object;
				info.mpSender = this;
				SendMediateMessage( GTMG_SELECTOBJECT, &info );
			}
			break;
		case LVN_INSERTITEM:
			{
			}
			break;
		case LVN_DELETEITEM:
			{
				if( mListCtrl.GetItemCount() == 1 )
					mLastSelectItem = -1;
			}
			break;
		}
	}
}

GtObject* GtTemplateListForm::GetActorObject(CString itemText)
{
	GtCString strName = itemText;
	GtActorObject* object = (GtActorObject*)GetObjectManager()->GetObject( strName );
	if(  object == NULL )
	{
		object = GetObjectManager()->CreateActorObject( "2DActor", strName );
	}

	object->SetObjectName( strName.GetAciiString() );

	GtCString fileName = strName;
	fileName += _T( ".gat" );
	object->SetGATFileName( fileName.GetAciiString() );

	fileName = strName;
	fileName += _T( ".gm" );
	object->SetFileName( fileName.GetAciiString() );
	return object;
}

void GtTemplateListForm::AddItem(CString itemName, gint8 iActortype, bool bSelected)
{
	int index = mListCtrl.GetItemCount();
	mListCtrl.InsertItem( index, itemName );
	if( bSelected )
	{
		mListCtrl.SetItemState( index, LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING
			, LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING );
	}
	mListCtrl.RedrawWindow();
	mListCtrl.RedrawItems( 0, mListCtrl.GetItemCount() );

	TemplateListData listData( itemName.GetString(), iActortype );
	mTemplateList.Add( listData );
}


void GtTemplateListForm::SaveTemplateList(const gchar* filePath)
{
	GnStream gnStream;

	if( gnStream.Save( filePath ) == false )
		return;

	guint32 count = mTemplateList.GetSize();
	gnStream.SaveStream( count );

	for( gtuint i = 0 ; i < count ; i++ )
	{
		TemplateListData listData = mTemplateList.GetAt( i );		
		gnStream.SaveStream( listData.mObjectType );
		const gtchar* objectName = listData.mObjectName.GetString();
		gnStream.SaveStream( objectName );
	}

	gnStream.Close();
}

void GtTemplateListForm::LoadTemplateList(const gchar* filePath)
{
	GnStream gnStream;
	if( gnStream.Load( filePath ) == false )
		return;

	guint32 count = 0;
	gnStream.LoadStream( count );

	for( gtuint i = 0 ; i < count ; i++ )
	{
		gint8 type;
		gnStream.LoadStream( type );
		gushort lenName = 0;
		gnStream.LoadStream( lenName );
		gtchar objectName[256] = { 0, };
		GnAssert( 256 > lenName );
		gnStream.LoadStreams( (gchar*)objectName, sizeof(gtchar) * lenName );

		AddItem( objectName, type );
	}

	gnStream.Close();
}

void GtTemplateListForm::OnSaveObjectstate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	gchar filePath[GN_MAX_PATH];
	GtToolSettings::MakeSaveFilePath( "templatelist.lst", NULL, filePath, GN_MAX_PATH );
	SaveTemplateList( filePath );
}
