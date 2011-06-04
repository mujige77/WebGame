// GcEditorSequenceTexture.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GcEditorSequenceTexture.h"
#include "GtObjectNew.h"
#include "GcBasicPropEntity.h"
#include "GcPropertyGridFileProperty.h"

float GcEditorSequenceTexture::mDefaultStartTime = 0.0f;
float GcEditorSequenceTexture::mDefaultEndTime = 0.1f;

void GcEditorSequenceTexture::TextureListBox::OnBrowse()
{
	if( mEnableAddItem == false )
		return;

	int nSel = GetSelItem();

	CFileDialog dlg(true, _T("IMG"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
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

void GcEditorSequenceTexture::TextureListBox::OnEndEditLabel(LPCTSTR lpszLabel)
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

void GcEditorSequenceTexture::TextureListBox::CreateNewItem()
{
	CFileDialog dlg(true, _T("IMG"), NULL
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

void GcEditorSequenceTexture::AniListBox::CreateNewItem()
{
	int count = GetCount();
	CString makeName = GetMakeName( count );
	int nSel = AddItem( makeName );
	OnAfterAddItem(nSel);
	SelectItem( nSel );
}

BOOL GcEditorSequenceTexture::AniListBox::RemoveItem(int iItem)
{
	if( GcVSListBox::RemoveItem( iItem ) == false )
		return false;

	for( int i = iItem - 1 ; i < GetCount() ; i++ )
	{
		CString makeName = GetMakeName( i );
		SetItemText( i , makeName );
	}
	return true;
}

CString GcEditorSequenceTexture::AniListBox::GetMakeName(int count)
{
	gtchar* format = _T("TextureAni_%0d");
	if( count > 9 )
		format = _T("TextureAni_%0d");

	CString makeName;
	makeName.Format(  format, count );
	return makeName;
}

IMPLEMENT_DYNAMIC(GcEditorSequenceTexture, GcEditorPropertyPage)

GcEditorSequenceTexture::GcEditorSequenceTexture() : GcEditorPropertyPage(GcEditorSequenceTexture::IDD)
{
}

GcEditorSequenceTexture::~GcEditorSequenceTexture()
{
	mpTextureAnimationPropEntity.SetNullProperty();
}


BEGIN_MESSAGE_MAP(GcEditorSequenceTexture, GcEditorPropertyPage)
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
	ON_EN_CHANGE(IDC_ET_DEFAULTSTARTTIME, &GcEditorSequenceTexture::OnChangeDefaultstarttime)
	ON_EN_CHANGE(IDC_ET_DEFAULTENDTIME, &GcEditorSequenceTexture::OnChangeDefaultendtime)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SP_DEFAULTSTARTTIME, &GcEditorSequenceTexture::OnDeltaposDefaultstarttime)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SP_DEFAULTENDTIME, &GcEditorSequenceTexture::OnDeltaposDefaultendtime)
END_MESSAGE_MAP()

void GcEditorSequenceTexture::DoDataExchange(CDataExchange* pDX)
{
	GcEditorPropertyPage::DoDataExchange( pDX );
	DDX_Control( pDX, IDC_TEXTUREEDITPAGE_LOCATION, mPropLocation );
	DDX_Control( pDX, IDC_SEQUENCETEXTURELISBOX, mTextureListBox );
	DDX_Control( pDX, IDC_TEXTURESEQUENCELISTBOX, mAniListBox );
	DDX_Control(pDX, IDC_ET_DEFAULTSTARTTIME, mETDefaultStartTime);
	DDX_Control(pDX, IDC_ET_DEFAULTENDTIME, mETDefaultEndTime);
}


BOOL GcEditorSequenceTexture::OnInitDialog()
{
	GcEditorPropertyPage::OnInitDialog();

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


BOOL GcEditorSequenceTexture::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	GTVSITEMACTIVATE* item = (GTVSITEMACTIVATE*)lParam;
	switch( wParam )
	{
	case GTMG_VSLISTITEM_MOVEUP:
		{
			if( item->iItem == -1 )
				break;

			GnTObjectArray<GnAnimation::AniInfoPtr>* ani = mpsCurrentAni->GetAniInfos();
			ani->ChangePostion( item->iItem, item->iItem + 1 );
			SelectChangeTextureItem( item->iItem );
		}
		break;
	case GTMG_VSLISTITEM_MOVEDOWN:
		{
			if( item->iItem == -1 )
				break;

			GnTObjectArray<GnAnimation::AniInfoPtr>* ani = mpsCurrentAni->GetAniInfos();
			ani->ChangePostion( item->iItem, item->iItem - 1 );
			SelectChangeTextureItem( item->iItem );
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
				if( mpsCurrentAni && (int)mpsCurrentAni->GetAniInfoCount() > item->iItem )
				{
					SelectChangeTextureItem( item->iItem );
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
	return GcEditorPropertyPage::OnNotify(wParam, lParam, pResult);
}

LRESULT GcEditorSequenceTexture::OnPropertyChanged(WPARAM wparam, LPARAM lparam)
{
	CMFCPropertyGridProperty *pProp = (CMFCPropertyGridProperty*)lparam;
	if (!pProp) return 0;

	switch( pProp->GetData() )
	{
	case Gc2DTexturePropEntity::MSG_TEXTUREPATH:
		{
			RenameTextureItem( mTextureListBox.GetSelItem(), mpTextureAnimationPropEntity.GetTextureFilePath() );
		}
		break;
	case Gc2DTexturePropEntity::MSG_STARTTIME:
		{
			if( mpsCurrentAni )
			{
				GnAnimation::AniInfo* info = mpsCurrentAni->GetAniInfo( mTextureListBox.GetSelItem() );				
				if( info )
				{
					//info->SetStartTime( mpTextureAnimationPropEntity.GetStartTime() );
				}
			}
		}
		break;
	case Gc2DTexturePropEntity::MSG_ENDTIME:
		{
			if( mpsCurrentAni )
			{
				GnAnimation::AniInfo* info = mpsCurrentAni->GetAniInfo( mTextureListBox.GetSelItem() );				
				if( info )
				{
					//info->SetEndTime( mpTextureAnimationPropEntity.GetEndTime() );
				}
			}
		}
		break;
	}
	return 1;
}

void GcEditorSequenceTexture::AddTextureItem(GTVSITEMACTIVATE* item)
{
	if( mpsCurrentAni == NULL )
	{
		AfxMessageBox( _T("에니메이션을 먼저 추가하세요") );
		mTextureListBox.RemoveItem( item->iItem );
		return;
	}

	if( item->iItem == -1 )
		return;

	CString strName = mTextureListBox.GetItemText( item->iItem );
	
	if( mpsCurrentAni )
	{
		Gn2DTextureAni::TextureAniInfo* info = GtObjectNew<Gn2DTextureAni::TextureAniInfo>::Create();
		info->SetStartTime( mDefaultStartTime );
		info->SetEndTime( mDefaultEndTime );
		GtConvertString convertStr = strName.GetString();
		info->SetTextureName( convertStr.GetAciiString() );
		mpsCurrentAni->AddAniInfo( info );

		SelectChangeTextureItem( item->iItem );
	}

	GeFileName( strName );	
	mTextureListBox.SetItemText( item->iItem, strName );
	mPropList.AdjustLayout();

	CheckEnableOKButton();
}

void GcEditorSequenceTexture::RemoveTextureItem(GTVSITEMACTIVATE* item)
{
	if( item->iItem == -1 )
		return;

	mpTextureAnimationPropEntity.SetClearValues();

	if( mpsCurrentAni && (int)mpsCurrentAni->GetAniInfoCount() > item->iItem )
	{
		mpsCurrentAni->GetAniInfos()->RemoveAtAndFillAll( item->iItem );
	}
	mPropList.AdjustLayout();
	CheckEnableOKButton();
}

void GcEditorSequenceTexture::RenameTextureItem(int index)
{
	CString beforeName = mTextureListBox.GetBeforeEditText();	
	CString strName = mTextureListBox.GetItemText( index );
	RenameTextureItem( index, strName );
}

void GcEditorSequenceTexture::RenameTextureItem(int uiIndex, CString strFilePath)
{
	mpTextureAnimationPropEntity.SetTextureFilePath( strFilePath );

	if( mpsCurrentAni )
	{
		Gn2DTextureAni::TextureAniInfo* info = 
			(Gn2DTextureAni::TextureAniInfo*)mpsCurrentAni->GetAniInfo( uiIndex );
		GtConvertString convertName = strFilePath.GetString();
		info->SetTextureName( convertName.GetAciiString() );
	}

	GeFileName( strFilePath );
	mTextureListBox.SetItemText( uiIndex, strFilePath );

	mPropList.AdjustLayout();
}

void GcEditorSequenceTexture::GeFileName(CString strName)
{
	if( mpsCurrentAni == NULL )
		return;

	gtchar filePath[GN_MAX_PATH] = { 0, };
	GnVerify( GnPath::GetFileName( strName.GetString(), filePath, GN_MAX_PATH, true ) );	
	strName = filePath;
}

void GcEditorSequenceTexture::OnOK()
{
	float endTime = 0.0f;
	for( gtuint i = 0 ; i < mpsCurrentAni->GetAniInfoCount() ; i++ )
	{
		GnAnimation::AniInfo* info = mpsCurrentAni->GetAniInfo( i );
		endTime += info->GetEndTime();
	}
	Gn2DSequence* gnSequence = mpSequence->GetSequence();
	gnSequence->SetStartTime( 0 );
	gnSequence->SetEndTime( endTime );
}

void GcEditorSequenceTexture::AddAniItem(GTVSITEMACTIVATE* item)
{
	GnAssert( mAniCtrls.GetSize() == item->iItem );
	Gn2DTextureAni* ani = GtObjectNew<Gn2DTextureAni>::Create();

	mpsCurrentAni = ani;
	mAniCtrls.Add( ani );
	mpSequence->AddTextureAni( ani );
}

void GcEditorSequenceTexture::RemoveAniItem(GTVSITEMACTIVATE* item)
{
	while( mTextureListBox.GetCount()  )
	{
		mTextureListBox.RemoveItem( 0 );
	}
	Gn2DTextureAni*  pCtrl = mAniCtrls.GetAt( item->iItem );
	mAniCtrls.RemoveAtAndFillAll( item->iItem );
	mpSequence->RemoveAtAndFillAllAni( item->iItem );
	mpsCurrentAni = NULL;
	CheckEnableOKButton();
}

void GcEditorSequenceTexture::SelectChangeTextureItem(int uiIndex)
{
	Gn2DTextureAni::TextureAniInfo* textureAniInfo = 
		(Gn2DTextureAni::TextureAniInfo*)mpsCurrentAni->GetAniInfo( uiIndex );
	GnAssert( textureAniInfo );
	GtConvertString str = textureAniInfo->GetTextureName();
	mpTextureAnimationPropEntity.SetIndex( uiIndex );
	mpTextureAnimationPropEntity.SetTextureFilePath( str.c_str() );
	//mpTextureAnimationPropEntity.SetStartTime( textureAniInfo->GetStartTime() );
	//mpTextureAnimationPropEntity.SetEndTime( textureAniInfo->GetEndTime() );
	//mPropList.SetCurSel( mpTextureAnimationPropEntity.GetTextureNumberProperty() );
	//mPropList.SetCurSel( mpTextureAnimationPropEntity.GetTextureGridFileProperty() );
}

void GcEditorSequenceTexture::SelectChangeAniItem(GTVSITEMACTIVATE* item)
{
	while( mTextureListBox.GetCount()  )
	{
		mTextureListBox.RemoveItem( 0 );
	}
	if( mAniCtrls.GetSize() > (gtuint)item->iItem )
	{
		mpsCurrentAni = mAniCtrls.GetAt( item->iItem );
		if( mpsCurrentAni  )
		{
			for( int i = 0 ; i < (int)mpsCurrentAni->GetAniInfoCount() ; i++ )
			{
				Gn2DTextureAni::TextureAniInfo* info = 
					(Gn2DTextureAni::TextureAniInfo*)mpsCurrentAni->GetAniInfo( i );
				GtConvertString str = info->GetTextureName();
				GeFileName( str.c_str() );
				mTextureListBox.AddItem( str.c_str() );
			}
			if( mpsCurrentAni->GetAniInfoCount() )
				mTextureListBox.SelectItem( 0 );
		}
	}
}
//GnSMTextureAniCtrl* GtProperties::CreateSMTextureAniCtrl()
//{
//	Gc2DTexturePropEntity* texEntity = GetEntityFromClassNameDef(mpEntities, Gc2DTexturePropEntity);
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
//		GtConvertString str = texProp->GetPath(i);
//		if( str.GetLength() )
//		{
//			GnTextureProperty* texProperty = GnObjectNew<GnTextureProperty>::Create(  str.GetAciiString() );
//			textureAni->SetAniInfo( i, texProperty, aniEntity->GetStartTime(), aniEntity->GetEndTime() );
//		}
//	}
//	return textureAni;
//}

void GcEditorSequenceTexture::OnChangeDefaultstarttime()
{
}


void GcEditorSequenceTexture::OnChangeDefaultendtime()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// GcEditorPropertyPage::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void GcEditorSequenceTexture::OnDeltaposDefaultstarttime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void GcEditorSequenceTexture::OnDeltaposDefaultendtime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}
