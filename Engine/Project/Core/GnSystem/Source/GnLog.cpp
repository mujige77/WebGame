#include "GnSystemPCH.h"
#include "GnLog.h"

const gtuint gMaxDebugMessageLength = 256;

static GNFORCEINLINE void LineCheck(gtchar* message, gsize& messageLength)
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

static GNFORCEINLINE void GnOutputDebugString(const gtchar* message)
{
#ifdef WIN32
	OutputDebugString( message );
#else // WIN32
	GnTPrintf( GnText("%s") , message );
#endif // WIN32
}

void WriteOutputDebug(const gtchar* format, ...)
{
	gtchar message[gMaxDebugMessageLength] = {0,};
	va_list kArgs;
	va_start( kArgs, format );
#ifdef WIN32
	gsize messageLength = GnTvssprintf( message, sizeof(message), format, kArgs );
#else // WIN32
    gsize messageLength = GnTvssprintf( message, format, kArgs );
#endif // WIN32
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

static GNFORCEINLINE void LineCheckA(char* message, gsize& messageLength)
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

static GNFORCEINLINE void GnOutputFileA(const gchar* message)
{
	FILE *fp = NULL;
	static gchar logFileName[GN_MAX_PATH] = {0,};
	if( logFileName[0] == 0 )
	{
		GnStrcpy( logFileName, GnSystem::GetWorkDirectory(), sizeof( logFileName ) );
		GnStrcat( logFileName, "log.txt", sizeof( logFileName ) );
#ifdef WIN32
		fopen_s( &fp, logFileName ,"w" );
#else // WIN32
        fp = fopen( logFileName ,"w" );
#endif // WIN32
		fclose(fp);
	}
#ifdef WIN32
   	fopen_s( &fp, logFileName, "a+" );
#else // WIN32
    fp = fopen( logFileName, "a+" );
#endif // WIN32

	fseek(fp,0,SEEK_END);
	fprintf(fp,"%s\n",message);
	fclose(fp);
}


static GNFORCEINLINE void GnOutputDebugStringA(const gchar* message)
{
#ifdef WIN32
	OutputDebugStringA( message );
#else // WIN32
    printf( "%s", message );
#endif // WIN32
}

void WriteOutputDebugA(const gchar* format, ...)
{
	char message[gMaxDebugMessageLength] = {0,};
	va_list kArgs;
	va_start( kArgs, format );
#ifdef WIN32
	gsize messageLength = GnVssprintf( message, sizeof(message), format, kArgs );
#else // WIN32
    gsize messageLength = GnVssprintf( message, format, kArgs );
#endif // WIN32
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

void WriteOutputFileA(const gchar* format, ...)
{
	char message[gMaxDebugMessageLength] = {0,};
	va_list kArgs;
	va_start( kArgs, format );
#ifdef WIN32
	gsize messageLength = GnVssprintf( message, sizeof(message), format, kArgs );
#else // WIN32
    gsize messageLength = GnVssprintf( message, format, kArgs );
#endif // WIN32
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