# GrabRide Fare Debug

## 1. Phân tích lỗi

### Lỗi 1: Sai công thức tính cước trên 2 km

Code cũ:
total_fare = distance * 4500.0;

Công thức đúng:
12000 + (distance - 2) * 4500

Nguyên nhân:
Chương trình tính 4500 đồng cho toàn bộ quãng đường thay vì chỉ tính
4500 đồng cho phần quãng đường vượt quá 2 km.

### Lỗi 2: Sử dụng phép gán thay vì phép so sánh

Code cũ:
if (is_raining = 1)

Code đúng:
if (is_raining == 1)

Nguyên nhân:
Dấu = là phép gán, làm is_raining luôn nhận giá trị 1.
Vì vậy điều kiện luôn đúng và phụ phí 20% luôn được áp dụng.

## 2. Test Cases

| Trường hợp kiểm thử | Dữ liệu đầu vào | Kết quả sai thực tế | Kết quả đúng mong đợi |
|---|---|---:|---:|
| Đi 2 km, trời không mưa | distance = 2, is_raining = 0 | 14.400 VND | 12.000 VND |
| Đi 3 km, trời không mưa | distance = 3, is_raining = 0 | 16.200 VND | 16.500 VND |

## 3. Kết luận

Đã sửa hai lỗi logic trong chương trình:
- Sửa công thức tính cước đối với quãng đường lớn hơn 2 km.
- Sửa phép gán = thành phép so sánh == trong điều kiện thời tiết.

Chương trình sau khi sửa xử lý đúng quy tắc tính cước của GrabRide.