
// MFCStudyDoc.cpp : implementation of the CMFCStudyDoc class
//

#include "stdafx.h"
#include "MFCStudy.h"

#include "MFCStudyDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCStudyDoc

IMPLEMENT_DYNCREATE(CMFCStudyDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCStudyDoc, CDocument)
END_MESSAGE_MAP()


// CMFCStudyDoc construction/destruction

CMFCStudyDoc::CMFCStudyDoc()
{
	// TODO: add one-time construction code here

}

CMFCStudyDoc::~CMFCStudyDoc()
{
}

BOOL CMFCStudyDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMFCStudyDoc serialization

void CMFCStudyDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CMFCStudyDoc diagnostics

#ifdef _DEBUG
void CMFCStudyDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCStudyDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCStudyDoc commands
