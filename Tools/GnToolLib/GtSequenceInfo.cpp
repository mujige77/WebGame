#include "GnToolLibPCH.h"
#include "GtSequenceInfo.h"
#include "GnSMTextureAniCtrl.h"
#include "GtSMTextureAniCtrl.h"

GtSequenceInfo::GtSequenceInfo() : mStartTime( 0.0f ), mEndTime( 0.0f ), mSequenceID(GUINT32_MAX)
{

}

void GtSequenceInfo::RemoveController(GtTimeController* pCtlr)
{
	for( gtuint i = 0 ; i < mTimeCtlrs.GetSize() ; i++ )
	{
		if( pCtlr == mTimeCtlrs.GetAt(i) )
		{
			mTimeCtlrs.RemoveAtAndFillAll( i );
			return;
		}
	}
}

void GtSequenceInfo::ChangePostionController(GtTimeController* pCtlr1, GtTimeController* pCtlr2)
{
	gtuint index1 = 0;
	for(  ; index1 < mTimeCtlrs.GetSize() ; index1++ )
	{
		if( mTimeCtlrs.GetAt( index1 ) == pCtlr1 )
			break;
	}
	GnAssert( index1 < mTimeCtlrs.GetSize() );

	gtuint index2 = 0;
	for(  ; index2 < mTimeCtlrs.GetSize() ; index2++ )
	{
		if( mTimeCtlrs.GetAt( index2 ) == pCtlr2 )
			break;
	}
	GnAssert( index2 < mTimeCtlrs.GetSize() );

	mTimeCtlrs.SetAt( index1, pCtlr2 );
	mTimeCtlrs.SetAt( index2, pCtlr1 );
}

void GtSequenceInfo::SaveStream(const gchar* objectName, const gchar* basePath)
{
	for( gtuint i = 0 ; i < mTimeCtlrs.GetSize() ; i++ )
	{
		GtTimeController* ctlr =mTimeCtlrs.GetAt( i );
		if( ctlr )
		{
			ctlr->SaveStream(objectName, basePath);
			break;
		}
	}

	GnSequence* sequence = CreateSequence();	
	GnObjectStream gnStream;

	gchar outPath[GN_MAX_PATH] = {0,};
	GnStrcpy( outPath, basePath, sizeof(outPath) );
	GnStrcat( outPath, mFileName, sizeof(outPath) );
	
	gnStream.InsertRootObjects( sequence );

	gnStream.Save( outPath );
	gchar outPath2[GN_MAX_PATH] = {0,};
	GnPath::GetFullPathA( outPath, outPath2, GN_MAX_PATH );
	GnLogA( "GtActorObject SaveStream %s", outPath2 );
	gnStream.Close();

	GnDelete sequence;
}

void GtSequenceInfo::LoadStream(const gchar* objectName, const gchar* basePath)
{
	GnObjectStream gnStream;

	gchar outPath[GN_MAX_PATH] = {0,};
	GnStrcpy( outPath, basePath, sizeof(outPath) );
	GnStrcat( outPath, mFileName, sizeof(outPath) );

	if( gnStream.Load( outPath ) == false )
		return;

	GnSequence* sequence = (GnSequence*)gnStream.GetObject( 0 );
	gnStream.Close();

	SetStartTime( sequence->GetStartTime() );
	SetEndTime( sequence->GetEndTime() );
	SetName( sequence->GetName() );

	GnSMTextureAniCtrl* timeCtlr = (GnSMTextureAniCtrl*)sequence->GetTimeControls();
	while( timeCtlr )
	{
		GtSMTextureAniCtrl* gtTimectlr = GtSMTextureAniCtrl::CreateFromGnData(timeCtlr);
		mTimeCtlrs.Add( gtTimectlr );
		timeCtlr = (GnSMTextureAniCtrl*)timeCtlr->GetNext();
	}
	
	GnDelete sequence;
}

GnSequence* GtSequenceInfo::CreateSequence()
{
	GnSequence* sequence = GnNew GnSequence();
	sequence->SetStartTime( mStartTime );
	sequence->SetEndTime( mEndTime );
	sequence->SetName( mName  );
	GnTimeController* gnRootTimeCtlr = NULL;
	GnTimeController* gnTimeCtlr = NULL;
	for( gtuint i = 0 ; i < mTimeCtlrs.GetSize() ; i++ )
	{
		GtTimeController* gtTimeCtlr = mTimeCtlrs.GetAt( i );
		GnTimeController* temp = gtTimeCtlr->CreateGnTimeController();
		if( gnTimeCtlr )
			gnTimeCtlr->SetNext( temp );
		else
			gnRootTimeCtlr = temp;
		gnTimeCtlr = temp;
	}
	sequence->SetTimeControls(gnRootTimeCtlr);
	return sequence;
}