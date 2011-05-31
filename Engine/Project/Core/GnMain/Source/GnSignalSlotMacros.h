#ifndef GNSIGNALSLOTMACROS_H
#define GNSIGNALSLOTMACROS_H


#define GnUnsubscribeFromAll(GnTSetName)                    \
    {                                                       \
        unsigned int uiSize;                                \
        uiSize = GnTSetName.GetSize();                      \
        while (uiSize != 0)                                 \
        {                                                   \
            GnTSetName.GetAt(0)->Unsubscribe(this);         \
            uiSize = GnTSetName.GetSize();                  \
        }                                                   \
    }

#define GnSubscribeToMe(GnTSetName, Element)                \
    {                                                       \
        int iIsThere = GnTSetName.Find(Element);            \
        if (iIsThere == -1)                                 \
        {                                                   \
            GnTSetName.Add(Element);                        \
            Element->Subscribe(this);                        \
        }                                                   \
    }

#define GnUnsubscribeToMe(GnTSetName, Element)              \
    {                                                       \
        int iIsThere = GnTSetName.Find(Element);            \
        if (iIsThere != -1)                                 \
        {                                                   \
            GnTSetName.RemoveAt(iIsThere);                  \
            Element->Unsubscribe(this);                      \
        }                                                   \
    }

// ArgList is actually a parenthesized list of arguments.
#define GnEmitSignalToAll(GnTSetName, ArgList)              \
    {                                                       \
        unsigned int uiIdx, uiSize;                         \
        uiSize = GnTSetName.GetSize();                      \
        for (uiIdx = 0; uiIdx < uiSize; ++uiIdx)            \
        {                                                   \
            GnTSetName.GetAt(uiIdx)->ReceiveSignal ArgList; \
        }                                                   \
    }

// Although these macros are very short, they were created so that if the
// system were to change in the future to use GnTArray or some other storage
// type, the only changes necessary would be in the declaration in the .h
// files and in this macro file.
#define GnNumElements(GnTSetName)                           \
    GnTSetName.GetSize();

#define GnIsElementInGroup(GnTSetName, Element)             \
    (GnTSetName.Find(Element) != -1);


#endif // GNSIGNALSLOTMACROS_H
