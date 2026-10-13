# BÁO CÁO THIẾT KẾ MODULE QUẢN LÝ VÉ TICKETBOX

## 1. Phân tích Input/Output

### 1.1. Hàm `tinhGiaThanhToan()`

- Input: Một biến cấu trúc `VeSuKien`.
- Output: Giá vé sau khuyến mãi.
- Xử lý: Nếu `isEarlyBird == 1`, giá thanh toán bằng `giaGoc * 0.85`; ngược lại, giá thanh toán bằng giá gốc.

### 1.2. Hàm `timVeTheoMa()`

- Input: Mảng vé, số lượng vé hiện tại và mã vé cần tìm.
- Output: Trả về chỉ số của vé nếu tìm thấy; trả về `-1` nếu không tồn tại.
- Xử lý: Duyệt mảng từ vị trí `0` đến `soLuongVe - 1`.

### 1.3. Hàm `phatHanhVe()`

- Input: Mảng vé, số lượng hiện tại và thông tin vé mới.
- Output: Trả về số lượng vé mới.
- Xử lý: Kiểm tra sức chứa mảng và mã vé trùng. Nếu hợp lệ, thêm vé vào cuối mảng và tăng số lượng lên 1. Nếu thất bại, giữ nguyên số lượng.

### 1.4. Hàm `checkInQR()`

- Input: Mảng vé, số lượng hiện tại và mã vé cần check-in.
- Output: Trả về `1` nếu check-in thành công, `0` nếu thất bại.
- Xử lý: Kiểm tra danh sách rỗng, tìm mã vé, kiểm tra trạng thái check-in. Nếu vé chưa check-in, cập nhật `daCheckIn = 1`.

### 1.5. Hàm `huyVe()`

- Input: Mảng vé, số lượng hiện tại và mã vé cần hủy.
- Output: Trả về số lượng vé sau khi xử lý.
- Xử lý: Nếu tìm thấy vé, dồn các phần tử phía sau sang trái và giảm số lượng đi 1. Nếu không tìm thấy, giữ nguyên số lượng.

### 1.6. Hàm `hienThiDanhSachVe()`

- Input: Mảng vé và số lượng vé hiện tại.
- Output: In danh sách vé, giá thanh toán và trạng thái check-in.
- Xử lý: Nếu danh sách rỗng, thông báo và kết thúc hàm.

## 2. Thiết kế kiến trúc hàm

Các Function Prototypes:

- `float tinhGiaThanhToan(struct VeSuKien ve);`
- `int timVeTheoMa(const struct VeSuKien dsVe[], int soLuongVe, int maVe);`
- `int phatHanhVe(struct VeSuKien dsVe[], int soLuongVe, struct VeSuKien veMoi);`
- `int checkInQR(struct VeSuKien dsVe[], int soLuongVe, int maVe);`
- `int huyVe(struct VeSuKien dsVe[], int soLuongVe, int maVe);`
- `void hienThiDanhSachVe(const struct VeSuKien dsVe[], int soLuongVe);`

### Vai trò của hàm `timVeTheoMa()`

Đây là hàm tìm kiếm dùng chung. Hàm `checkInQR()` sử dụng kết quả để xác định vé có tồn tại trước khi cập nhật trạng thái. Hàm `huyVe()` sử dụng kết quả để xác định vị trí cần xóa.

Việc tái sử dụng hàm tìm kiếm giúp tránh viết lặp logic, giảm lỗi và giúp chương trình dễ bảo trì.

## 3. Sơ đồ xử lý nghiệp vụ

### 3.1. Luồng Check-in QR

1. Nhận mã vé từ yêu cầu check-in.
2. Kiểm tra danh sách có rỗng hay không.
3. Gọi `timVeTheoMa()` để tìm mã vé.
4. Nếu kết quả là `-1`, thông báo vé không tồn tại và từ chối.
5. Nếu vé đã có `daCheckIn == 1`, cảnh báo quét trùng và từ chối.
6. Nếu vé hợp lệ và chưa check-in, cập nhật `daCheckIn = 1`.
7. Trả về `1` khi thành công, `0` khi thất bại.

### 3.2. Luồng Hủy vé

1. Nhận mã vé cần hủy.
2. Kiểm tra danh sách rỗng.
3. Gọi `timVeTheoMa()` để tìm vị trí vé.
4. Nếu không tìm thấy, thông báo lỗi và giữ nguyên số lượng.
5. Nếu tìm thấy, dồn các vé phía sau sang trái để loại bỏ vé tại vị trí đó.
6. Giảm số lượng vé đi 1.
7. Trả về số lượng mới để `main()` cập nhật bằng phép gán.

## 4. Các trường hợp kiểm thử

- Phát hành vé mới khi danh sách chưa đầy: thêm thành công.
- Phát hành vé khi đủ 50 vé: từ chối và giữ nguyên số lượng.
- Phát hành mã vé trùng: từ chối.
- Check-in vé chưa sử dụng: thành công và cập nhật trạng thái.
- Check-in lại vé đã sử dụng: từ chối.
- Check-in mã vé không tồn tại: từ chối.
- Hủy vé tồn tại: xóa vé và giảm số lượng.
- Hủy mã vé không tồn tại: giữ nguyên số lượng.
- Check-in hoặc hủy khi danh sách rỗng: thông báo lỗi, không truy cập mảng ngoài phạm vi.

## 5. Kết luận

Chương trình được chia thành các hàm theo từng nhiệm vụ riêng biệt. Việc sử dụng `timVeTheoMa()` giúp tái sử dụng logic tìm kiếm. Các hàm phát hành và hủy vé trả về số lượng mới để `main()` đồng bộ dữ liệu. Chương trình kiểm soát sức chứa mảng, mã vé trùng, check-in lặp và thao tác trên danh sách rỗng.
