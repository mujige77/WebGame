#include "GnMeshPCH.h"
#include "GnSQLiteTable.h"
#include "sqlite3.h"

GnSQLiteTable::GnSQLiteTable()
{
	mpaszResults = 0;
	mnRows = 0;
	mnCols = 0;
	mnCurrentRow = 0;
}


GnSQLiteTable::GnSQLiteTable(const GnSQLiteTable& rTable)
{
	mpaszResults = rTable.mpaszResults;
	// Only one object can own the results
	const_cast<GnSQLiteTable&>(rTable).mpaszResults = 0;
	mnRows = rTable.mnRows;
	mnCols = rTable.mnCols;
	mnCurrentRow = rTable.mnCurrentRow;
}


GnSQLiteTable::GnSQLiteTable(char** paszResults, int nRows, int nCols)
{
	mpaszResults = paszResults;
	mnRows = nRows;
	mnCols = nCols;
	mnCurrentRow = 0;
}


GnSQLiteTable::~GnSQLiteTable()
{
	try
	{
		Finalize();
	}
	catch (...)
	{
	}
}


GnSQLiteTable& GnSQLiteTable::operator=(const GnSQLiteTable& rTable)
{
	try
	{
		Finalize();
	}
	catch (...)
	{
	}
	mpaszResults = rTable.mpaszResults;
	// Only one object can own the results
	const_cast<GnSQLiteTable&>(rTable).mpaszResults = 0;
	mnRows = rTable.mnRows;
	mnCols = rTable.mnCols;
	mnCurrentRow = rTable.mnCurrentRow;
	return *this;
}


void GnSQLiteTable::Finalize()
{
	if (mpaszResults)
	{
		sqlite3_free_table(mpaszResults);
		mpaszResults = 0;
	}
}


int GnSQLiteTable::NumFields()
{
	CheckResults();
	return mnCols;
}


int GnSQLiteTable::NumRows()
{
	CheckResults();
	return mnRows;
}


const char* GnSQLiteTable::FieldValue(int nField)
{
	CheckResults();
	
	if (nField < 0 || nField > mnCols-1)
	{
		return NULL;
	}
	
	int nIndex = (mnCurrentRow*mnCols) + mnCols + nField;
	return mpaszResults[nIndex];
}


const char* GnSQLiteTable::FieldValue(const char* szField)
{
	CheckResults();
	
	if (szField)
	{
		for (int nField = 0; nField < mnCols; nField++)
		{
			if (strcmp(szField, mpaszResults[nField]) == 0)
			{
				int nIndex = (mnCurrentRow*mnCols) + mnCols + nField;
				return mpaszResults[nIndex];
			}
		}
	}
	
	return NULL;
}


int GnSQLiteTable::GetIntField(int nField, int nNullValue/*=0*/)
{
	if ( FieldIsNull( nField ) )
	{
		return nNullValue;
	}
	else
	{
		return atoi( FieldValue( nField ) );
	}
}


int GnSQLiteTable::GetIntField(const char* szField, int nNullValue/*=0*/)
{
	if ( FieldIsNull(szField))
	{
		return nNullValue;
	}
	else
	{
		return atoi( FieldValue( szField ) );
	}
}


double GnSQLiteTable::GetFloatField(int nField, double fNullValue/*=0.0*/)
{
	if ( FieldIsNull(nField))
	{
		return fNullValue;
	}
	else
	{
		return atof( FieldValue(nField) );
	}
}


double GnSQLiteTable::GetFloatField(const char* szField, double fNullValue/*=0.0*/)
{
	if ( FieldIsNull(szField) )
	{
		return fNullValue;
	}
	else
	{
		return atof( FieldValue(szField) );
	}
}


const char* GnSQLiteTable::GetStringField(int nField, const char* szNullValue/*=""*/)
{
	if ( FieldIsNull(nField) )
	{
		return szNullValue;
	}
	else
	{
		return FieldValue(nField);
	}
}


const char* GnSQLiteTable::GetStringField(const char* szField, const char* szNullValue/*=""*/)
{
	if ( FieldIsNull(szField) )
	{
		return szNullValue;
	}
	else
	{
		return FieldValue(szField);
	}
}


bool GnSQLiteTable::FieldIsNull(int nField)
{
	CheckResults();
	return ( FieldValue(nField) == 0 );
}


bool GnSQLiteTable::FieldIsNull(const char* szField)
{
	CheckResults();
	return ( FieldValue(szField) == 0 );
}


const char* GnSQLiteTable::FieldName(int nCol)
{
	CheckResults();
	
	if ( nCol < 0 || nCol > mnCols-1 )
	{
		return NULL;
	}
	
	return mpaszResults[nCol];
}


void GnSQLiteTable::SetRow(int nRow)
{
	CheckResults();
	
	if (nRow < 0 || nRow > mnRows-1)
	{
		return;
	}
	
	mnCurrentRow = nRow;
}


void GnSQLiteTable::CheckResults()
{
	if (mpaszResults == 0)
	{
		return;
	}
}