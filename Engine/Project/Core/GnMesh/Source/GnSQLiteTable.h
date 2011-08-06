//
//  GnSQLiteTable.h
//  Core
//
//  Created by Max Yoon on 11. 8. 4..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef Core_GnSQLiteTable_h
#define Core_GnSQLiteTable_h

class GnSQLiteTable
{
private:
	int mnCols;
    int mnRows;
    int mnCurrentRow;
    char** mpaszResults;
	
public:
	
    GnSQLiteTable();
	
    GnSQLiteTable(const GnSQLiteTable& rTable);
	
    GnSQLiteTable(char** paszResults, int nRows, int nCols);
	
    virtual ~GnSQLiteTable();
	
    GnSQLiteTable& operator=(const GnSQLiteTable& rTable);
	
    int NumFields();
	
    int NumRows();
	
    const char* FieldName(int nCol);
	
    const char* FieldValue(int nField);
    const char* FieldValue(const char* szField);
	
    int GetIntField(int nField, int nNullValue=0);
    int GetIntField(const char* szField, int nNullValue=0);
	
    double GetFloatField(int nField, double fNullValue=0.0);
    double GetFloatField(const char* szField, double fNullValue=0.0);
	
    const char* GetStringField(int nField, const char* szNullValue="");
    const char* GetStringField(const char* szField, const char* szNullValue="");
	
    bool FieldIsNull(int nField);
    bool FieldIsNull(const char* szField);
	
    void SetRow(int nRow);
	
    void Finalize();
	
private:
    void CheckResults();
};

#endif
