#ifndef __Core__GnSQLiteQuery__
#define __Core__GnSQLiteQuery__



class sqlite3_stmt;
class GnSQLiteQuery
{
	enum
	{
		GNSQLITE_NULL = 5,
	};
private:
	sqlite3_stmt* mpStatement;
	bool mEof;
	guint mColumnCount;
	
public:
	GnSQLiteQuery(sqlite3_stmt* pStatement, bool bEof);
	virtual ~GnSQLiteQuery();
	
	gint GetFieldDataType(gint iNumColumn);
	gint GetIntField(gint iNumColumn);
	double GetFloatField(gint iNumColumn);
	const gchar* GetStringField(gint iNumColumn);
	gint GetFieldIndex(const gchar* szField);
	const gchar* GetFieldName(gint iCol);
	const gchar* GetFieldDeclType(gint iCol);
	void NextRow();
	void Finalize();
public:
	inline void SetColumnCount(guint uiCount) {
		mColumnCount = uiCount;
	}
	inline guint GetColumnCount() {
		return mColumnCount;
	}
	inline void SetIsEof(bool val) {
		mEof = true;
	}
	inline bool IsEof() {
		return mEof;
	}
};

#endif
