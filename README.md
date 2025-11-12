# 🧩 PE Analyzer MFC Application

---

## 🧱 Tính năng chính

- 📂 **Đọc và ánh xạ file PE** bằng API Windows (`CreateFile`, `MapViewOfFile`).
- 🧠 **Phân tích và hiển thị:**
  - `IMAGE_DOS_HEADER`
  - `IMAGE_NT_HEADERS` (hỗ trợ cả PE32 và PE64)
  - `Section Headers`
  - `Import Table`
  - `Export Table`
- 🪟 **Hiển thị dữ liệu bằng giao diện
- ⚙️ **Xử lý lỗi và xác thực định dạng PE** (magic signature, e_lfanew, RVA conversion, ...).

---


## ⚙️ Các hàm chính

### 🔹 `CaDlg::ParsePEFile(const CString& filePath)`
- Mở file PE, ánh xạ vào bộ nhớ, kiểm tra hợp lệ và gọi các hàm hiển thị.
- Tự động nhận dạng file **PE32 hoặc PE64**.

### 🔹 `DisplayDOSHeader(PIMAGE_DOS_HEADER pDosHeader)`
- Hiển thị thông tin cơ bản của DOS header (`e_magic`, `e_lfanew`).

### 🔹 `DisplayNTHeaders32/64(PIMAGE_NT_HEADERS32/64 pNtHeaders, LPVOID lpBase)`
- Hiển thị các trường của NT Header (Signature, Machine, EntryPoint, ImageBase...).

### 🔹 `DisplaySectionHeaders(PIMAGE_NT_HEADERS pNtHeaders, LPVOID lpBase)`
- Liệt kê các section `.text`, `.data`, `.rsrc`,... và thông tin chi tiết của chúng.

### 🔹 `DisplayImportTable(PIMAGE_NT_HEADERS pNtHeaders, LPVOID lpBase, DWORD fileSize)`
- Phân tích và hiển thị danh sách DLL và hàm được import.

### 🔹 `DisplayExportTable(PIMAGE_NT_HEADERS pNtHeaders, LPVOID lpBase)`
- Phân tích và hiển thị danh sách các hàm được export.

### 🔹 `RvaToRawOffset(PIMAGE_NT_HEADERS pNtHeaders, DWORD rva)`
- Chuyển đổi địa chỉ **RVA** sang **Raw File Offset**.

---

```markdown
![PE Analyzer Interface](screenshots/app.png)
