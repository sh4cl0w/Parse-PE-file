
// aDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "a.h"
#include "aDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

CaDlg::CaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_A_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editpath);
	DDX_Control(pDX, IDC_BUTTON1, m_btnok);
	DDX_Control(pDX, IDC_TAB1, m_tabctrl);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Control(pDX, IDC_LIST2, m_list2);
	DDX_Control(pDX, IDC_LIST3, m_list3);
	DDX_Control(pDX, IDC_LIST4, m_list4);
	DDX_Control(pDX, IDC_LIST5, m_list5);
}

BEGIN_MESSAGE_MAP(CaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_BUTTON1, &CaDlg::OnBnClickedButton1)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CaDlg::OnTcnSelchangeTab1)
	
END_MESSAGE_MAP()

BOOL CaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_tabctrl.InsertItem(0, _T("DOS Header"));
	m_tabctrl.InsertItem(1, _T("NT Headers"));
	m_tabctrl.InsertItem(2, _T("Sections"));
	m_tabctrl.InsertItem(3, _T("Imports"));
	m_tabctrl.InsertItem(4, _T("Exports"));
	LRESULT dummy;
	OnTcnSelchangeTab1(nullptr, &dummy);

	//them cot cho cac list
	m_list1.InsertColumn(0, _T("Field"), LVCFMT_LEFT, 150);
	m_list1.InsertColumn(1, _T("Offset"), LVCFMT_LEFT, 150);
	m_list1.InsertColumn(2, _T("Value"), LVCFMT_LEFT, 150);

	m_list2.InsertColumn(0, _T("Field"), LVCFMT_LEFT, 150);
	m_list2.InsertColumn(1, _T("Offset"), LVCFMT_LEFT, 150);
	m_list2.InsertColumn(2, _T("Value"), LVCFMT_LEFT, 150);

	m_list3.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 100);
	m_list3.InsertColumn(1, _T("Virtual Size"), LVCFMT_LEFT, 150);
	m_list3.InsertColumn(2, _T("Virtual Address"), LVCFMT_LEFT, 150);
	m_list3.InsertColumn(3, _T("Size of Raw"), LVCFMT_LEFT, 150);
	m_list3.InsertColumn(4, _T("Pointer to Raw data"), LVCFMT_LEFT, 150);

	m_list4.InsertColumn(0, _T("DLL"), LVCFMT_LEFT, 150);
	m_list4.InsertColumn(1, _T("Function"), LVCFMT_LEFT, 250);

	m_list5.InsertColumn(0, _T("Ordinal"), LVCFMT_LEFT, 100);
	m_list5.InsertColumn(1, _T("Tên hàm"), LVCFMT_LEFT, 200);
	m_list5.InsertColumn(2, _T("RVA"), LVCFMT_LEFT, 150);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CaDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CaDlg::OnBnClickedButton1()
{
	CString filePath;
	m_editpath.GetWindowText(filePath);
	if (filePath.IsEmpty()) {
		AfxMessageBox(_T("Please enter a file path"));
	}
	ParsePEFile(filePath);
}


void CaDlg::ParsePEFile(const CString& filePath)
{
	HANDLE hFile = CreateFile(filePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		CString errorMsg;
		errorMsg.Format(_T("Failed to open file. Error code: %d"), GetLastError());
		AfxMessageBox(errorMsg);
		return;
	}

	DWORD fileSize = GetFileSize(hFile, NULL);
	if (fileSize == INVALID_FILE_SIZE || fileSize < sizeof(IMAGE_DOS_HEADER) + sizeof(IMAGE_NT_HEADERS)) {
		AfxMessageBox(_T("Invalid file size."));
		CloseHandle(hFile);
		return;
	}

	HANDLE hMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, fileSize, NULL);
	if (!hMapping) {
		CString errorMsg;
		errorMsg.Format(_T("Failed to create file mapping. Error code: %d"), GetLastError());
		AfxMessageBox(errorMsg);
		CloseHandle(hFile);
		return;
	}

	LPVOID lpBase = MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, fileSize);
	if (!lpBase) {
		CString errorMsg;
		errorMsg.Format(_T("Failed to map file. Error code: %d"), GetLastError());
		AfxMessageBox(errorMsg);
		CloseHandle(hMapping);
		CloseHandle(hFile);
		return;
	}

	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpBase;
	if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
		AfxMessageBox(_T("Invalid DOS Header."));
		UnmapViewOfFile(lpBase);
		CloseHandle(hMapping);
		CloseHandle(hFile);
		return;
	}

	if (pDosHeader->e_lfanew >= fileSize) {
		AfxMessageBox(_T("Invalid e_lfanew."));
		UnmapViewOfFile(lpBase);
		CloseHandle(hMapping);
		CloseHandle(hFile);
		return;
	}

	PIMAGE_NT_HEADERS32 pNt32 = (PIMAGE_NT_HEADERS32)((BYTE*)lpBase + pDosHeader->e_lfanew);
	if (pNt32->Signature != IMAGE_NT_SIGNATURE) {
		AfxMessageBox(_T("Invalid NT Headers."));
		
	}

	WORD magic = pNt32->OptionalHeader.Magic;

	if (magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC) {
		// 32-bit PE
		DisplayDOSHeader(pDosHeader);
		DisplayNTHeaders32(pNt32, lpBase);
		DisplaySectionHeaders((PIMAGE_NT_HEADERS)pNt32, lpBase); // IMAGE_FIRST_SECTION() works for both
		DisplayImportTable((PIMAGE_NT_HEADERS)pNt32, lpBase, fileSize);
		DisplayExportTable((PIMAGE_NT_HEADERS)pNt32, lpBase);
	}
	else if (magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC) {
		// 64-bit PE
		PIMAGE_NT_HEADERS64 pNt64 = (PIMAGE_NT_HEADERS64)((BYTE*)lpBase + pDosHeader->e_lfanew);
		DisplayDOSHeader(pDosHeader);
		DisplayNTHeaders64(pNt64, lpBase);
		DisplaySectionHeaders((PIMAGE_NT_HEADERS)pNt64, lpBase);
		DisplayImportTable((PIMAGE_NT_HEADERS)pNt64, lpBase, fileSize);
		DisplayExportTable((PIMAGE_NT_HEADERS)pNt64, lpBase);
	}
	else {
		AfxMessageBox(_T("Unknown PE format."));
	}
	

	/*DisplayDOSHeader(pDosHeader);
	DisplayNTHeaders(pNtHeaders, lpBase);
	DisplaySectionHeaders(pNtHeaders, lpBase);
	DisplayImportTable(pNtHeaders, lpBase,fileSize);
	
	DisplayExportTable(pNtHeaders, lpBase);*/
	
	UnmapViewOfFile(lpBase);
	CloseHandle(hMapping);
	CloseHandle(hFile);
}


void CaDlg::DisplayDOSHeader(PIMAGE_DOS_HEADER pDosHeader)
{

	m_list1.DeleteAllItems();
	CString str, offsetStr;

	// e_magic
	str.Format(_T("0x%X"), pDosHeader->e_magic);
	offsetStr.Format(_T("0x%X"), (BYTE*)&pDosHeader->e_magic - (BYTE*)pDosHeader);
	m_list1.InsertItem(0, _T("e_magic"));
	m_list1.SetItemText(0, 1, offsetStr);
	m_list1.SetItemText(0, 2, str);

	// e_lfanew
	str.Format(_T("0x%X"), pDosHeader->e_lfanew);
	offsetStr.Format(_T("0x%X"), (BYTE*)&pDosHeader->e_lfanew - (BYTE*)pDosHeader);
	m_list1.InsertItem(1, _T("e_lfanew"));
	m_list1.SetItemText(1, 1, offsetStr);
	m_list1.SetItemText(1, 2, str);

}


void CaDlg::DisplayNTHeaders32(PIMAGE_NT_HEADERS32 pNtHeaders, LPVOID lpBase)
{
	m_list2.DeleteAllItems();
	CString str, offsetStr;

	str.Format(_T("0x%X"), pNtHeaders->Signature);
	offsetStr.Format(_T("0x%X"), (BYTE*)&pNtHeaders->Signature - (BYTE*)lpBase);
	m_list2.InsertItem(0, _T("Signature"));
	m_list2.SetItemText(0, 1, offsetStr);
	m_list2.SetItemText(0, 2, str);

	str.Format(_T("0x%X"), pNtHeaders->FileHeader.Machine);
	offsetStr.Format(_T("0x%X"), (BYTE*)&pNtHeaders->FileHeader.Machine - (BYTE*)lpBase);
	m_list2.InsertItem(1, _T("Machine"));
	m_list2.SetItemText(1, 1, offsetStr);
	m_list2.SetItemText(1, 2, str);

	str.Format(_T("0x%X"), pNtHeaders->OptionalHeader.Magic);
	offsetStr.Format(_T("0x%X"), (BYTE*)&pNtHeaders->OptionalHeader.Magic - (BYTE*)lpBase);
	m_list2.InsertItem(2, _T("Magic"));
	m_list2.SetItemText(2, 1, offsetStr);
	m_list2.SetItemText(2, 2, str);

	
	str.Format(_T("%d"), pNtHeaders->FileHeader.NumberOfSections);
	offsetStr.Format(_T("0x%X"), (BYTE*)&pNtHeaders->FileHeader.NumberOfSections - (BYTE*)lpBase);
	m_list2.InsertItem(3, _T("Number of Sections"));
	m_list2.SetItemText(3, 1, offsetStr);
	m_list2.SetItemText(3, 2, str);

	
	str.Format(_T("0x%X"), pNtHeaders->FileHeader.SizeOfOptionalHeader);
	offsetStr.Format(_T("0x%X"), (BYTE*)&pNtHeaders->FileHeader.SizeOfOptionalHeader - (BYTE*)lpBase);
	m_list2.InsertItem(4, _T("Size of Optional Header"));
	m_list2.SetItemText(4, 1, offsetStr);
	m_list2.SetItemText(4, 2, str);

	
	str.Format(_T("0x%X"), pNtHeaders->FileHeader.Characteristics);
	offsetStr.Format(_T("0x%X"), (BYTE*)&pNtHeaders->FileHeader.Characteristics - (BYTE*)lpBase);
	m_list2.InsertItem(5, _T("Characteristics"));
	m_list2.SetItemText(5, 1, offsetStr);
	m_list2.SetItemText(5, 2, str);

	
	str.Format(_T("0x%X"), pNtHeaders->OptionalHeader.AddressOfEntryPoint);
	offsetStr.Format(_T("0x%X"), (BYTE*)&pNtHeaders->OptionalHeader.AddressOfEntryPoint - (BYTE*)lpBase);
	m_list2.InsertItem(6, _T("Entry Point"));
	m_list2.SetItemText(6, 1, offsetStr);
	m_list2.SetItemText(6, 2, str);

	str.Format(_T("0x%llX"), pNtHeaders->OptionalHeader.ImageBase);
	offsetStr.Format(_T("0x%X"), (BYTE*)&pNtHeaders->OptionalHeader.ImageBase - (BYTE*)lpBase);
	m_list2.InsertItem(7, _T("Image Base"));
	m_list2.SetItemText(7, 1, offsetStr);
	m_list2.SetItemText(7, 2, str);


	str.Format(_T("0x%llX"), pNtHeaders->OptionalHeader.SectionAlignment);
	offsetStr.Format(_T("0x%X"), (BYTE*)&pNtHeaders->OptionalHeader.SectionAlignment - (BYTE*)lpBase);
	m_list2.InsertItem(8, _T("Section Alignment"));
	m_list2.SetItemText(8, 1, offsetStr);
	m_list2.SetItemText(8, 2, str);


	str.Format(_T("0x%llX"), pNtHeaders->OptionalHeader.FileAlignment);
	offsetStr.Format(_T("0x%X"), (BYTE*)&pNtHeaders->OptionalHeader.FileAlignment - (BYTE*)lpBase);
	m_list2.InsertItem(9, _T("File Alignment"));
	m_list2.SetItemText(9, 1, offsetStr);
	m_list2.SetItemText(9, 2, str);
}
void CaDlg::DisplayNTHeaders64(PIMAGE_NT_HEADERS64 pNtHeaders, LPVOID lpBase)
{
	m_list2.DeleteAllItems();
	CString str, offsetStr;

	str.Format(_T("0x%X"), pNtHeaders->Signature);
	offsetStr.Format(_T("0x%X"), (BYTE*)&pNtHeaders->Signature - (BYTE*)lpBase);
	m_list2.InsertItem(0, _T("Signature"));
	m_list2.SetItemText(0, 1, offsetStr);
	m_list2.SetItemText(0, 2, str);

	str.Format(_T("0x%X"), pNtHeaders->FileHeader.Machine);
	offsetStr.Format(_T("0x%X"), (BYTE*)&pNtHeaders->FileHeader.Machine - (BYTE*)lpBase);
	m_list2.InsertItem(1, _T("Machine"));
	m_list2.SetItemText(1, 1, offsetStr);
	m_list2.SetItemText(1, 2, str);

	str.Format(_T("0x%X"), pNtHeaders->OptionalHeader.Magic);
	offsetStr.Format(_T("0x%X"), (BYTE*)&pNtHeaders->OptionalHeader.Magic - (BYTE*)lpBase);
	m_list2.InsertItem(2, _T("Magic"));
	m_list2.SetItemText(2, 1, offsetStr);
	m_list2.SetItemText(2, 2, str);

	// NumberOfSections
	str.Format(_T("%d"), pNtHeaders->FileHeader.NumberOfSections);
	offsetStr.Format(_T("0x%X"), (BYTE*)&pNtHeaders->FileHeader.NumberOfSections - (BYTE*)lpBase);
	m_list2.InsertItem(3, _T("Number of Sections"));
	m_list2.SetItemText(3, 1, offsetStr);
	m_list2.SetItemText(3, 2, str);

	// SizeOfOptionalHeader
	str.Format(_T("0x%X"), pNtHeaders->FileHeader.SizeOfOptionalHeader);
	offsetStr.Format(_T("0x%X"), (BYTE*)&pNtHeaders->FileHeader.SizeOfOptionalHeader - (BYTE*)lpBase);
	m_list2.InsertItem(4, _T("Size of Optional Header"));
	m_list2.SetItemText(4, 1, offsetStr);
	m_list2.SetItemText(4, 2, str);

	//Characteristics
	str.Format(_T("0x%X"), pNtHeaders->FileHeader.Characteristics);
	offsetStr.Format(_T("0x%X"), (BYTE*)&pNtHeaders->FileHeader.Characteristics - (BYTE*)lpBase);
	m_list2.InsertItem(5, _T("Characteristics"));
	m_list2.SetItemText(5, 1, offsetStr);
	m_list2.SetItemText(5, 2, str);

	// Entry Point
	str.Format(_T("0x%X"), pNtHeaders->OptionalHeader.AddressOfEntryPoint);
	offsetStr.Format(_T("0x%X"), (BYTE*)&pNtHeaders->OptionalHeader.AddressOfEntryPoint - (BYTE*)lpBase);
	m_list2.InsertItem(6, _T("Entry Point"));
	m_list2.SetItemText(6, 1, offsetStr);
	m_list2.SetItemText(6, 2, str);

	// Image Base
	str.Format(_T("0x%llX"), pNtHeaders->OptionalHeader.ImageBase);
	offsetStr.Format(_T("0x%X"), (BYTE*)&pNtHeaders->OptionalHeader.ImageBase - (BYTE*)lpBase);
	m_list2.InsertItem(7, _T("Image Base"));
	m_list2.SetItemText(7, 1, offsetStr);
	m_list2.SetItemText(7, 2, str);

	//SectionAlignment
	str.Format(_T("0x%llX"), pNtHeaders->OptionalHeader.SectionAlignment);
	offsetStr.Format(_T("0x%X"), (BYTE*)&pNtHeaders->OptionalHeader.SectionAlignment - (BYTE*)lpBase);
	m_list2.InsertItem(8, _T("Section Alignment"));
	m_list2.SetItemText(8, 1, offsetStr);
	m_list2.SetItemText(8, 2, str);

	//FileAlignment
	str.Format(_T("0x%llX"), pNtHeaders->OptionalHeader.FileAlignment);
	offsetStr.Format(_T("0x%X"), (BYTE*)&pNtHeaders->OptionalHeader.FileAlignment - (BYTE*)lpBase);
	m_list2.InsertItem(9, _T("File Alignment"));
	m_list2.SetItemText(9, 1, offsetStr);
	m_list2.SetItemText(9, 2, str);
}


void CaDlg::DisplaySectionHeaders(PIMAGE_NT_HEADERS pNtHeaders, LPVOID lpBase)
{
	m_list3.DeleteAllItems();

	PIMAGE_SECTION_HEADER pSectionHeader = IMAGE_FIRST_SECTION(pNtHeaders);
	CString str;

	for (int i = 0; i < pNtHeaders->FileHeader.NumberOfSections; i++) {
		m_list3.InsertItem(i, CString((char*)pSectionHeader[i].Name));

		str.Format(_T("0x%X"), pSectionHeader[i].Misc.VirtualSize);
		m_list3.SetItemText(i, 1, str);

		str.Format(_T("0x%X"), pSectionHeader[i].VirtualAddress);
		m_list3.SetItemText(i, 2, str);

		str.Format(_T("0x%X"), pSectionHeader[i].SizeOfRawData);
		m_list3.SetItemText(i, 3, str);

		str.Format(_T("0x%X"), pSectionHeader[i].PointerToRawData);
		m_list3.SetItemText(i, 4, str);
	}
}


void CaDlg::DisplayImportTable(PIMAGE_NT_HEADERS pNtHeaders, LPVOID lpBase, DWORD fileSize)
{
	m_list4.DeleteAllItems();

	BOOL isPE64 = (pNtHeaders->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC);

	// Lấy DataDirectory phù hợp
	PIMAGE_DATA_DIRECTORY pImportDir = isPE64 ?
		&((PIMAGE_NT_HEADERS64)pNtHeaders)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT] :
		&((PIMAGE_NT_HEADERS32)pNtHeaders)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];

	if (pImportDir->VirtualAddress == 0 || pImportDir->Size == 0) {
		AfxMessageBox(_T("No import table found."));
		return;
	}

	DWORD importRaw = RvaToRawOffset(pNtHeaders, pImportDir->VirtualAddress);
	if (importRaw == 0) {
		AfxMessageBox(_T("Invalid import table address."));
		return;
	}

	PIMAGE_IMPORT_DESCRIPTOR pImportDesc = (PIMAGE_IMPORT_DESCRIPTOR)((BYTE*)lpBase + importRaw);
	int itemIndex = 0;

	while (pImportDesc->Name != 0 && (BYTE*)pImportDesc < (BYTE*)lpBase + fileSize) {
		DWORD dllNameRaw = RvaToRawOffset(pNtHeaders, pImportDesc->Name);
		if (dllNameRaw == 0) break;

		LPCSTR szDllName = (LPCSTR)((BYTE*)lpBase + dllNameRaw);
		CString strDllName(szDllName);
		strDllName.MakeLower();

		ULONGLONG thunkRva = pImportDesc->OriginalFirstThunk ? pImportDesc->OriginalFirstThunk : pImportDesc->FirstThunk;
		DWORD thunkRaw = RvaToRawOffset(pNtHeaders, (DWORD)thunkRva);
		if (thunkRaw == 0) {
			pImportDesc++;
			continue;
		}

		if (isPE64) {
			PIMAGE_THUNK_DATA64 pThunk = (PIMAGE_THUNK_DATA64)((BYTE*)lpBase + thunkRaw);
			while (pThunk->u1.AddressOfData != 0 && (BYTE*)pThunk < (BYTE*)lpBase + fileSize) {
				CString strFunction, strOrdinal, strType, strRVA;

				if (pThunk->u1.Ordinal & IMAGE_ORDINAL_FLAG64) {
					
					WORD ordinal = (WORD)(pThunk->u1.Ordinal & 0xFFFF);
					strFunction.Format(_T("Ordinal: %04X"), ordinal);
					strType = _T("Ordinal");

					strRVA.Format(_T("0x%08X"), pThunk->u1.Ordinal);
				}
				else {
					DWORD nameRaw = RvaToRawOffset(pNtHeaders, (DWORD)pThunk->u1.AddressOfData);
					if (nameRaw != 0) {
						PIMAGE_IMPORT_BY_NAME pImport = (PIMAGE_IMPORT_BY_NAME)((BYTE*)lpBase + nameRaw);
						strFunction = CString(pImport->Name);
						strType = _T("Name");
						strRVA.Format(_T("0x%08llX"), pThunk->u1.AddressOfData);
					}
				}

				if (!strFunction.IsEmpty()) {
					int nIndex = m_list4.InsertItem(itemIndex, strDllName);
					m_list4.SetItemText(nIndex, 1, strFunction);
					itemIndex++;
				}
				pThunk++;
			}
		}
		else {
			PIMAGE_THUNK_DATA32 pThunk = (PIMAGE_THUNK_DATA32)((BYTE*)lpBase + thunkRaw);
			while (pThunk->u1.AddressOfData != 0 && (BYTE*)pThunk < (BYTE*)lpBase + fileSize) {
				CString strFunction, strOrdinal, strType, strRVA;

				if (pThunk->u1.Ordinal & IMAGE_ORDINAL_FLAG32) {
					// Import theo ordinal (nếu cần xử lý thêm)
					WORD ordinal = (WORD)(pThunk->u1.Ordinal & 0xFFFF);
					strFunction.Format(_T("Ordinal: %04X"), ordinal);
					strType = _T("Ordinal");

					strRVA.Format(_T("0x%08X"), pThunk->u1.Ordinal);
				}
				else {
					DWORD nameRaw = RvaToRawOffset(pNtHeaders, pThunk->u1.AddressOfData);
					if (nameRaw != 0) {
						PIMAGE_IMPORT_BY_NAME pImport = (PIMAGE_IMPORT_BY_NAME)((BYTE*)lpBase + nameRaw);
						strFunction = CString(pImport->Name);
						strType = _T("Name");
						strRVA.Format(_T("0x%08X"), pThunk->u1.AddressOfData);
					}
				}

				if (!strFunction.IsEmpty()) {
					int nIndex = m_list4.InsertItem(itemIndex, strDllName);
					m_list4.SetItemText(nIndex, 1, strFunction);
					itemIndex++;
				}
				pThunk++;
			}
		}
		pImportDesc++;
	}

	// Sắp xếp theo tên hàm
	m_list4.SortItems([](LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
		CListCtrl* pList = (CListCtrl*)lParamSort;
		CString str1 = pList->GetItemText((int)lParam1, 1);
		CString str2 = pList->GetItemText((int)lParam2, 1);
		return str1.CompareNoCase(str2);
	}, (LPARAM)&m_list4);
}


// Hàm chuyển đổi RVA sang RAW offset
DWORD CaDlg::RvaToRawOffset(PIMAGE_NT_HEADERS pNtHeaders, DWORD rva)
{
	PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION(pNtHeaders);

	for (int i = 0; i < pNtHeaders->FileHeader.NumberOfSections; i++) {
		DWORD sectionStart = pSection[i].VirtualAddress;
		DWORD sectionEnd = sectionStart + max(pSection[i].SizeOfRawData, pSection[i].Misc.VirtualSize);

		if (rva >= sectionStart && rva < sectionEnd) {
			return rva - sectionStart + pSection[i].PointerToRawData;
		}
	}

	return 0;
}
void CaDlg::DisplayExportTable(PIMAGE_NT_HEADERS pNtHeaders, LPVOID lpBase)
{
	// Xóa và tạo lại cột
	m_list5.DeleteAllItems();
	BOOL isPE64 = (pNtHeaders->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC);

	PIMAGE_DATA_DIRECTORY pExportDir = isPE64 ?
		&((PIMAGE_NT_HEADERS64)pNtHeaders)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT] :
		&((PIMAGE_NT_HEADERS32)pNtHeaders)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];

	if (pExportDir->VirtualAddress == 0 || pExportDir->Size == 0) {
		AfxMessageBox(_T("DLL không có bảng Export."));
		return;
	}

	DWORD exportRaw = RvaToRawOffset(pNtHeaders, pExportDir->VirtualAddress);
	if (exportRaw == 0) {
		AfxMessageBox(_T("Không thể chuyển đổi địa chỉ bảng Export."));
		return;
	}

	PIMAGE_EXPORT_DIRECTORY pExport = (PIMAGE_EXPORT_DIRECTORY)((BYTE*)lpBase + exportRaw);

	// Lấy tên DLL
	DWORD nameRaw = RvaToRawOffset(pNtHeaders, pExport->Name);
	if (nameRaw == 0) {
		AfxMessageBox(_T("Không đọc được tên DLL."));
		return;
	}
	LPCSTR dllName = (LPCSTR)((BYTE*)lpBase + nameRaw);
	AfxMessageBox(CString("Tên DLL: ") + CString(dllName));

	// Lấy các bảng RVA
	DWORD functionsRaw = RvaToRawOffset(pNtHeaders, pExport->AddressOfFunctions);
	DWORD namesRaw = RvaToRawOffset(pNtHeaders, pExport->AddressOfNames);
	DWORD ordinalsRaw = RvaToRawOffset(pNtHeaders, pExport->AddressOfNameOrdinals);

	if (!functionsRaw || !namesRaw || !ordinalsRaw) {
		AfxMessageBox(_T("Không thể đọc bảng Export."));
		return;
	}

	DWORD* pFunctions = (DWORD*)((BYTE*)lpBase + functionsRaw);
	DWORD* pNames = (DWORD*)((BYTE*)lpBase + namesRaw);
	WORD* pOrdinals = (WORD*)((BYTE*)lpBase + ordinalsRaw);
	

	for (DWORD i = 0; i < pExport->NumberOfNames; i++) {
		DWORD nameOffset = RvaToRawOffset(pNtHeaders, pNames[i]);
		if (nameOffset == 0) continue;

		LPCSTR funcName = (LPCSTR)((BYTE*)lpBase + nameOffset);
		WORD ordinal = pOrdinals[i];
		DWORD funcRva = pFunctions[ordinal];

		CString strOrdinal;
		strOrdinal.Format(_T("%d"), ordinal + pExport->Base);

		CString strRva;
		strRva.Format(_T("0x%08X"), funcRva);

		int nIndex = m_list5.InsertItem(i, strOrdinal);
		m_list5.SetItemText(nIndex, 1, CString(funcName));
		m_list5.SetItemText(nIndex, 2, strRva);
	}
}

void CaDlg::OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	int selectedIndex = m_tabctrl.GetCurSel();

	m_list1.ShowWindow(SW_HIDE);
	m_list2.ShowWindow(SW_HIDE);
	m_list3.ShowWindow(SW_HIDE);
	m_list4.ShowWindow(SW_HIDE);
	m_list5.ShowWindow(SW_HIDE);

	switch (selectedIndex) {
	case 0: m_list1.ShowWindow(SW_SHOW); break;
	case 1: m_list2.ShowWindow(SW_SHOW); break;
	case 2: m_list3.ShowWindow(SW_SHOW); break;
	case 3: m_list4.ShowWindow(SW_SHOW); break;
	case 4: m_list5.ShowWindow(SW_SHOW); break;
	}

	*pResult = 0;
}



