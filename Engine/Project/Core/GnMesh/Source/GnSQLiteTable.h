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
	gint mnCols;
    gint mnRows;
    gint mnCurrentRow;
    char** mpaszResults;
	
public:
	
    GnSQLiteTable();
	
    GnSQLiteTable(const GnSQLiteTable& rTable);
	
    GnSQLiteTable(char** paszResults, int nRows, int nCols);
	
    virtual ~GnSQLiteTable();
	
    GnSQLiteTable& operator=(const GnSQLiteTable& rTable);
	
    gint NumFields();
	
    gint NumRows();
	
    const char* FieldName(int nCol);
	
    const char* FieldValue(int nField);
    const char* FieldValue(const char* szField);
	
	gint GetIntField(gint nField, gint nNullValue=0);
    gint GetIntField(const char* szField, gint nNullValue=0);
	
    double GetFloatField(gint nField, double fNullValue=0.0);
    double GetFloatField(const char* szField, double fNullValue=0.0);
	
    const char* GetStringField(gint nField, const char* szNullValue="");
    const char* GetStringField(const char* szField, const char* szNullValue="");
	
    bool FieldIsNull(gint nField);
    bool FieldIsNull(const char* szField);
	
    void SetRow(gint nRow);
	
    void Finalize();
	
private:
    void CheckResults();
};

#endif
