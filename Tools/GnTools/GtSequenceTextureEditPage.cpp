// GtSequenceTextureEditPage.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GnTools.h"
#include "GtSequenceTextureEditPage.h"
#include "GtTextureDefine.h"
#include "GnObjectNew.h"
#include "GtBasicPropEntity.h"
#include "GtPropertyGridFileProperty.h"

float GtSequenceTextureEditPage::mDefaultStartTime = 0.0f;
float GtSequenceTextureEditPage::mDefaultEndTime = 0.1f;

void GtSequenceTextureEditPage::TextureListBox::OnBrowse()
{
	if( mEnableAddItem == false )
		return;

	int nSel = GetSelItem();

	GtOpenDialog dlg(true, _T("IMG"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		gsTextureFileFilter, GetParent() );
	if( dlg.DoModal() == IDOK )
	{
		if (nSel == GetCount() || nSel == -1) // New item
		{
			nSel = AddItem( dlg.GetPathName() );
			SelectItem( nSel );
			OnAfterAddItem(nSel);
		}
		else
		{
			SetItemText( nSel, dlg.GetPathName() );
			OnAfterRenameItem( nSel );
		}
		//CListCtrl* pWndList = (CListCtrl*)CWnd::FromHandle( GetListHwnd() );
	}
}

void GtSequenceTextureEditPage::TextureListBox::OnEndEditLabel(LPCTSTR lpszLabel)
{
	int iSelItem = GetSelItem();
	if (iSelItem < 0)
	{
		ASSERT(FALSE);
		return;
	}

	CString strLabel = (lpszLabel != NULL) ? lpszLabel : _T("");
	if (m_bNewItem)
	{
		RemoveItem(iSelItem);
	}

	m_bNewItem = FALSE;
}

void GtSequenceTextureEditPage::TextureListBox::CreateNewItem()
{
	GtOpenDialog dlg(true, _T("IMG"), NULL
		, OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		gsTextureFileFilter, GetParent() );

	if( dlg.DoModal() == IDOK )
	{
		CString strPath;
		POSITION pos = dlg.GetStartPosition();
		while(pos)
		{
			strPath = dlg.GetNextPathName(pos);
			int sel = AddItem( strPath );
			SelectItem( sel );
			OnAfterAddItem( sel );
		}
	}
}

void GtSequenceTextureEditPage::AniListBox::CreateNewItem()
{
	int count = GetCount();
	CString makeName = GetMakeName( count );
	int nSel = AddItem( makeName );
	OnAfterAddItem(nSel);
	SelectItem( nSel );
}

BOOL GtSequenceTextureEditPage::AniListBox::RemoveItem(int iItem)
{
	if( GtVSListBox::RemoveItem( iItem ) == false )
		return false;

	for( int i = iItem - 1 ; i < GetCount() ; i++ )
	{
		CString makeName = GetMakeName( i );
		SetItemText( i , makeName );
	}
	return true;
}

CString GtSequenceTextureEditPage::AniListBox::GetMakeName(int count)
{
	gtchar* format = _T("TextureAni_%0d");
	if( count > 9 )
		format = _T("TextureAni_%0d");

	CString makeName;
	makeName.Format(  format, count );
	return makeName;
}

IMPLEMENT_DYNAMIC(GtSequenceTextureEditPage, GtPropertyPage)

GtSequenceTextureEditPage::GtSequenceTextureEditPage() : GtPropertyPage(GtSequenceTextureEditPage::IDD)
	,mpCurrentAni(NULL)
{
}

GtSequenceTextureEditPage::~GtSequenceTextureEditPage()
{
	mpTextureAnimationPropEntity.SetNullProperty();
}


BEGIN_MESSAGE_MAP(GtSequenceTextureEditPage, GtPropertyPage)
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
	ON_EN_CHANGE(IDC_ET_DEFAULTSTARTTIME, &GtSequenceTextureEditPage::OnChangeDefaultstarttime)
	ON_EN_CHANGE(IDC_ET_DEFAULTENDTIME, &GtSequenceTextureEditPage::OnChangeDefaultendtime)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SP_DEFAULTSTARTTIME, &GtSequenceTextureEditPage::OnDeltaposDefaultstarttime)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SP_DEFAULTENDTIME, &GtSequenceTextureEditPage::OnDeltaposDefaultendtime)
END_MESSAGE_MAP()

void GtSequenceTextureEditPage::DoDataExchange(CDataExchange* pDX)
{
	GtPropertyPage::DoDataExchange( pDX );
	DDX_Control( pDX, IDC_TEXTUREEDITPAGE_LOCATION, mPropLocation );
	DDX_Control( pDX, IDC_SEQUENCETEXTURELISBOX, mTextureListBox );
	DDX_Control( pDX, IDC_TEXTURESEQUENCELISTBOX, mAniListBox );
	DDX_Control(pDX, IDC_ET_DEFAULTSTARTTIME, mETDefaultStartTime);
	DDX_Control(pDX, IDC_ET_DEFAULTENDTIME, mETDefaultEndTime);
}


BOOL GtSequenceTextureEditPage::OnInitDialog()
{
	GtPropertyPage::OnInitDialog();

	mTextureListBox.SetWindowText( _T("Texture List") );
	mTextureListBox.SetStandardButtons();
	mTextureListBox.EnableBrowseButton();

	mAniListBox.SetWindowText( _T("Texture Ani List") );
	mAniListBox.SetStandardButtons( AFX_VSLISTBOX_BTN_NEW | AFX_VSLISTBOX_BTN_DELETE );
	mAniListBox.EnableBrowseButton( false );

	CRect rectPropList;
	mPropLocation.GetClientRect(&rectPropList);
	mPropLocation.MapWindowPoints(this, &rectPropList);

	mPropList.Create( WS_CHILD | WS_VISIBLE , rectPropList, this, 2 );
	mPropList.EnableHeaderCtrl(FALSE);
	mPropList.EnableDescriptionArea();
	mPropList.SetVSDotNetLook();
	mPropList.MarkModifiedProperties();
	mPropList.SetDescriptionRows(5);
		
	mPropList.AddProperty( mpTextureAnimationPropEntity.GetProperty() );
	return TRUE;
}


BOOL GtSequenceTextureEditPage::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	GTVSITEMACTIVATE* item = (GTVSITEMACTIVATE*)lParam;
	switch( wParam )
	{
	case GTMG_VSLISTITEM_MOVEUP:
		{
			if( item->iItem == -1 )
				break;

			GnTPrimitiveArray<GtSMTextureAniCtrl::AniInfo*>& ani = mpCurrentAni->GetAniList();
			ani.ChangePostion( item->iItem, item->iItem + 1 );
			ani.GetAt( item->iItem )->mIndex = item->iItem;
			ani.GetAt( item->iItem + 1 )->mIndex = item->iItem + 1;
			SelectChangeTextureItem( mpCurrentAni->GetAniInfo(item->iItem ) );
		}
		break;
	case GTMG_VSLISTITEM_MOVEDOWN:
		{
			if( item->iItem == -1 )
				break;

			GnTPrimitiveArray<GtSMTextureAniCtrl::AniInfo*>& ani = mpCurrentAni->GetAniList();
			ani.ChangePostion( item->iItem, item->iItem - 1 );
			ani.GetAt( item->iItem )->mIndex = item->iItem;
			ani.GetAt( item->iItem - 1)->mIndex = item->iItem - 1;
			SelectChangeTextureItem( mpCurrentAni->GetAniInfo(item->iItem ) );
		}
		break;
	case GTMG_VSLISTITEM_SELECTCHANGED:
		{
			if( item->iItem == -1 )
				break;
			if( item->hdr.hwndFrom == mAniListBox.GetSafeHwnd() )
				SelectChangeAniItem(item);
			else if( item->hdr.hwndFrom == mTextureListBox.GetSafeHwnd() )
			{
				if( mpCurrentAni && (int)mpCurrentAni->GetAniInfoCount() > item->iItem )
				{
					SelectChangeTextureItem( mpCurrentAni->GetAniInfo(item->iItem ) );
				}
			}
		}
		break;
	case GTMG_VSLISTITEM_BEFOREREMOVE:
		{
			if( item->hdr.hwndFrom == mTextureListBox.GetSafeHwnd() )
				RemoveTextureItem( item );
			else if( item->hdr.hwndFrom == mAniListBox.GetSafeHwnd() )
				RemoveAniItem( item );
		}
		break;
	case GTMG_VSLISTITEM_AFTERADD:
		{
			if( item->hdr.hwndFrom == mTextureListBox.GetSafeHwnd() )
				AddTextureItem(item);
			else if( item->hdr.hwndFrom == mAniListBox.GetSafeHwnd() )
				AddAniItem(item);
		}
		break;
	case GTMG_VSLISTITEM_AFTERRENAME:
		{
			if( item->hdr.hwndFrom == mTextureListBox.GetSafeHwnd() )
				RenameTextureItem( item->iItem );
		}
		break;
	}
	return GtPropertyPage::OnNotify(wParam, lParam, pResult);
}

LRESULT GtSequenceTextureEditPage::OnPropertyChanged(WPARAM wparam, LPARAM lparam)
{
	CMFCPropertyGridProperty *pProp = (CMFCPropertyGridProperty*)lparam;
	if (!pProp) return 0;

	switch( pProp->GetData() )
	{
	case Gt2DTexturePropEntity::MSG_TEXTUREPATH:
		{
			RenameTextureItem( mTextureListBox.GetSelItem(), mpTextureAnimationPropEntity.GetTextureFilePath() );
		}
		break;
	case Gt2DTexturePropEntity::MSG_STARTTIME:
		{
			if( mpCurrentAni )
			{
				GtSMTextureAniCtrl::AniInfo* info = mpCurrentAni->GetAniInfo( mTextureListBox.GetSelItem() );				
				if( info )
				{
					info->mStartTime = mpTextureAnimationPropEntity.GetStartTime();
				}
			}
		}
		break;
	case Gt2DTexturePropEntity::MSG_ENDTIME:
		{
			if( mpCurrentAni )
			{
				GtSMTextureAniCtrl::AniInfo* info = mpCurrentAni->GetAniInfo( mTextureListBox.GetSelItem() );				
				if( info )
				{
					info->mEndTime = mpTextureAnimationPropEntity.GetEndTime();
				}
			}
		}
		break;
	}
	return 1;
}

void GtSequenceTextureEditPage::AddTextureItem(GTVSITEMACTIVATE* item)
{
	if( mpCurrentAni == NULL )
	{
		AfxMessageBox( _T("에니메이션을 먼저 추가하세요") );
		mTextureListBox.RemoveItem( item->iItem );
		return;
	}

	if( item->iItem == -1 )
		return;

	CString strName = mTextureListBox.GetItemText( item->iItem );
	
	if( mpCurrentAni )
	{
		GtSMTextureAniCtrl::AniInfo* info = GnObjectNew<GtSMTextureAniCtrl::AniInfo>::Create();
		info->mIndex = item->iItem;
		info->mStartTime = mDefaultStartTime;
		info->mEndTime = mDefaultEndTime;
		GtCString convertStr = strName;
		info->mTextureFilePath = convertStr.GetAciiString();
		mpCurrentAni->InsertAniInfo( info );

		SelectChangeTextureItem( info );
	}

	GeFileName( strName );	
	mTextureListBox.SetItemText( item->iItem, strName );
	mPropList.AdjustLayout();

	CheckEnableOKButton();
}

void GtSequenceTextureEditPage::RemoveTextureItem(GTVSITEMACTIVATE* item)
{
	if( item->iItem == -1 )
		return;

	mpTextureAnimationPropEntity.SetClearValues();

	if( mpCurrentAni && (int)mpCurrentAni->GetAniInfoCount() > item->iItem )
	{
		mpCurrentAni->RemoveInfo( item->iItem );		
	}
	mPropList.AdjustLayout();
	CheckEnableOKButton();
}

void GtSequenceTextureEditPage::RenameTextureItem(int index)
{
	CString beforeName = mTextureListBox.GetBeforeEditText();	
	CString strName = mTextureListBox.GetItemText( index );
	RenameTextureItem( index, strName );
}

void GtSequenceTextureEditPage::RenameTextureItem(int uiIndex, CString strFilePath)
{
	mpTextureAnimationPropEntity.SetTextureFilePath( strFilePath );

	if( mpCurrentAni )
	{
		GtSMTextureAniCtrl::AniInfo* info = mpCurrentAni->GetAniInfo( uiIndex );
		GtCString convertName = strFilePath;
		info->mTextureFilePath = convertName.GetAciiString();
	}

	GeFileName( strFilePath );
	mTextureListBox.SetItemText( uiIndex, strFilePath );

	mPropList.AdjustLayout();
}

void GtSequenceTextureEditPage::GeFileName(CString &strName)
{
	if( mpCurrentAni == NULL )
		return;

	gtchar filePath[GN_MAX_PATH] = { 0, };
	GnVerify( GnPath::GetFileName( strName.GetString(), filePath, GN_MAX_PATH, true ) );	
	strName = filePath;
}

void GtSequenceTextureEditPage::OnOK()
{
	//GnAssert( mpObject );
	//for( int i = 0 ; i < mpCurrentEntites->GetEntityCount() ; i++ )
	//{
	//	CString name = mTextureListBox.GetItemText( i );
	//	GtPropertyEntity* textureEntity = mpCurrentEntites->GetEntity( name );
	//	textureEntity->ParseToObject( mpObject );
	//}
}

void GtSequenceTextureEditPage::AddAniItem(GTVSITEMACTIVATE* item)
{
	GnAssert( mAniCtrls.GetSize() == item->iItem );
	GtSMTextureAniCtrl* ani = GnObjectNew<GtSMTextureAniCtrl>::Create();
	ani->SetTargetName( mpObject->GetObjectName() );

	mpCurrentAni = ani;
	mAniCtrls.Add( ani );
	mpSequence->AddTimeController( ani );
}

void GtSequenceTextureEditPage::RemoveAniItem(GTVSITEMACTIVATE* item)
{
	while( mTextureListBox.GetCount()  )
	{
		mTextureListBox.RemoveItem( 0 );
	}
	GtSMTextureAniCtrl*  pCtrl = mAniCtrls.GetAt( item->iItem );
	mAniCtrls.RemoveAtAndFillAll( item->iItem );
	mpSequence->RemoveController( pCtrl );
	mpCurrentAni = NULL;
	CheckEnableOKButton();
}

void GtSequenceTextureEditPage::SelectChangeTextureItem(GtSMTextureAniCtrl::AniInfo* pAniInfo)
{
	GnAssert( pAniInfo );
	GtCString str = pAniInfo->mTextureFilePath;
	//mpTextureAnimationPropEntity.SetIndex( pAniInfo->mIndex );
	mpTextureAnimationPropEntity.SetTextureFilePath( str );
	mpTextureAnimationPropEntity.SetStartTime( pAniInfo->mStartTime );
	mpTextureAnimationPropEntity.SetEndTime( pAniInfo->mEndTime );
	//mPropList.SetCurSel( mpTextureAnimationPropEntity.GetTextureNumberProperty() );
	//mPropList.SetCurSel( mpTextureAnimationPropEntity.GetTextureGridFileProperty() );
}

void GtSequenceTextureEditPage::SelectChangeAniItem(GTVSITEMACTIVATE* item)
{
	while( mTextureListBox.GetCount()  )
	{
		mTextureListBox.RemoveItem( 0 );
	}
	if( mAniCtrls.GetSize() > (gtuint)item->iItem )
	{
		mpCurrentAni = mAniCtrls.GetAt( item->iItem );
		if( mpCurrentAni  )
		{
			for( int i = 0 ; i < (int)mpCurrentAni->GetAniInfoCount() ; i++ )
			{
				GtSMTextureAniCtrl::AniInfo* info = mpCurrentAni->GetAniInfo( i );
				GtCString str = info->mTextureFilePath;
				GeFileName( str );
				mTextureListBox.AddItem( str );
			}
			if( mpCurrentAni->GetAniInfoCount() )
				mTextureListBox.SelectItem( 0 );
		}
	}
}
//GnSMTextureAniCtrl* GtProperties::CreateSMTextureAniCtrl()
//{
//	Gt2DTexturePropEntity* texEntity = GetEntityFromClassNameDef(mpEntities, Gt2DTexturePropEntity);
//	if( texEntity == NULL )
//		return NULL;
//
//	GtTextureAnimationPropEntity* aniEntity = GetEntityFromClassNameDef(mpEntities, GtTextureAnimationPropEntity);
//	if( texEntity == NULL )
//		return NULL;
//
//	GtPropertyGridMultiFileProperty* texProp = (GtPropertyGridMultiFileProperty*)texEntity->GetProperty();
//	if( texProp == NULL )
//		return NULL;
//
//	GnSMTextureAniCtrl* textureAni = NULL;
//	if( texProp->GetSubItemsCount() )
//		textureAni = GnObjectNew<GnSMTextureAniCtrl>::Create(texProp->GetSubItemsCount() );
//	else
//		return NULL;
//
//	for( int i = 0 ; i < texProp->GetSubItemsCount() ; i++ )
//	{
//		GtCString str = texProp->GetPath(i);
//		if( str.GetLength() )
//		{
//			GnTextureProperty* texProperty = GnObjectNew<GnTextureProperty>::Create(  str.GetAciiString() );
//			textureAni->SetAniInfo( i, texProperty, aniEntity->GetStartTime(), aniEntity->GetEndTime() );
//		}
//	}
//	return textureAni;
//}

void GtSequenceTextureEditPage::OnChangeDefaultstarttime()
{
}


void GtSequenceTextureEditPage::OnChangeDefaultendtime()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// GtPropertyPage::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void GtSequenceTextureEditPage::OnDeltaposDefaultstarttime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void GtSequenceTextureEditPage::OnDeltaposDefaultendtime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}
