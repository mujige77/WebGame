#ifndef GNOTHER_H
#define GNOTHER_H

namespace GnT
{
	struct _NullType {};
	struct _TrueType {
		enum { isTrue = true };
	};
	struct _FalseType {
		enum { isTrue = false };
	};
}


#endif // GNOTHER_H