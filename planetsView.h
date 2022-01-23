
// planetsView.h : interface of the CplanetsView class
//

#pragma once


class CplanetsView : public CView
{
	CWinThread* m_pCurrentThread;
	int x;
	int y;
	int x1;
	int y1;
	int j;
protected: // create from serialization only
	CplanetsView() noexcept;
	DECLARE_DYNCREATE(CplanetsView)

// Attributes
public:
	int m_iCounter;
	CplanetsDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CplanetsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnButtonStart();
	afx_msg void OnButton3Stop();
	afx_msg void OnButton4Resume();
	static UINT StartThread(LPVOID param);
};

#ifndef _DEBUG  // debug version in planetsView.cpp
inline CplanetsDoc* CplanetsView::GetDocument() const
   { return reinterpret_cast<CplanetsDoc*>(m_pDocument); }
#endif

