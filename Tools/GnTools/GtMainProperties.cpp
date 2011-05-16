// GtMainProperties.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GnTools.h"
#include "GtMainProperties.h"
#include "GtBasicPropEntity.h"
#include "GtSequenceInfoPropEntity.h"
#include "GtScreenMeshPropEntity.h"
#include "GnObjectNew.h"
// GtMainProperties

IMPLEMENT_DYNAMIC(GtMainProperties, GtToolBarForm)

GtMainProperties::GtMainProperties() : mpEntities(NULL)
{

}

GtMainProperties::~GtMainProperties()
{
	if( mpEntities )
		delete mpEntities;
}


BEGIN_MESSAGE_MAP(GtMainProperties, GtToolBarForm)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnEditSequence)
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
END_MESSAGE_MAP()



// GtMainProperties 메시지 처리기입니다.


bool GtMainProperties::SetObject(GnAVObject* object)
{
	return true;
}

int GtMainProperties::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if ( GtToolBarForm::OnCreate(lpCreateStruct) == -1 )
		return -1;
	
	AttachNeedMessage( GTMG_SELECTOBJECT );

	CRect rectDummy;
	rectDummy.SetRectEmpty();
	if ( mPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2) == false )
	{
		TRACE0("속성 표를 만들지 못했습니다. \n");
		return -1;      // 만들지 못했습니다.
	}
	mPropList.SetVSDotNetLook( TRUE );
	if( mpEntities == NULL )
		mpEntities = new GtCollectionEntities(&mPropList);

	mToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	mToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* 잠금 */);
	mToolBar.CleanUpLockedImages();
	mToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* 잠금 */);

	mToolBar.SetPaneStyle(mToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	mToolBar.SetPaneStyle(mToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	mToolBar.SetOwner(this);
	// 모든 명령은 부모 프레임이 아닌 이 컨트롤을 통해 라우팅됩니다.
	mToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();
	return 0;
}


void GtMainProperties::OnSize(UINT nType, int cx, int cy)
{
	GtToolBarForm::OnSize(nType, cx, cy);

	AdjustLayout();
}

void GtMainProperties::AdjustLayout()
{
	CRect rectClient, rectToolBar;
	GetClientRect(rectClient);	
	mToolBar.GetWindowRect( rectToolBar );
	int cyToolbar = rectToolBar.Size().cy;

	mToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top , rectClient.Width(), cyToolbar, SWP_NOACTIVATE | SWP_NOZORDER);
	mPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + cyToolbar, rectClient.Width(), rectClient.Height() - cyToolbar,
		SWP_NOACTIVATE | SWP_NOZORDER);
}

void GtMainProperties::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	mPropList.SetFocus();
}

void GtMainProperties::ReceiveMediateMessage(gtuint messageIndex, GtMediateObjectMessage* pSander)
{
	switch( messageIndex )
	{
	case GTMG_SELECTOBJECT:
		ChangeProperty(pSander);
		break;
	}
}

void GtMainProperties::ChangeProperty(GtMediateObjectMessage* pInfo)
{
	GtObjectMessage* objectInfo = (GtObjectMessage*)pInfo;
	GnAssert( objectInfo );
	GnAssert( objectInfo->mpObject );

	GnFrame* gnFrame = GetActiveGnFrame();
	if( gnFrame )
		gnFrame->RemoveObject( mpsCurrentObject );

	mpsCurrentObject = objectInfo->mpObject;
	mpEntities->DetachAllEntity();

	GtPropertyEntity* object = NULL;
	object = GnObjectNew<GtBasicPropEntity>::Create();
	object->ParseToEntity( mpsCurrentObject );
	mpEntities->AttachEntity( object );

	object = GnObjectNew<GtScreenMeshPropEntity>::Create();
	object->ParseToEntity( mpsCurrentObject );
	mpEntities->AttachEntity( object );

	if( mpsCurrentObject->GetType() != GtActorObject::GTPLANEACTORTYPE )
		return;
}

void GtMainProperties::OnEditSequence()
{
	if( mpsCurrentObject )
		return;
}

LRESULT GtMainProperties::OnPropertyChanged(WPARAM wparam, LPARAM lparam)
{
	CMFCPropertyGridProperty *pProp = (CMFCPropertyGridProperty*)lparam;
	if (!pProp) return 0;

	switch( pProp->GetData() )
	{
	case GtBasicPropEntity::MSG_OBJECTNAME:
		break;
	case GtBasicPropEntity::MSG_OBJECTTYPE:
		break;
	case GtBasicPropEntity::MSG_FILENAME:
		break;
	case GtBasicPropEntity::MSG_OBJECTINDEX:
		break;
	case GtSequenceInfoPropEntity::MSG_FILENAME:
		break;
	case GtSequenceInfoPropEntity::MSG_SEQUENCEID:
		break;
	case GtScreenMeshPropEntity::MSG_HEIGHT:					
	case GtScreenMeshPropEntity::MSG_WIDTH:
		{
			GtScreenMeshPropEntity* enitiy = GetEntityFromClassNameDef( mpEntities,  GtScreenMeshPropEntity );
			enitiy->ParseToObject( mpsCurrentObject );
		}
		break;
	}
	return 1;
}

void GtMainProperties::OnSaveObjectstate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
