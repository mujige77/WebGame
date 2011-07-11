// GcEditorTexture.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GcEditorTexture.h"
#include "GtObjectNew.h"
#include "GcBasicPropEntity.h"
#include "GcPropertyGridFileProperty.h"

float GcEditorTexture::mDefaultStartTime = 0.0f;
float GcEditorTexture::mDefaultEndTime = 0.1f;

float GcEditorTexture::GetDefaultStartTime() {
	return mDefaultStartTime;
}
void GcEditorTexture::SetDefaultStartTime(float val) {
	mDefaultStartTime = val;
}	
float GcEditorTexture::GetDefaultEndTime() {
	return mDefaultEndTime;
}
void GcEditorTexture::SetDefaultEndTime(float val) {
	mDefaultEndTime = val;
}

IMPLEMENT_DYNAMIC(GcEditorTexture, GcEditorPropertyPage)

	GcEditorTexture::GcEditorTexture() : GcEditorPropertyPage(GcEditorTexture::IDD)
{
}

GcEditorTexture::~GcEditorTexture()
{
	mpTextureAnimationPropEntity.SetNullProperty();
	for( gtuint i = 0 ; i < mTextureLists.GetSize() ; i++ )
	{
		delete mTextureLists.GetAt( i );
	}
}


BEGIN_MESSAGE_MAP(GcEditorTexture, GcEditorPropertyPage)
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
	ON_EN_CHANGE(IDC_ET_DEFAULTSTARTTIME, &GcEditorTexture::OnChangeDefaultstarttime)
	ON_EN_CHANGE(IDC_ET_DEFAULTENDTIME, &GcEditorTexture::OnChangeDefaultendtime)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SP_DEFAULTSTARTTIME, &GcEditorTexture::OnDeltaposDefaultstarttime)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SP_DEFAULTENDTIME, &GcEditorTexture::OnDeltaposDefaultendtime)
END_MESSAGE_MAP()

void GcEditorTexture::DoDataExchange(CDataExchange* pDX)
{
	GcEditorPropertyPage::DoDataExchange( pDX );
	DDX_Control( pDX, IDC_TEXTUREEDITPAGE_LOCATION, mPropLocation );
	DDX_Control( pDX, IDC_SEQUENCETEXTURELISBOX, mTextureBox );
	DDX_Control( pDX, IDC_TEXTURESEQUENCELISTBOX, mTextureListBox );
	DDX_Control(pDX, IDC_ET_DEFAULTSTARTTIME, mETDefaultStartTime);
	DDX_Control(pDX, IDC_ET_DEFAULTENDTIME, mETDefaultEndTime);
}


BOOL GcEditorTexture::OnInitDialog()
{
	GcEditorPropertyPage::OnInitDialog();

	mTextureBox.SetWindowText( _T("Texture List") );
	mTextureBox.SetStandardButtons();
	mTextureBox.EnableBrowseButton();
	mTextureBox.SetDefaultStartTime( GetDefaultStartTime() );
	mTextureBox.SetDefaultEndTime( GetDefaultEndTime() );

	mTextureListBox.SetWindowText( _T("Texture Ani List") );
	mTextureListBox.SetStandardButtons( AFX_VSLISTBOX_BTN_NEW | AFX_VSLISTBOX_BTN_DELETE );
	mTextureListBox.EnableBrowseButton( false );
	mTextureListBox.SetTextureLists( &mTextureLists );

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


BOOL GcEditorTexture::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	GTVSITEMACTIVATE* item = (GTVSITEMACTIVATE*)lParam;
	switch( wParam )
	{
	case GTMG_VSLISTITEM_MOVEUP:
	case GTMG_VSLISTITEM_MOVEDOWN:
	case GTMG_VSLISTITEM_SELECTCHANGED:
		{
			if( item->iItem == -1 )
				break;

			if( item->hdr.hwndFrom == mTextureListBox.GetSafeHwnd() )
			{
				SelectChangeListItem( item->iItem );
			}
			else if( item->hdr.hwndFrom == mTextureBox.GetSafeHwnd() )
			{
				SelectChangeTextureItem( item->iItem );
			}
		}
		break;
	case GTMG_VSLISTITEM_BEFOREREMOVE:
		{
			CheckEnableOKButton();
		}
		break;
	case GTMG_VSLISTITEM_AFTERADD:
		{
			CheckEnableOKButton();
		}
		break;
	case GTMG_VSLISTITEM_AFTERRENAME:
		{
		}
		break;
	}
	return GcEditorPropertyPage::OnNotify(wParam, lParam, pResult);
}

LRESULT GcEditorTexture::OnPropertyChanged(WPARAM wparam, LPARAM lparam)
{
	CMFCPropertyGridProperty *pProp = (CMFCPropertyGridProperty*)lparam;
	if (!pProp) return 0;

	switch( pProp->GetData() )
	{
	case Gc2DTexturePropEntity::MSG_TEXTUREPATH:
		{
			//RenameTextureItem( mTextureBox.GetSelItem(), mpTextureAnimationPropEntity.GetTextureFilePath() );
		}
		break;
	case Gc2DTexturePropEntity::MSG_STARTTIME:
		{
			//if( mpsCurrentAni )
			{
				//GnAnimation::AniInfo* info = mpsCurrentAni->GetAniInfo( mTextureBox.GetSelItem() );				
				//if( info )
				//{
				//	//info->SetStartTime( mpTextureAnimationPropEntity.GetStartTime() );
				//}
			}
		}
		break;
	case Gc2DTexturePropEntity::MSG_ENDTIME:
		{
// 			if( mpsCurrentAni )
// 			{
// 				GnAnimation::AniInfo* info = mpsCurrentAni->GetAniInfo( mTextureBox.GetSelItem() );				
// 				if( info )
// 				{
// 					//info->SetEndTime( mpTextureAnimationPropEntity.GetEndTime() );
// 				}
// 			}
		}
		break;
	}
	return 1;
}

void GcEditorTexture::SelectChangeListItem(int iItem)
{
	mTextureBox.SetTextureInfo( mTextureLists.GetAt( iItem ) );
}

void GcEditorTexture::SelectChangeTextureItem(int iItem)
{
	int sel = mTextureListBox.GetSelItem();
	if( sel == -1 )
		return;

	TextureListInfo* listInfo = mTextureLists.GetAt( sel );
	GnAssert( listInfo );
	if( listInfo == NULL )
		return;
	
	TextureListInfo::TextureInfo* testureInfo = listInfo->GetTextures()->GetAt( iItem );	
	mpTextureAnimationPropEntity.SetIndex( iItem );
	mpTextureAnimationPropEntity.SetTextureFilePath( testureInfo->GetTextureName() );
}

void GcEditorTexture::GeFileName(CString strName)
{
	gtchar filePath[GN_MAX_PATH] = { 0, };
	GnVerify( GnPath::GetFileName( strName.GetString(), filePath, GN_MAX_PATH, true ) );	
	strName = filePath;
}

void GcEditorTexture::OnOK()
{
	//float endTime = 0.0f;
	//for( gtuint i = 0 ; i < mpsCurrentAni->GetAniInfoCount() ; i++ )
	//{
	//	GnAnimation::AniInfo* info = mpsCurrentAni->GetAniInfo( i );
	//	endTime += info->GetEndTime();
	//}
	//Gn2DSequence* gnSequence = mpSequence->GetSequence();
	//gnSequence->SetStartTime( 0 );
	//gnSequence->SetEndTime( endTime );
}

void GcEditorTexture::OnChangeDefaultstarttime()
{
}


void GcEditorTexture::OnChangeDefaultendtime()
{
}

void GcEditorTexture::OnDeltaposDefaultstarttime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void GcEditorTexture::OnDeltaposDefaultendtime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}

bool GcEditorTexture::CheckEnableButton()
{
	if( GcEditorPropertyPage::CheckEnableButton() == false )
		return false;

	if( mTextureLists.GetSize() )
	{
		TextureListInfo* listInof = mTextureLists.GetAt( 0 );
		if( listInof->GetTextures()->GetSize() )
			return true;
	}
	return false;
}