#include "GnGamePCH.h"
#include "GUserHaveItem.h"

bool GUserHaveItem::CreateHaveItem(const gchar* pcName)
{
	gstring fullPath;
	GetWriteablePath( USER_HAVEDATA_FILENAME, fullPath );
	gint ret = Open( fullPath.c_str() );
	
	if( GnSQLite::GNSQLITE_SUCCESS != ret )
		return false;
	
	Execute( "CREATE TABLE %s(idx INT, type INT, level INT, count INT);", pcName );
	
	mCurrentTableName = pcName;
	CreateBasicUnit();
	CreateBasicAbility();
	
	Close();
	return true;
}

bool GUserHaveItem::DropHaveItem(const gchar* pcName)
{
	gstring fullPath;
	GetWriteablePath( USER_HAVEDATA_FILENAME, fullPath );
	gint ret = Open( fullPath.c_str());
	
	if( GnSQLite::GNSQLITE_SUCCESS != ret )
		return false;
	
	Execute( "DROP TABLE %s;", pcName );
	Close();
	return true;
}

bool GUserHaveItem::OpenPlayerItem(const gchar* pcName)
{
	gstring fullPath;
	GetWriteablePath( USER_HAVEDATA_FILENAME, fullPath );
	gint ret = Open( fullPath.c_str());
	
	if( GnSQLite::GNSQLITE_SUCCESS != ret )
		return false;
	
	mCurrentTableName = pcName;
	return true;
}

void GUserHaveItem::Close()
{
	mOpenItemTable.Finalize();	
	GnSQLite::Close();
}

void GUserHaveItem::AddItem(guint32 uiIndex, eItemType uiType, guint32 uiLevel, guint32 uiCount)
{
	GnVerify( Execute( "INSERT INTO %s VALUES(%d, %d, %d, %d);", mCurrentTableName.GetHandle(), uiIndex
		, uiType, uiLevel, uiCount ) == 0 );
}

void GUserHaveItem::DeleteItem(guint32 uiIndex, eItemType type)
{
	GnVerify( Execute(  "DELETE FROM %s WHERE rowid = (SELECT rowid FROM %s WHERE idx=%d AND type=%d LIMIT 1)"
		, mCurrentTableName.GetHandle(), mCurrentTableName.GetHandle(), uiIndex, type ) == 0 );	
}

guint32 GUserHaveItem::GetItemLevel(guint32 uiIndex)
{
	GnSQLiteQuery query = ExecuteSingleQuery( "SELECT * FROM %s WHERE idx=%d"
		, mCurrentTableName.GetHandle(), uiIndex );
#if GNDEBUG
	gint levelIndex = query.GetFieldIndex( "level" );
	if( levelIndex != eLevel )		
		GnLogA( "Error UserHaveItem GetItemLevel not equal levelIndex" );
#endif
	return query.GetIntField( eLevel );
}

guint32 GUserHaveItem::GetItemCount(guint32 uiIndex)
{
	GnSQLiteQuery query = ExecuteSingleQuery( "SELECT * FROM %s WHERE idx=%d"
		, mCurrentTableName.GetHandle(), uiIndex );
#if GNDEBUG
	gint levelIndex = query.GetFieldIndex( "count" );
	if( levelIndex != eCount )		
		GnLogA( "Error UserHaveItem GetItemCount not equal count" );
#endif
	return query.GetIntField( eCount );
}

bool GUserHaveItem::GetItem(guint32 uiIndex, GUserHaveItem::Item& outItem)
{
	GnSQLiteQuery query = ExecuteSingleQuery( "SELECT * FROM %s WHERE idx=%d"
		, mCurrentTableName.GetHandle(), uiIndex );

	if( query.QueryReturn() == false )
		return false;
	
	GUserHaveItem::Item item = 
	{
		query.GetIntField( 0 ),
		(eItemType)query.GetIntField( 1 ),
		query.GetIntField( 2 ),
		query.GetIntField( 3 )
	};
	outItem = item;
	return true;
}

bool GUserHaveItem::GetItems(eItemType uiType, GnList<GUserHaveItem::Item>& outItem)
{
	GnSQLiteQuery query = ExecuteSingleQuery( "SELECT * FROM %s WHERE type=%d"
		, mCurrentTableName.GetHandle(), uiType );

	while ( query.IsEof() == false )
	{
		GUserHaveItem::Item item = 
		{
			query.GetIntField( 0 ),
			(eItemType)query.GetIntField( 1 ),
			query.GetIntField( 2 ),
			query.GetIntField( 3 )
		};

		outItem.Append( item );
		query.NextRow();
	}
	return true;
}

void GUserHaveItem::UpdateLevel(guint32 uiIndex, guint32 uiLevel)
{
	GnVerify( Execute( "UPDATE %s SET level=%d WHERE idx=%d;", mCurrentTableName.GetHandle(), uiLevel
					  , uiIndex ) == 0 );
}


void GUserHaveItem::UpdateCount(guint32 uiIndex, guint32 uiCount)
{
	GnVerify( Execute( "UPDATE %s SET count=%d WHERE idx=%d;", mCurrentTableName.GetHandle(), uiCount
					  , uiIndex ) == 0 );
}

void GUserHaveItem::CreateBasicUnit()
{
	guint32 count = eMaxIndexUnit - INDEX_UNIT;
	for ( gtuint i = 0; i < count; i++ )
	{
		if( i == 1 )
			AddItem( i + INDEX_UNIT, eUnit, 1 );
		else
			AddItem( i + INDEX_UNIT, eUnit );
	}	
}

void GUserHaveItem::CreateBasicAbility()
{
	guint32 count = eMaxIndexAbility - INDEX_ABILITY;
	for ( gtuint i = 0; i < count; i++ )
	{
		AddItem( i + INDEX_ABILITY, eAbility );
	}
}