#pragma once
#include <CCEGLView.h>

NS_CC_BEGIN;

class GtGLView : public CCEGLView
{
public:
	GtGLView(void);
	virtual ~GtGLView(void);

	virtual bool Create(HWND hwnd, int w, int h);
};

NS_CC_END;