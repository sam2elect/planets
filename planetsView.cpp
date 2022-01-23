
// planetsView.cpp : implementation of the CplanetsView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "planets.h"
#endif

#include "planetsDoc.h"
#include "planetsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CplanetsView

IMPLEMENT_DYNCREATE(CplanetsView, CView)

BEGIN_MESSAGE_MAP(CplanetsView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CplanetsView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CplanetsView construction/destruction

CplanetsView::CplanetsView() noexcept
{
	// TODO: add construction code here
	m_pCurrentThread = NULL;
	x = 400;
	y = 200;
	x1 = 300 + 150 * cos(3);
	y1 = 200 + 150 * sin(3);
	m_iCounter = 0;
	j = 0;
}

CplanetsView::~CplanetsView()
{
}

BOOL CplanetsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CplanetsView drawing

void CplanetsView::OnDraw(CDC* pDC)
{
	CplanetsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	
		{
			CPen black;
			black.CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
			CPen* p02dPen = pDC->SelectObject(&black);
			pDC->Ellipse(450, 350, 150, 50); //Outer ellipse
			pDC->Ellipse(x1 + 10, y1 + 10, x1 - 10, y1 - 10);//Outer planet ellipse
			pDC->SelectObject(p02dPen);
		}
		{
			CPen red;
			red.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
			CPen* p03dPen = pDC->SelectObject(&red);
			pDC->Ellipse(400, 300, 200, 100);//Middle ellipse
			pDC->Ellipse(x + 10, y + 10, x - 10, y - 10);//inner planet ellipse
			pDC->SelectObject(p03dPen);
		}
		{
			CPen yellow;
			yellow.CreatePen(PS_SOLID, 3, RGB(255, 255, 0));
			CPen* p01dPen = pDC->SelectObject(&yellow);
			pDC->Ellipse(330, 230, 270, 170);//centre ellipse
			pDC->SelectObject(p01dPen);
		}
		for ( j; j <= 130; j=j+6 )
		{
			
			x = 300 + 100 * cos(j);
			y = 200 + 100 * sin(j);
			x1 = 300 + 150 * cos(j + 3);
			y1 = 200 + 150 * sin(j + 3);
			
				
					CPen red;
					red.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
					CPen* p03dPen = pDC->SelectObject(&red);
					pDC->Ellipse(x + 10, y + 10, x - 10, y - 10);
					pDC->SelectObject(p03dPen);
				
				
					CPen black;
					black.CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
					CPen* p02dPen = pDC->SelectObject(&black);
					pDC->Ellipse(x1 + 10, y1 + 10, x1 - 10, y1 - 10);
					pDC->SelectObject(p02dPen);
				
					Invalidate();
					Sleep(300);


		}
}


// CplanetsView printing


void CplanetsView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CplanetsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CplanetsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CplanetsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CplanetsView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CplanetsView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CplanetsView diagnostics

#ifdef _DEBUG
void CplanetsView::AssertValid() const
{
	CView::AssertValid();
}

void CplanetsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CplanetsDoc* CplanetsView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CplanetsDoc)));
	return (CplanetsDoc*)m_pDocument;
}
#endif //_DEBUG


// CplanetsView message handlers
void CplanetsView::OnButtonStart()
{
	m_pCurrentThread = AfxBeginThread(CplanetsView::StartThread, this);
	// TODO: Add your command handler code here
}


void CplanetsView::OnButton3Stop()
{
	m_pCurrentThread->SuspendThread();


	// TODO: Add your command handler code here
}


void CplanetsView::OnButton4Resume()
{
	m_pCurrentThread->ResumeThread();
	// TODO: Add your command handler code here
}


UINT CplanetsView::StartThread(LPVOID param)
{
	CplanetsView* pView = (CplanetsView*)param;
	CPoint MyPoint(0, 0);
	int j = 0;
	while (1) {
		j = j + 6;
		pView->x = 300 + 100 * cos(j);
		pView->y = 200 + 100 * sin(j);
		pView->x1 = 300 + 150 * cos(j + 3);
		pView->y1 = 200 + 150 * sin(j + 3);

		pView->Invalidate();
		Sleep(300);
	}

	// TODO: Add your implementation code here.
	return 0;
}
