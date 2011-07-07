// GcEffectTemplateDockable.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GcEffectTemplateDockable.h"
#include "GcNewObjectDlg.h"
#include "ActorMacro.h"

GcEffectTemplateDockable::GcEffectTemplateDockable()
{
}

GcEffectTemplateDockable::~GcEffectTemplateDockable()
{
}

void GcEffectTemplateDockable::ReciveNotiyfiMessage(WPARAM wParam, LPARAM lParam)
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
				SelectItem( mLastSelectItem );
				return;
			}
			break;
		case LVN_INSERTITEM:
			{
			}
			break;
		case LVN_DELETEITEM:
			{
				if( mListCtrl.GetItemCount() == 1 )
				{
					mLastSelectItem = -1;
					GcObjectMessage info;
					info.mpObject = NULL;
					info.mpSender = this;
					SendMediateMessage( GTMG_SELECTOBJECT, &info );
				}
				else if( mListCtrl.GetItemCount() )
				{
					GcSequenceMessage sequenceMsg;
					sequenceMsg .mpObject = NULL;
					sequenceMsg .mpSender = this;
					sequenceMsg .mpSequenceInfo = NULL;
					SendMediateMessage( GTMG_SELECTSEQUENCE, &sequenceMsg );
				}				
			}
			break;
		}
	}
}

Gt2DActor* GcEffectTemplateDockable::GetActorObject(CString itemText)
{
	GtConvertString strName = itemText.GetString();
	Gt2DActor* object = (Gt2DActor*)GetObjectFactory()->GetObject( itemText );
	if(  object == NULL )
	{
		object = (Gt2DActor*)GetObjectFactory()->CreateObject( Gt2DActor::OBJECT_TYPE, itemText );
	}
	GnAssert( object );
	object->SetObjectName( strName.GetAciiString() );
	return object;
}

void GcEffectTemplateDockable::SelectItem(int iIndex)
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	if( mpsCurrentObject )
	{
		switch( mpsCurrentObject->GetType() )
		{
		case Gt2DActor::OBJECT_TYPE:
			{
				Gt2DActor* object = (Gt2DActor*)((GtObject*)mpsCurrentObject);
				object->GetActor()->StopAnimation();
				SendMediateMessage( GTMG_REDRAW, NULL );
				GnLayer* state = GetSceneManager()->GetMainGameLayer();
				state->RemoveChild( object->GetActor()->GetRootNode() );
			}

		}
	}
	CString itemText = mListCtrl.GetItemText( iIndex, 0 );
	Gt2DActor* object = GetActorObject(itemText);
	if( object == NULL )
		return;

	mpsCurrentObject = object;
	if( object->IsNewItem() == false )
	{
		if( object->LoadData() == false )
			GnVerify( object->CreateData() );
	}
	else
	{
		GnVerify( object->CreateData() );
	}

	object->GetRootNode()->SetScale( 1.0f );
	object->GetRootNode()->GetMesh()->setAnchorPoint( CCPointMake(0,0) );
	object->GetRootNode()->SetPosition( ActorBasePosition );
	//object->GetRootNode()->GetMesh()->setFlipX( true );
	GnLayer* state = GetSceneManager()->GetMainGameLayer();
	state->AddChild( object->GetRootNode(), 102 );

	GcObjectMessage info;
	info.mpObject = object;
	info.mpSender = this;
	SendMediateMessage( GTMG_SELECTOBJECT, &info );
}

void GcEffectTemplateDockable::OnSaveObjectstate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	gchar filePath[GN_MAX_PATH];
	GtToolSettings::MakeSaveFilePath( "templatelist.lst", NULL, filePath, GN_MAX_PATH );
	SaveTemplateList( filePath );
}