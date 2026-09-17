# Bài tập 03: Phân tích Trade-off - ShopeeFood Order Validator

## 1. Phân tích Input và Output

### Input

| Biến            | Kiểu dữ liệu | Ý nghĩa                       |
| --------------- | ------------ | ----------------------------- |
| `order_id`      | int          | Mã đơn hàng                   |
| `subtotal`      | int          | Giá trị tiền món ăn           |
| `distance_km`   | float        | Khoảng cách giao hàng         |
| `booking_hour`  | int          | Giờ đặt hàng từ 0 đến 23      |
| `is_store_open` | int          | Trạng thái quán: 1 mở, 0 đóng |
| `inventory_qty` | int          | Số lượng tồn kho              |

### Output

Chương trình in ra:

* Mã đơn hàng
* Giá trị tiền món ăn
* Khoảng cách giao hàng
* Giờ đặt hàng
* Trạng thái quán
* Tồn kho
* Phí giao hàng cơ bản
* Phụ phí giờ cao điểm
* Giảm phí giao hàng
* Phí giao hàng thực tế
* Trạng thái đơn hàng hợp lệ
* Tổng tiền thanh toán

---

## 2. Phân tích hai giải pháp

### Giải pháp A: Tách biệt cờ hiệu

Tạo các biến cờ có giá trị `0` hoặc `1`:

```text
is_peak_hour
is_discount_eligible
is_valid_order
```

Sau đó dùng các cờ này trong phép tính.

Ví dụ:

```text
surcharge = 10000 * is_peak_hour
discount = 15000 * is_discount_eligible
```

Nếu cờ bằng `1` thì khoản phí được áp dụng.

Nếu cờ bằng `0` thì khoản phí bằng `0`.

Đây là giải pháp được sử dụng trong chương trình.

---

### Giải pháp B: Gộp biểu thức logic

Có thể viết trực tiếp điều kiện vào công thức tính toán thay vì tạo nhiều biến trung gian.

Ví dụ:

```text
surcharge = 10000 *
((booking_hour >= 11 && booking_hour <= 13)
|| (booking_hour >= 18 && booking_hour <= 20));
```

Điều kiện hợp lệ cũng có thể gộp trực tiếp vào phép tính tổng tiền.

Ưu điểm là code ngắn hơn nhưng biểu thức dài và khó kiểm tra hơn.

---

## 3. So sánh hai giải pháp

| Tiêu chí         | Giải pháp A: Tách cờ  | Giải pháp B: Gộp biểu thức |
| ---------------- | --------------------- | -------------------------- |
| Độ đọc hiểu      | Dễ đọc                | Khó đọc hơn                |
| Khả năng bảo trì | Dễ sửa                | Khó sửa hơn                |
| Phát hiện lỗi    | Dễ kiểm tra từng cờ   | Khó xác định lỗi           |
| Bộ nhớ           | Dùng thêm một số biến | Ít biến hơn                |
| Độ rõ ràng       | Cao                   | Thấp hơn                   |

## 4. Lựa chọn giải pháp

Chọn **Giải pháp A - Tách biệt cờ hiệu**.

Lý do:

* Dễ đọc và dễ hiểu.
* Có thể kiểm tra từng điều kiện riêng.
* Dễ phát hiện lỗi khi dữ liệu đầu vào không hợp lệ.
* Dễ thay đổi khi nghiệp vụ tính phí thay đổi.
* Vẫn đáp ứng yêu cầu không sử dụng câu lệnh rẽ nhánh.

---

## 5. Công thức xử lý

### Kiểm tra giờ cao điểm

Giờ cao điểm:

```text
11 <= booking_hour <= 13
HOẶC
18 <= booking_hour <= 20
```

Biểu thức:

```text
is_peak_hour =
((booking_hour >= 11 && booking_hour <= 13)
|| (booking_hour >= 18 && booking_hour <= 20));
```

### Phụ phí

```text
surcharge = 10000 * is_peak_hour;
```

### Kiểm tra điều kiện giảm phí

```text
is_discount_eligible = (subtotal >= 100000);
```

### Giảm phí

```text
discount = 15000 * is_discount_eligible;
```

### Kiểm tra đơn hàng hợp lệ

Đơn hàng hợp lệ khi:

```text
is_store_open == 1
inventory_qty > 0
distance_km > 0
distance_km <= 15
booking_hour >= 0
booking_hour <= 23
subtotal >= 0
```

Biểu thức:

```text
is_valid_order =
(is_store_open == 1)
&& (inventory_qty > 0)
&& (distance_km > 0.0)
&& (distance_km <= 15.0)
&& (booking_hour >= 0)
&& (booking_hour <= 23)
&& (subtotal >= 0);
```

### Phí giao hàng thực tế

```text
final_delivery_fee =
(base_fee + surcharge - discount) * is_valid_order;
```

### Tổng tiền thanh toán

```text
total_payment =
(subtotal + final_delivery_fee) * is_valid_order;
```

Khi `is_valid_order = 0`, tổng tiền thanh toán sẽ bằng `0`.

---

## 6. Pseudocode

```text
Bắt đầu

Nhập order_id
Nhập subtotal
Nhập distance_km
Nhập booking_hour
Nhập is_store_open
Nhập inventory_qty

Xác định is_peak_hour
Xác định is_discount_eligible

Tính surcharge
Tính discount

Kiểm tra các điều kiện hợp lệ
Xác định is_valid_order

Tính final_delivery_fee
Tính total_payment

In phiếu đơn hàng

Kết thúc
```

---

## 7. Kiểm thử

### Trường hợp 1: Đơn hàng hợp lệ

```text
order_id = 1001
subtotal = 120000
distance_km = 5
booking_hour = 12
is_store_open = 1
inventory_qty = 10
```

Kết quả:

```text
is_peak_hour = 1
surcharge = 10000
is_discount_eligible = 1
discount = 15000
is_valid_order = 1
final_delivery_fee = 10000
total_payment = 130000
```

### Trường hợp 2: Quán đóng cửa

```text
is_store_open = 0
```

Kết quả:

```text
is_valid_order = 0
final_delivery_fee = 0
total_payment = 0
```

### Trường hợp 3: Khoảng cách vượt quá giới hạn

```text
distance_km = 20
```

Kết quả:

```text
is_valid_order = 0
final_delivery_fee = 0
total_payment = 0
```

### Trường hợp 4: Giờ đặt không hợp lệ

```text
booking_hour = -5
```

Kết quả:

```text
is_valid_order = 0
total_payment = 0
```

---

## 8. Các lỗi cần tránh

### Nhầm toán tử logic

Đúng:

```text
&&
||
!
```

Không dùng:

```text
&
|
```

### Nhầm toán tử gán và so sánh

Đúng:

```text
is_store_open == 1
```

Không viết:

```text
is_store_open = 1
```

### Kiểm tra dữ liệu biên

Khoảng cách phải:

```text
distance_km > 0
distance_km <= 15
```

Giờ đặt phải:

```text
booking_hour >= 0
booking_hour <= 23
```

Tồn kho phải:

```text
inventory_qty > 0
```

---

## 9. Kết luận

Giải pháp tách biệt các biến cờ giúp biểu diễn rõ từng quy tắc nghiệp vụ. Các cờ Boolean có giá trị `0` hoặc `1` được kết hợp với phép tính số học để bật hoặc tắt các khoản phí mà không cần sử dụng câu lệnh rẽ nhánh.

Chương trình đáp ứng các ràng buộc của bài tập và sử dụng kiến thức về biến, kiểu dữ liệu, `printf`, `scanf`, toán tử số học, toán tử so sánh và toán tử logic.
