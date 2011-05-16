#ifndef GNDATASTREAM_H
#define GNDATASTREAM_H

class GnDataStreamList : public GnList<GnDataStream*>
{
public:
	GnDataStreamList();
	void AddDataStream(GnDataStream* element);
	void RemoveAllStream();

private:
	gtuint mStride;
};

// 버텍스 버퍼를 만들기위한 클래스
class GNMESH_ENTRY GnMeshData : public GnObject
{
	GnDeclareRTTI;
	GnDeclareFlags(guint8);
	GnDeclareStream;
public:
	enum 
	{
		ADD_DATASTREAM_MASK = 0x01,
	};

protected:
	GnDataStreamList mDataStreams;

public:
	inline GnMeshData()
	{
		SetAddDataStream( false );
	};
	virtual ~GnMeshData();

	// 내가 필요한 버텍스 정보를 저장 한다.
	GnDataStream* AddDataStream(const GnDataStream::eFormat format, guint32 uiVertexCount);
	GnDataStream* GetDataStream(const GnDataStream::eFormat format, guint8 uiIndex = 0);
	virtual GnDataStream* CreateDataStream(GnDataStream::eFormat format, guint32 vertexCount) = 0;

	inline GnDataStreamList& GetDataStreams()
	{
		return mDataStreams;
	}

	inline void Update()
	{
		UpdateData();
	}

protected:	
	// GnDataStream이 추가 되거나 삭제 되면 true가 되어 데이터를 업데이트(UpdateData) 한다.
	inline bool IsAddDataStream()
	{
		return GetBit( ADD_DATASTREAM_MASK );
	}
	inline void SetAddDataStream(bool val)
	{
		SetBit( val, ADD_DATASTREAM_MASK );
	}

protected:
	virtual void UpdateData() = 0;
};

#endif // GNDATASTREAM_H