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
		inline const gchar* GetSequenceName() { return mSequenceName; }
		inline void SetSequenceName(const gchar* val) { mSequenceName = val; }
		inline const gchar* GetFileName() { return mFileName; }
		inline void SetFileName(const gchar* val) { mFileName = val; }
	};
protected:
	GnTObjectDeleteMap<guint32, SequenceInfo*> mpSequences;
	GnSimpleString mGATFilePath;
	GnSimpleString mGMFilePath;

public:
	GnActorTool(){};
	virtual ~GnActorTool(){};

	void GetSequenceInfos(GnTPrimitiveArray<SequenceInfo*>& outInfo);
	void AddSequenceInfo(guint32 uiID, const gchar* pcName, const gchar* pcFileName);
	bool GetGAFullFileName(SequenceInfo* pSequenceInfo, gchar* pcOutPath, gtuint uiMaxSize);	
	inline bool GetGAFullFileName(guint32 uiID, gchar* pcOutPath, gtuint uiMaxSize) {
		SequenceInfo* sequenceInfo = NULL;
		if( GetSequenceInfo( uiID, sequenceInfo ) == false )
		{
			pcOutPath[0] = '\0';
			return false;
		}
		return GetGAFullFileName( sequenceInfo, pcOutPath, uiMaxSize );
	}	
	
	inline const gchar* GetGATFilePath() {
		return mGATFilePath;
	}
	inline void SetGATFilePath(const gchar* val) {
		mGATFilePath = val;
	}	
	inline const gchar* GetGMFilePath() {
		return mGMFilePath;
	}
	inline void SetGMFilePath(const gchar* val) {
		mGMFilePath = val;
	}

	inline gtuint GetSequenceInfoCount() {
		return mpSequences.Count();
	}	
	
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