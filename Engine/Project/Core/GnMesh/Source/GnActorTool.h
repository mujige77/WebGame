#ifndef GNACTORTOOL_H
#define GNACTORTOOL_H

class GNMESH_ENTRY GnActorTool : public GnSmartObject
{
	GnDeclareRTTI;
	GnDeclareDataStream;
public:
	class GNMESH_ENTRY SequenceInfo : public GnMemoryObject
	{
		GnDeclareDataStream;
	public:
		guint32 mSequenceID;
		GnSimpleString mSequenceName;
		GnSimpleString mFileName;		
		inline guint32 GetSequenceID() { return mSequenceID; }
		inline void SetSequenceID(guint32 val) { mSequenceID = val; }
		inline GnSimpleString& GetSequenceName() { return mSequenceName; }
		inline void SetSequenceName(GnSimpleString val) { mSequenceName = val; }
		inline GnSimpleString& GetFileName() { return mFileName; }
		inline void SetFileName(GnSimpleString val) { mFileName = val; }
	};
protected:
	GnTObjectDeleteMap<guint32, SequenceInfo*> mpSequences;
	GnSimpleString mName;
	GnSimpleString mGATFilePath;
	GnSimpleString mGMFilePath;

public:
	GnActorTool(){};
	virtual ~GnActorTool(){};

	inline bool GetGAFullFileName(guint32 uiID, gchar* pcOutPath, gtuint uiMaxSize) {
		SequenceInfo* sequenceInfo = NULL;
		if( GetSequenceInfo( uiID, sequenceInfo ) )
		{
			pcOutPath[0] = '\0';
			return false;
		}
		return GetGAFullFileName( sequenceInfo, pcOutPath, uiMaxSize );
	}
	bool GetGAFullFileName(SequenceInfo* pSequenceInfo, gchar* pcOutPath, gtuint uiMaxSize);
	inline GnSimpleString GetName() {
		return mName;
	}
	inline void SetName(GnSimpleString val) {
		mName = val;
	}
	inline GnSimpleString& GetGATFilePath() {
		return mGATFilePath;
	}
	inline void SetGATFilePath(GnSimpleString& val) {
		mGATFilePath = val;
	}	
	inline GnSimpleString& GetGMFilePath() {
		return mGMFilePath;
	}
	inline void SetGMFilePath(GnSimpleString& val) {
		mGMFilePath = val;
	}

	inline gtuint GetSequenceInfoCount() {
		return mpSequences.Count();
	}
	void GetSequenceInfos(GnTPrimitiveArray<SequenceInfo*>& outInfo);
	
	inline bool GetSequenceInfo(guint32 uiID, SequenceInfo*& pSequences) {
		return mpSequences.GetAt(uiID, pSequences);
	}
	inline void AddSequenceInfo(guint32 uiID, SequenceInfo* pSequences) {
		mpSequences.Insert(uiID, pSequences);
	}
	inline void SetSequenceInfo(guint32 uiID, SequenceInfo* pSequences) {
		mpSequences.SetAt(uiID, pSequences, true);
	}
	inline void RemoveSequenceInfo(guint32 uiID) {
		mpSequences.Remove(uiID, true);
	}
	inline void RemoveAllSequenceInfo() {
		mpSequences.RemoveAll(true);
	}
};

GnSmartPointer(GnActorTool);
#endif // GNACTORTOOL_H