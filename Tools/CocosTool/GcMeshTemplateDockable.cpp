// GcMeshTemplateDockable.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GcMeshTemplateDockable.h"
#include "GcNewObjectDlg.h"
#include "ActorMacro.h"

GcMeshTemplateDockable::GcMeshTemplateDockable()
{
}

GcMeshTemplateDockable::~GcMeshTemplateDockable()
{
}

void GcMeshTemplateDockable::ReciveNotiyfiMessage(WPARAM wParam, LPARAM lParam)
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
					SendMediateMessage( GTMG_SELECT2DOBJECT, &info );
				}		
			}
			break;
		}
	}
}

Gt2DObject* GcMeshTemplateDockable::GetActorObject(CString itemText)
{
	GtConvertString strName = itemText.GetString();
	Gt2DObject* object = GnDynamicCast( Gt2DObject, GetObjectFactory()->GetObject( itemText ) );
	if(  object == NULL )
	{
		object = (Gt2DObject*)GetObjectFactory()->CreateObject( Gt2DObject::OBJECT_TYPE, itemText );
	}
	GnAssert( object );
	object->SetObjectName( strName.GetAciiString() );
	return object;
}

void GcMeshTemplateDockable::SelectItem(int iIndex)
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	if( mpsCurrentObject )
	{
		switch( mpsCurrentObject->GetType() )
		{
		case Gt2DObject::OBJECT_TYPE:
			{
				Gt2DObject* object = GnDynamicCast( Gt2DObject, mpsCurrentObject );				
				GnLayer* state = GetSceneManager()->GetMainGameLayer();
				state->RemoveChild( object->Get2DMeshObjecct() );
				SendMediateMessage( GTMG_REDRAW, NULL );
			}
			break;
		default:
			return;
		}
	}
	CString itemText = mListCtrl.GetItemText( iIndex, 0 );
	Gt2DObject* object = GnDynamicCast( Gt2DObject, GetActorObject( itemText ) );
	if( object == NULL )
		return;

	TemplateListData data = GetTemplateListData( iIndex );
	object->Set2DObjectType( data.mObjectType );
	mpsCurrentObject = object;
	//if( object->IsNewItem() == false )
	//{
		if( object->LoadData() == false )
			GnVerify( object->CreateData() );
	//}
	//else
	//	GnVerify( object->CreateData() );

	GcObjectMessage info;
	info.mpObject = object;
	info.mpSender = this;
	SendMediateMessage( GTMG_SELECT2DOBJECT, &info );
}

void GcMeshTemplateDockable::DoNewTemplate()
{
	GcNewObjectDlg dlg;
	if( dlg.DoModal() == IDCANCEL )
		return;

	CString itemName = dlg.GetObjectName();
	if( itemName.GetLength() <= 0 )
		return;

	int type = dlg.GetObjectType();
	GtObject* object = GetActorObject( itemName );
	GnAssert( object );
	object->SetNewItem( true );

	AddItem( itemName, type, true );

	GcObjectMessage info;
	info.mpObject = object;
	info.mpSender = this;
	SendMediateMessage( GTMG_NEWOBJECT, &info );
}

void GcMeshTemplateDockable::DoDelTemplate()
{

}

void GcMeshTemplateDockable::DoOpenTemplate()
{

}