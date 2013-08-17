
// MFCStudyView.cpp : implementation of the CMFCStudyView class
//

#include "stdafx.h"
#include "MFCStudy.h"

#include "MFCStudyDoc.h"
#include "MFCStudyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCStudyView

IMPLEMENT_DYNCREATE(CMFCStudyView, CView)

BEGIN_MESSAGE_MAP(CMFCStudyView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCStudyView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFCStudyView construction/destruction

CMFCStudyView::CMFCStudyView()
{
	// TODO: add construction code here

}

CMFCStudyView::~CMFCStudyView()
{
}

BOOL CMFCStudyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCStudyView drawing

void CMFCStudyView::OnDraw(CDC* /*pDC*/)
{
	CMFCStudyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMFCStudyView printing


void CMFCStudyView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CMFCStudyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCStudyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCStudyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMFCStudyView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCStudyView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CMFCStudyView diagnostics

#ifdef _DEBUG
void CMFCStudyView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCStudyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCStudyDoc* CMFCStudyView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCStudyDoc)));
	return (CMFCStudyDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCStudyView message handlers
