#ifndef GNLISTMANAGER_H
#define GNLISTMANAGER_H
#include "GnList.h"

template<class TListType, class TListSmartPointer>
class GnListManager : public GnSmartObject
{
protected:
	GnList<TListSmartPointer> mList;	
	typedef GnListIterator<TListSmartPointer> ElementIterator;
	typedef TListType ElementType;

public:
	GnListManager(){};
	virtual ~GnListManager()
	{
		RemoveAll();
	};
	inline void Append(TListType* val)
	{
		mList.Append(val);
	}
	inline void Prepend(TListType* val)
	{
		mList.Prepend(val);
	}
	inline void Remove(TListType* val)
	{
		GnListRemove(mList, val);
	}
	inline void RemoveAll()
	{
		mList.RemoveAll();
	}
	inline GnList<TListSmartPointer>& GetList()
	{
		return mList;
	}
	inline const GnList<TListSmartPointer>& GetList() const
	{
		return mList;
	}
};

#endif // GNLISTMANAGER_H