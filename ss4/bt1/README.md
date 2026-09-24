# Báo cáo sửa lỗi – Module tính tiền đơn hàng POS Coffee

## 1. Mô tả sự cố

Khi thu ngân nhập đơn hàng có N ly, hệ thống chỉ cho nhập size và tính tiền cho N − 1 ly. Ly cuối cùng bị bỏ qua nên tổng tiền hóa đơn luôn thấp hơn thực tế. Chương trình vẫn biên dịch thành công vì đây là **lỗi logic**, không phải lỗi cú pháp.

## 2. Dòng lệnh sai logic

```c
for (int i = 1; i < so_luong_ly; i++) {
```

## 3. Phân tích nguyên nhân kỹ thuật

Biến đếm `i` bắt đầu từ **1**, nhưng điều kiện dừng lại dùng toán tử **`<`** (nhỏ hơn hẳn). Hai lựa chọn này không khớp nhau:

- Với `so_luong_ly = 3`: `i` nhận các giá trị 1, 2. Khi `i = 3`, điều kiện `3 < 3` sai nên vòng lặp kết thúc → chỉ chạy **2 lần**.
- Tổng quát: vòng lặp chạy `so_luong_ly − 1` lần. Đây là lỗi kinh điển **off-by-one** (lệch một đơn vị).

Hệ quả nghiệp vụ:

- Ly cuối cùng không được hỏi size và không được cộng vào `tong_tien`, gây thất thoát doanh thu ở **mọi** đơn hàng.
- Đơn hàng chỉ có 1 ly thì vòng lặp không chạy lần nào, hóa đơn ra **0 VNĐ**.

Một vòng lặp đúng phải có số lần lặp bằng đúng `so_luong_ly`. Có hai cách viết tương đương:

| Cách viết | Giá trị của `i` | Số lần lặp |
|---|---|---|
| `for (int i = 1; i <= so_luong_ly; i++)` | 1 → so_luong_ly | so_luong_ly |
| `for (int i = 0; i < so_luong_ly; i++)` | 0 → so_luong_ly − 1 | so_luong_ly |

Bản sửa chọn cách thứ nhất (`i <= so_luong_ly`) vì giữ nguyên được dòng in `"Ly thứ %d"` hiển thị đúng số thứ tự 1, 2, 3… cho thu ngân mà không phải sửa thêm chỗ nào khác.

## 4. Nội dung sửa lỗi

```c
// Trước
for (int i = 1; i < so_luong_ly; i++) {

// Sau
for (int i = 1; i <= so_luong_ly; i++) {
```

Phần còn lại của chương trình (bảng giá, cấu trúc `if / else if`, kiểu `long long` cho tổng tiền) đã đúng nghiệp vụ nên được giữ nguyên.

## 5. Bảng Test Cases đối chứng

Bảng giá: Size S = 30.000 VNĐ, Size M = 36.000 VNĐ, Size L = 40.000 VNĐ.

| Trường hợp kiểm thử | Dữ liệu đầu vào | Kết quả sai thực tế (mã cũ) | Kết quả đúng mong đợi (mã đã sửa) |
|---|---|---|---|
| TC01 – Đơn hàng 3 ly, mỗi ly một size | Số lượng ly: `3`<br>Ly 1: `1` (S)<br>Ly 2: `2` (M)<br>Ly 3: `3` (L) | Chỉ hỏi size 2 ly, ly 3 bị bỏ qua.<br>Tổng: **66000 VNĐ** (30.000 + 36.000) | Hỏi đủ 3 ly.<br>Tổng: **106000 VNĐ** (30.000 + 36.000 + 40.000) |
| TC02 – Đơn hàng 1 ly (biên dưới) | Số lượng ly: `1`<br>Ly 1: `3` (L) | Không hỏi size ly nào.<br>Tổng: **0 VNĐ** | Hỏi size 1 ly.<br>Tổng: **40000 VNĐ** |

## 6. Biên dịch và chạy

```bash
gcc main.c -o pos_order
./pos_order
```
