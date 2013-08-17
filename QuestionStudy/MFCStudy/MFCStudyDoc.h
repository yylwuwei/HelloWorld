
// MFCStudyDoc.h : interface of the CMFCStudyDoc class
//


#pragma once


class CMFCStudyDoc : public CDocument
{
protected: // create from serialization only
	CMFCStudyDoc();
	DECLARE_DYNCREATE(CMFCStudyDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CMFCStudyDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


