// Group1.cpp : implementation file
//

#include "stdafx.h"
#include "Group.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////
// CCISBitmap


CCISBitmap::CCISBitmap()
{
	m_crBlack = 0;
	m_crWhite = RGB(255,255,255);
}

CCISBitmap::~CCISBitmap()
{

}

int CCISBitmap::Width()
{
	BITMAP bm;
	GetBitmap(&bm);
	return bm.bmWidth;
}

int CCISBitmap::Height()
{
	BITMAP bm;
	GetBitmap(&bm);
	return bm.bmHeight;
}

void CCISBitmap::DrawTransparent(CDC * pDC, int x, int y, COLORREF crColour)
{
	COLORREF crOldBack = pDC->SetBkColor(m_crWhite);
	COLORREF crOldText = pDC->SetTextColor(m_crBlack);
	CDC dcImage, dcTrans;

	// Create two memory dcs for the image and the mask
	dcImage.CreateCompatibleDC(pDC);
	dcTrans.CreateCompatibleDC(pDC);

	// Select the image into the appropriate dc
	CBitmap* pOldBitmapImage = dcImage.SelectObject(this);

	// Create the mask bitmap
	CBitmap bitmapTrans;
	int nWidth = Width();
	int nHeight = Height();
	bitmapTrans.CreateBitmap(nWidth, nHeight, 1, 1, NULL);

	// Select the mask bitmap into the appropriate dc
	CBitmap* pOldBitmapTrans = dcTrans.SelectObject(&bitmapTrans);

	// Build mask based on transparent colour
	dcImage.SetBkColor(crColour);
	dcTrans.BitBlt(0, 0, nWidth, nHeight, &dcImage, 0, 0, SRCCOPY);

	// Do the work - True Mask method - cool if not actual display
	pDC->BitBlt(x, y, nWidth, nHeight, &dcImage, 0, 0, SRCINVERT);
	pDC->BitBlt(x, y, nWidth, nHeight, &dcTrans, 0, 0, SRCAND);
	pDC->BitBlt(x, y, nWidth, nHeight, &dcImage, 0, 0, SRCINVERT);

	// Restore settings
	dcImage.SelectObject(pOldBitmapImage);
	dcTrans.SelectObject(pOldBitmapTrans);
	pDC->SetBkColor(crOldBack);
	pDC->SetTextColor(crOldText);
}


/////////////////////////////////////////////////////////////////////////////
// CGroup

IMPLEMENT_DYNCREATE(CGroup, CButton);

CGroup::CGroup()
{
	m_folded = false;
	m_created = false;
	m_IsAttracted = true;
	m_attract = true;
	m_userFont = false;
	m_borders = true;
	m_last = false;
	m_extendLastCtrl = false;
	m_contained = false;

	m_barColor = RGB(0,0,85);
	m_textColor = RGB(255,255,255);
	m_ctrlIndex = 0;
	m_barHeight = 25;
	m_barWidth = -1;
	
	m_toggle = NULL;
	m_bitmap = NULL;
	m_bmpMask = 0;
	m_fontSize = 12;
	
}

CGroup::~CGroup()
{
	if(m_toggle!=NULL)
		m_toggle->DestroyWindow();
	if(m_bitmap!=NULL)
		::DeleteObject(m_bitmap);
}


BEGIN_MESSAGE_MAP(CGroup, CButton)
	//{{AFX_MSG_MAP(CGroup)
	ON_WM_PAINT()
	ON_BN_CLICKED(BUTTON_TOGGLE,OnToggle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGroup message handlers

void CGroup::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	//get the group size
	GetClientRect(m_clRect);

	
	//define the different zones of the control
	if(m_bitmap!=NULL && m_resizeBar && m_barHeight<m_bitmap->Height())
	{
		m_barHeight = m_bitmap->Height()+2;
	}
	
	if(m_barWidth==-1)
	{
		m_barWidth = m_clRect.right;
	}

	if(m_contained)
	{
		m_attract = false;
		m_IsAttracted = false;
	}	


	captionRect = CRect(m_clRect.left+1,m_clRect.top,m_barWidth-1,m_barHeight-1);
	groupRect = CRect(m_clRect.left,m_clRect.top+(m_barHeight-1),m_clRect.right,m_clRect.bottom);
	buttonRect = CRect(m_barWidth-20,m_clRect.top+3,m_barWidth-3,m_clRect.top+(m_barHeight-3));
	
	//first init...
	if(!m_created)
	{
		m_created = true;

		//take reference of the controls contained within the group area
		m_parent = GetParent()->GetWindow (GW_CHILD);
		CWnd* pr = m_parent->GetParent();
		while (m_parent)
		{
			CRect m_copRect;
			GetWindowRect(m_copRect);
			CRect wRect;
			m_parent->GetWindowRect(wRect);
			if(wRect.left>m_copRect.left && wRect.right<m_copRect.right && wRect.top>m_copRect.top && wRect.bottom<m_copRect.bottom)
			{
				m_controls[m_ctrlIndex] = m_parent->GetDlgCtrlID();
				BOOL nID = m_parent->IsKindOf(RUNTIME_CLASS(CGroup));
				//if it is...
				if(nID)
				{
					//get a pointer to the CGroup object
					CGroup* cg = (CGroup*)m_parent;
					cg->m_contained = true;
				}
				m_ctrlIndex++;
			}
			m_parent = m_parent->GetWindow (GW_HWNDNEXT);
		}
	
		//set up the caption font
		if(!m_userFont)
		{
			LOGFONT lf;
			::ZeroMemory(&lf,sizeof(lf));

			lf.lfHeight = MulDiv(m_fontSize,dc.GetDeviceCaps(LOGPIXELSX),72);
			lf.lfWidth = 0;
			lf.lfEscapement = 0;
			lf.lfOrientation = 0;
			lf.lfWeight = FW_BOLD;
			lf.lfItalic = TRUE;
			lf.lfUnderline = FALSE;
			lf.lfStrikeOut = FALSE;
			lf.lfCharSet = DEFAULT_CHARSET;
			lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
			lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
			lf.lfQuality = DEFAULT_QUALITY;
			lf.lfPitchAndFamily = VARIABLE_PITCH | FF_SWISS;

			//create the font
			m_font.CreateFontIndirect(&lf);
		}
		//retrieve the control caption
		GetWindowText(m_caption);

		//create the toggle button
		if(!m_toggle)
		{
			m_toggle = new CButton;
			m_toggle->Create(_T(""),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_BITMAP,buttonRect,this,BUTTON_TOGGLE);
			m_toggle->ShowWindow(true);
			m_toggle->SetBitmap(::LoadBitmap(NULL, MAKEINTRESOURCE(32753)));
		}

		//have to be set, otherwise the control will not be redrawn if, for instance, you move the dialog window...
		SetRedraw();

	}

	//assign the font to the device context
	CFont* pOldFont = (CFont*)dc.SelectObject(&m_font);
	CBrush brush;
	brush.CreateSolidBrush(m_barColor);
	CBrush* pOldBrush = (CBrush*)dc.SelectObject(&brush);

	//draw the rectangle of the title bar
	dc.FillRect(captionRect,&brush);

	//restore
	dc.SelectObject(pOldBrush);

	//draw the group border
	if(!m_folded && m_borders)
		dc.Draw3dRect(groupRect,RGB(128,128,128),RGB(255,255,255));
	
	//draw the title bar border
	if(m_barBorders)
		dc.Draw3dRect(CRect(m_clRect.left,m_clRect.top,m_barWidth,m_barHeight),RGB(128,128,128),RGB(255,255,255));
	
	//draw the caption text
	dc.SetBkColor(m_barColor);
	dc.SetTextColor(m_textColor);

	int diffHFont = (int)(((m_barHeight-5) - m_fontSize)*0.5);

	if(m_bitmap==NULL)
	{
		dc.TextOut(m_clRect.left+(int)(m_barHeight*0.3),m_clRect.top+diffHFont,m_caption);
	}
	else
	{
		dc.TextOut(m_clRect.left+(m_bitmap->Width()+2),m_clRect.top+diffHFont,m_caption);
		m_bitmap->DrawTransparent(GetDC(), 1, 1, m_bmpMask);
	}
	dc.SelectObject(pOldBrush);

}

void CGroup::SetTextFont(LOGFONT lf)
{
	m_font.DeleteObject();
	m_font.CreateFontIndirect(&lf);
	m_userFont = true;
}

void CGroup::SetBarHeight(int h)
{
	m_barHeight = h;
	Invalidate();
}

void CGroup::SetBarWidth(int w)
{
	m_barWidth = w;
	Invalidate();
}

void CGroup::SetTextFont (CString face,int size,bool bold,bool italic,bool underline)
{
	CPaintDC dc(this);
	m_fontSize = size;

	LOGFONT lf;
	::ZeroMemory(&lf,sizeof(lf));

	lf.lfHeight = MulDiv(m_fontSize,dc.GetDeviceCaps(LOGPIXELSX),72);
	lf.lfWidth = 0;
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;
	lf.lfWeight = (bold?FW_BOLD:FALSE);
	lf.lfItalic = italic;
	lf.lfUnderline = underline;
	lf.lfStrikeOut = FALSE;
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf.lfQuality = DEFAULT_QUALITY;
	lf.lfPitchAndFamily = VARIABLE_PITCH | FF_SWISS;
	_tcscpy(lf.lfFaceName,face);

	//create the font
	SetTextFont(lf);
}

void CGroup::SetFold(bool toggle)
{
	if(!m_toggle)
	{
		buttonRect = CRect(m_clRect.right-20,m_clRect.top+3,m_clRect.right-3,m_clRect.top+(m_barHeight-3));

		m_toggle = new CButton;
		m_toggle->Create(_T("-"),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,buttonRect,this,BUTTON_TOGGLE);
		m_toggle->ShowWindow(toggle);
	}
	else
		m_toggle->ShowWindow(toggle);
	
	if(!toggle)
	{
		if(m_folded)
		{
			OnToggle();
		}
	}
}

void CGroup::SetBitmap(UINT bmpID,COLORREF mask,bool resizeBar)
{

	if (bmpID == 0)
	{
		return;
	}

	if(m_bitmap!=NULL)
	{
		m_bitmap->DeleteObject();
	}
	
	m_bitmap = new CCISBitmap;

	m_bmpMask = mask;
	m_resizeBar = resizeBar;
	m_bitmap->LoadBitmap(bmpID);
	Invalidate();
}

void CGroup::OnToggle()
{
	//change the state of the group: expanded / folded
	m_folded=!m_folded;

	//change the image of the button
	// (somehow, I couldn't pass the defines and had to put down the index ?????????)
	m_toggle->SetBitmap(::LoadBitmap(NULL, MAKEINTRESOURCE(m_folded?32752:32753)));
	
	//remove the black focus rectangle in the button
	SetFocus();
	m_toggle->SetButtonStyle(BS_PUSHBUTTON);

	//get the first child window of the main dialog (owner of the group)
	m_parent = GetParent()->GetWindow (GW_CHILD);

	//get the CWnd of the parent window (that would be the main dialog)
	CWnd* pr = m_parent->GetParent();

	//get the screen position of the group
	CRect m_copRect,wRect,rRect;
	GetWindowRect(m_copRect);
	//and get the correct client coords from the dialog
	pr->ScreenToClient(m_copRect);

	while (m_parent)
	{
		//get the screen position of the child window
		m_parent->GetWindowRect(wRect);
		//transform them into client coords from the dialog
		pr->ScreenToClient(wRect);
		rRect = wRect;

		//if the group attracts other groups and the control is not self
		if(m_attract && m_parent!=this)
		{
			//Get the vertical offset between the group and the child window we're processing
			int offset = (m_folded? -(m_clRect.Height() - m_barHeight) : m_clRect.Height() - m_barHeight);
			
			//check if the child window is another CGroup
			BOOL nID = m_parent->IsKindOf(RUNTIME_CLASS(CGroup));

			//if it is...
			if(nID)
			{
				//get a pointer to the CGroup object
				CGroup* cg = (CGroup*)m_parent;

				//if the group can be attracted by other groups
				if(cg->m_IsAttracted)
				{
					//check if the processed child window (attracted group) is below (attraction is only done upward) the group 
					if(wRect.top>m_copRect.top)
					{
						if((wRect.left>=m_copRect.left && wRect.left<=m_copRect.right) ||
						   (wRect.right>=m_copRect.left && wRect.right<=m_copRect.right))
						{
							//look for all the other window contained within the processed child window (attracted group)
							CWnd* m_search = GetParent()->GetWindow(GW_CHILD);

							//variable to store the lowest control in the processed child window (attracted group)
							int indexLowest = -1;
							int currentLow = 0;

							//retrieve the number of control contained within the processed child window (attracted group)
							int numbControls = cg->m_ctrlIndex;

							//for each control
							for(int i=0;i<numbControls;i++)
							{
								int dlgIndex = cg->m_controls[i];
								CRect eRect;
								//get the position of the control
								pr->GetDlgItem(dlgIndex)->GetWindowRect(eRect);
								//check to see if it's the lowest
								if(eRect.bottom>currentLow)
								{
									indexLowest = dlgIndex;
									currentLow = eRect.bottom;
								}
								//offset the rectangle
								eRect.OffsetRect(0,offset);
								pr->ScreenToClient(eRect);
								//and move the control...
								pr->GetDlgItem(dlgIndex)->MoveWindow(eRect);
							}

							//offset the processed child window rectangle...
							rRect.OffsetRect(0,offset);
							//if it has the last flag, change its height
							if(cg->m_last)
								rRect.bottom-=offset;
							//and move it.
							m_parent->MoveWindow(rRect);
							//if the lowest control has the extended flag
							if(cg->m_extendLastCtrl)
							{
								//change its height
								pr->GetDlgItem(indexLowest)->GetWindowRect(rRect);
								pr->ScreenToClient(rRect);
								rRect.bottom-=offset;
								pr->GetDlgItem(indexLowest)->MoveWindow(rRect);
							}
						}
					}
				}
			}
		}
		
		for(int i=0;i<m_ctrlIndex;i++)
		{
			if(m_parent->GetDlgCtrlID() == m_controls[i])
			{
				m_parent->ShowWindow(m_folded?false:true);
				break;
			}
		}
		m_parent = m_parent->GetWindow (GW_HWNDNEXT);
	}

	GetParent()->RedrawWindow();
	Invalidate();
}
