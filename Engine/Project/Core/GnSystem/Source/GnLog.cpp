#include "GnSystemPCH.h"
#include "GnLog.h"

const gtuint gMaxDebugMessageLength = 256;

GNFORCEINLINE void LineCheck( gtchar* message, gsize& messageLength )
{
	if (message[messageLength-1] != '\n')
	{
		message[messageLength] = '\n';
		message[messageLength+1] = NULL;
	}
	else
	{
		message[messageLength] = NULL;
	}
}

GNFORCEINLINE void GnOutputDebugString( gtchar* message )
{
#ifdef WIN32
	OutputDebugString(message);
#else // WIN32

#endif // WIN32
}

void WriteOutputDebug(gtchar* format, ...)
{
	gtchar message[gMaxDebugMessageLength] = {0,};
	va_list kArgs;
	va_start( kArgs, format );
	gsize messageLength = GnTvssprintf( message, sizeof(message), format, kArgs );
	va_end( kArgs );

#if defined(GNDEBUG) || defined(GNLOG)
	if( messageLength >= gMaxDebugMessageLength - 3 )
	{
		GnOutputDebugString( GnText( "Overed LogBuffer" ) );
	}
#endif // defined(GNDEBUG) || defined(GNLOG)

	LineCheck(message, messageLength);
	GnOutputDebugString(message);
}

GNFORCEINLINE void LineCheckA( char* message, gsize& messageLength )
{
	if (message[messageLength-1] != '\n')
	{
		message[messageLength] = '\n';
		message[messageLength+1] = NULL;
	}
	else
	{
		message[messageLength] = NULL;
	}
}

GNFORCEINLINE void GnOutputFileA( char* message )
{
	FILE *fp = NULL;
	static gchar logFileName[GN_MAX_PATH] = {0,};
	if( logFileName[0] == 0 )
	{
		GnStrcpy( logFileName, GnSystem::GetWorkDirectory(), sizeof( logFileName ) );
		GnStrcat( logFileName, "log.txt", sizeof( logFileName ) );
		fopen_s( &fp, logFileName ,"w" );
		fclose(fp);
	}
	fopen_s( &fp, logFileName, "a+" );
	fseek(fp,0,SEEK_END);
	fprintf(fp,"%s\n",message);
	fclose(fp);
}


GNFORCEINLINE void GnOutputDebugStringA( char* message )
{
#ifdef WIN32
	OutputDebugStringA(message);
#else // WIN32

#endif // WIN32
}

void WriteOutputDebugA(char* format, ...)
{
	char message[gMaxDebugMessageLength] = {0,};
	va_list kArgs;
	va_start( kArgs, format );
	gsize messageLength = GnVssprintf( message, sizeof(message), format, kArgs );
	va_end( kArgs );

#if defined(GNDEBUG) || defined(GNLOG)
	if( messageLength >= gMaxDebugMessageLength - 3 )
	{
		GnOutputDebugStringA( "Overed LogBuffer" );
	}
#endif // defined(GNDEBUG) || defined(GNLOG)

	LineCheckA(message, messageLength);
	GnOutputDebugStringA(message);
}

void WriteOutputFileA(char* format, ...)
{
	char message[gMaxDebugMessageLength] = {0,};
	va_list kArgs;
	va_start( kArgs, format );
	gsize messageLength = GnVssprintf( message, sizeof(message), format, kArgs );
	va_end( kArgs );

#if defined(GNDEBUG) || defined(GNLOG)
	if( messageLength >= gMaxDebugMessageLength - 3 )
	{
		GnOutputFileA( "Overed LogBuffer" );
	}
#endif // defined(GNDEBUG) || defined(GNLOG)

	LineCheckA(message, messageLength);
	GnOutputFileA(message);
}