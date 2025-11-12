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
![PE Analyzer Interface](<img width="652" height="492" alt="Screenshot 2025-11-12 145238" src="https://github.com/user-attachments/assets/44565854-cb15-42df-8b0e-af97bff78ab7" />)
