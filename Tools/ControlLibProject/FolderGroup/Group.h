#if !defined(AFX_GROUP1_H__A03DF69F_A1E6_4CAF_A256_F6B52B14F25E__INCLUDED_)
#define AFX_GROUP1_H__A03DF69F_A1E6_4CAF_A256_F6B52B14F25E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Group1.h : header file
//

//////////////////////////////////////////////////
//////////////////////////////////////////////////
//												//
//				D I S C L A I M E R !!!			//
//												//
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//   CGroup wrapper class						//
//	 by David Msika, 2001						//
//												//
//	If you find this piece of code useful and	//
//	you want to use it, please don't forget me	//
//	in the credits :) It's all about pride...	//
//												//
//	On the other hand, if you find any bugs,	//
//	I didn't write this code, I don't know what	//
//	you're talking about and this page will		//
//	auto-destruct your computer in 5 seconds :) //
//												//
//	Alright, maybe not, but you can still send	//
//	me bug reports at: dmsika@shiny.com			//
//												//
//	Have fun and code safe !!					//
//												//
//////////////////////////////////////////////////
//////////////////////////////////////////////////

//////////////////////////////////////////////////
//////////////////////////////////////////////////
//												//
//		The bitmap piece is the handy work		//
//		of Paul Reynolds.						//
//		Paul.Reynolds@cmgroup.co.uk				//
//												//
//////////////////////////////////////////////////
//////////////////////////////////////////////////

class CCISBitmap : public CBitmap  
{
public:
	CCISBitmap();
	virtual ~CCISBitmap();

	// Functions
	int Height();
	int Width();	
	virtual void DrawTransparent(CDC* pDC, int x, int y, COLORREF crColour);	
	
private:
	COLORREF	m_crBlack;
	COLORREF	m_crWhite;
};

/////////////////////////////////////////////////////////////////////////////
// CGroup window

#define BUTTON_TOGGLE	1

class CGroup : public CButton
{
	DECLARE_DYNCREATE(CGroup)
// Construction
public:

	bool		m_IsAttracted;		//define whether the group can be attracted by others
	bool		m_last;				//modify the height of the control when attracted
	bool		m_extendLastCtrl;	//the lowest control in the group will change its height
	bool		m_contained;		//the group is within another group
	CRect		m_clRect;			//store the group coords

	int			m_controls[100];	//remember which controls are contained within the group...
	int			m_ctrlIndex;
	
	
	CGroup();

	//return a pointer to the CGroup object...
	CGroup* GetGroupCtrl() { return this; }

	// Change the titlebar color
	void	SetBarColor(COLORREF color) { m_barColor = color; Invalidate(); }
	
	// Change the title text color
	void	SetTextColor(COLORREF color) { m_textColor = color; Invalidate(); }

	// Tells the group whether it attracts other groups or not
	void	SetAttract(bool toggle = false) { m_attract = toggle; Invalidate(); }

	//set whether the group can fold or not...
	void	SetFold(bool toggle = true);

	//add a bitmap to the title bar
	void	SetBitmap(UINT bmpID,COLORREF mask = RGB(0,0,0),bool resizeBar = false);

	// Toggle to tell whether the group can be attracted
	void	SetAttraction(bool toggle = true) { m_IsAttracted = toggle; Invalidate(); }

	// Set text font using either a LOGFONT or variables
	void	SetTextFont (LOGFONT lf);
	void	SetTextFont (CString face,int size = 12,bool bold = true,bool italic = false,bool underline = false);

	//Set the title bar height
	void	SetBarHeight(int h);

	//Set the title bar width
	void	SetBarWidth(int w);

	//Set whether the group will change its height or not when attracted
	void	SetLastGroup(bool toggle = false) {m_last = toggle; Invalidate(); }

	//Set whether the last control (bottomest) in the group will have its height modified by attraction
	void	SetLastCtrl(bool toggle = false) {m_extendLastCtrl = toggle; Invalidate(); }

	//Toggle the display of the frame for the group
	void	DrawGroupBorder(bool toggle = true) { m_borders = toggle; Invalidate(); }

	//toggle the display the frame for the title bar
	void	DrawBarBorder(bool toggle = true) { m_barBorders = toggle; Invalidate(); }

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGroup)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGroup();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGroup)
	afx_msg void OnPaint();
	afx_msg void OnToggle();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	CWnd*	m_parent; //the owner of the group
	CButton*	m_toggle;	//the button that toggles the view

	CCISBitmap*	m_bitmap;	//bitmap to add to the title bar
	COLORREF	m_bmpMask;	//transparency mask for the bitmap
	bool		m_resizeBar;	//sets whether the title bar should be readjusted	
	
	bool		m_folded;	//state of the group
	bool		m_created;	//creation state of the group
	bool		m_attract;	//if true, the group pulls or push all the other groups below
	bool		m_userFont; //user defined font
	bool		m_borders;	//group borders toggle
	bool		m_barBorders;//draw frame around titlebar
	bool		m_foldAble;	//tells whether the group has a fold button
	

	CString		m_caption;	//store the group title
	CFont		m_font;		//font for the title
	int			m_fontSize; //size of the font (height)

	COLORREF	m_barColor;	//color of the title bar
	COLORREF	m_textColor;//color og the title text
	
	int			m_barHeight;//titlebar height
	int			m_barWidth; //titlebar width

	CRect		captionRect;
	CRect		groupRect;
	CRect		buttonRect;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GROUP1_H__A03DF69F_A1E6_4CAF_A256_F6B52B14F25E__INCLUDED_)
