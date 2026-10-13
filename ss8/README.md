# Bài tập 01: Dò vết lỗi Pass-by-value khi cập nhật giá vé sự kiện

## 1. Phân tích lỗi

### Lỗi 1: Biến `soLuong` không được cập nhật trong `main()`

Trong hàm `datVeConcert()`, tham số `soLuong` được truyền theo cơ chế Pass-by-value, nghĩa là hàm chỉ nhận một bản sao của biến được truyền vào.

Câu lệnh `soLuong++` chỉ tăng giá trị của biến cục bộ trong hàm, không làm thay đổi biến `soLuong` trong `main()`. Vì vậy, khi gọi `hienThiDanhSachVe(dsVe, soLuong)`, chương trình vẫn nhận giá trị 0 và thông báo chưa có vé.

**Cách sửa:** Đổi kiểu trả về của `datVeConcert()` từ `void` thành `int`. Sau khi đặt vé thành công, hàm trả về số lượng mới để `main()` cập nhật bằng phép gán.

### Lỗi 2: Chưa kiểm tra giới hạn 4 vé mỗi đơn hàng

Chương trình ban đầu chỉ kiểm tra sức chứa mảng `MAX_VE`, chưa kiểm tra giới hạn `MAX_VE_PER_ORDER`.

Do đó, khách hàng có thể đặt quá 4 vé trong cùng một đơn hàng.

**Cách sửa:** Kiểm tra `soLuong >= MAX_VE_PER_ORDER` trước khi thêm vé. Nếu vượt giới hạn, thông báo lỗi và trả về số lượng hiện tại.

### Lỗi 3: Kiểm tra sức chứa mảng

Chương trình cần kiểm tra `soLuong >= MAX_VE` trước khi ghi dữ liệu vào mảng để tránh truy cập ngoài phạm vi mảng.

## 2. Bảng Test Cases

| Trường hợp kiểm thử | Dữ liệu đầu vào | Kết quả sai thực tế | Kết quả đúng mong đợi |
|---|---|---|---|
| TC01 – Kiểm tra cập nhật số lượng vé | Đặt vé 101 (VIP, 2.000.000 VND, Early Bird) và vé 102 (Zone A, 1.200.000 VND, không Early Bird). | `soLuong` trong `main()` vẫn bằng 0; giỏ hàng thông báo chưa có vé. | Giỏ hàng có 2 vé. Vé 101 có giá 1.700.000 VND; vé 102 có giá 1.200.000 VND. |
| TC02 – Kiểm tra giới hạn số lượng vé | Đặt liên tiếp 5 vé trong cùng một đơn hàng. | Hệ thống không cảnh báo giới hạn 4 vé mỗi đơn hàng. | 4 vé đầu được thêm thành công; vé thứ 5 bị từ chối. `soLuong` bằng 4 và giỏ hàng chỉ hiển thị 4 vé. |

## 3. Kết luận

Chương trình đã được sửa bằng cách sử dụng giá trị trả về của hàm để đồng bộ biến đếm `soLuong`, bổ sung kiểm tra giới hạn 4 vé mỗi đơn hàng và kiểm tra sức chứa mảng trước khi thêm vé. Quy tắc giảm giá Early Bird 15% được giữ nguyên.

## 4. Cách biên dịch và chạy

Biên dịch bằng GCC:

`gcc -std=c11 -Wall -Wextra main.c -o main`

Chạy chương trình:

`./main`

Trên Windows, có thể chạy:

`.\main.exe`
