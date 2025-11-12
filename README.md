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


```markdown
![PE Analyzer Interface](https://raw.githubusercontent.com/sh4cl0w/Parse-PE-file/refs/heads/main/project/Screenshot%202025-11-12%20145238.png)?raw=true)
