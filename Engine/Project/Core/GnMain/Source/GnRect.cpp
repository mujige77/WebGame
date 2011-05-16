#include "GnMainPCH.h"
#include "GnRect.h"

GnFRect::GnFRect() : left(0), top(0), right(0), bottom(0)
{

}

GnFRect::GnFRect(float l, float t, float r, float b) : left(l), top(t), right(r), bottom(b)
{

}

void GnFRect::LoadStream(GnStream* pStream)
{
	pStream->LoadStream( left );
	pStream->LoadStream( top );
	pStream->LoadStream( right );
	pStream->LoadStream( bottom );
}

void GnFRect::SaveStream(GnStream* pStream)
{
	pStream->SaveStream( left );
	pStream->SaveStream( top );
	pStream->SaveStream( right );
	pStream->SaveStream( bottom );
}

GnIRect::GnIRect() : left(0), top(0), right(0), bottom(0)
{

}

GnIRect::GnIRect(gint32 l, gint32 t, gint32 r, gint32 b) : left(l), top(t), right(r), bottom(b)
{

}

void GnIRect::LoadStream(GnStream* pStream)
{
	pStream->LoadStream( left );
	pStream->LoadStream( top );
	pStream->LoadStream( right );
	pStream->LoadStream( bottom );
}

void GnIRect::SaveStream(GnStream* pStream)
{
	pStream->SaveStream( left );
	pStream->SaveStream( top );
	pStream->SaveStream( right );
	pStream->SaveStream( bottom );
}