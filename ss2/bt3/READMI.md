# GRAB RIDE SESSION 02 - EXERCISE 10

## 1. Phân tích bài toán

Chương trình tính cước chuyến xe GrabRide dựa trên khoảng cách di chuyển và trạng thái phụ phí thời tiết hoặc giờ cao điểm.

### Input

| Tên biến      | Kiểu dữ liệu | Ý nghĩa                           |
| ------------- | ------------ | --------------------------------- |
| `distance_km` | `double`     | Khoảng cách chuyến đi, đơn vị km  |
| `is_surge`    | `int`        | `0`: bình thường, `1`: có phụ phí |

### Output

Chương trình hiển thị:

* Khoảng cách chuyến đi.
* Cước phí cơ bản.
* Tổng cước phí sau khi áp dụng phụ phí.

Nếu dữ liệu đầu vào không hợp lệ, chương trình thông báo lỗi và dừng xử lý.

---

## 2. Quy tắc nghiệp vụ

### 2.1. Cước phí cơ bản

Nếu:

```text
distance_km <= 2.0
```

thì:

```text
base_fare = 12.000 VNĐ
```

Nếu:

```text
distance_km > 2.0
```

thì:

```text
base_fare = 12.000 + (distance_km - 2.0) * 4.500
```

Điểm biên `2.0 km` vẫn chỉ tính `12.000 VNĐ`.

### 2.2. Phụ phí Surge

Nếu:

```text
is_surge = 1
```

thì tổng tiền được nhân hệ số `1.2`.

```text
total_fare = base_fare * 1.2
```

Nếu:

```text
is_surge = 0
```

thì:

```text
total_fare = base_fare
```

---

## 3. Kiểm tra dữ liệu đầu vào

Chương trình sử dụng Guard Clause để kiểm tra dữ liệu trước khi thực hiện tính toán.

### 3.1. Khoảng cách không hợp lệ

Nếu:

```text
distance_km <= 0.0
```

chương trình báo lỗi và dừng.

### 3.2. Trạng thái Surge không hợp lệ

Chỉ chấp nhận:

```text
0 hoặc 1
```

Nếu:

```text
is_surge != 0 && is_surge != 1
```

chương trình báo lỗi và dừng.

Việc kiểm tra dữ liệu trước giúp ngăn dữ liệu không hợp lệ đi vào quá trình tính toán.

---

## 4. Giải pháp 1 - Deeply Nested IF

Giải pháp Legacy sử dụng nhiều câu lệnh `if` lồng nhau.

Ví dụ:

```c
if (distance_km > 0)
{
    if (distance_km <= 2.0)
    {
        base_fare = 12000;

        if (is_surge == 1)
        {
            total_fare = base_fare * 1.2;
        }
        else
        {
            total_fare = base_fare;
        }
    }
    else
    {
        base_fare = 12000 + (distance_km - 2.0) * 4500;

        if (is_surge == 1)
        {
            total_fare = base_fare * 1.2;
        }
        else
        {
            total_fare = base_fare;
        }
    }
}
```

### Nhược điểm

* Có nhiều tầng `if` lồng nhau.
* Khó đọc và theo dõi luồng xử lý.
* Công thức phụ phí `base_fare * 1.2` bị lặp lại.
* Khi thay đổi hệ số phụ phí phải kiểm tra nhiều nhánh.
* Khó mở rộng khi thêm nhiều quy tắc nghiệp vụ.

---

## 5. Giải pháp 2 - Guard Clauses và Step-by-Step

Giải pháp được lựa chọn gồm 3 bước chính:

### Bước 1: Kiểm tra dữ liệu

Kiểm tra khoảng cách và trạng thái Surge.

Nếu dữ liệu sai thì sử dụng `return` để dừng chương trình ngay.

### Bước 2: Tính cước cơ bản

Sau khi dữ liệu hợp lệ, chương trình tính `base_fare` dựa trên khoảng cách.

### Bước 3: Tính phụ phí

Sau khi có `base_fare`, chương trình kiểm tra `is_surge` và tính `total_fare`.

Cách này giúp tách biệt các nhiệm vụ và hạn chế việc lồng điều kiện.

---

## 6. Pseudocode

```text
BEGIN

Nhập distance_km
Nhập is_surge

IF distance_km <= 0
    In lỗi
    Dừng chương trình

IF is_surge khác 0 và 1
    In lỗi
    Dừng chương trình

IF distance_km <= 2.0
    base_fare = 12000
ELSE
    base_fare = 12000 + (distance_km - 2.0) * 4500

IF is_surge == 1
    total_fare = base_fare * 1.2
ELSE
    total_fare = base_fare

In base_fare
In total_fare

END
```

---

## 7. So sánh hai giải pháp

| Tiêu chí             | Deeply Nested IF            | Guard Clause + Step-by-Step  |
| -------------------- | --------------------------- | ---------------------------- |
| Độ phức tạp đọc hiểu | Khó khi có nhiều tầng       | Dễ đọc                       |
| Kiểm tra dữ liệu     | Lẫn với logic tính toán     | Tách riêng ở đầu             |
| Code Duplication     | Dễ bị trùng lặp             | Giảm trùng lặp               |
| Khả năng bảo trì     | Khó                         | Dễ                           |
| Thay đổi giá cước    | Có thể phải sửa nhiều nhánh | Tập trung tại phần tính cước |
| Khả năng mở rộng     | Dễ trở nên phức tạp         | Dễ thêm bước xử lý           |
| Luồng xử lý          | Nhiều nhánh lồng nhau       | Tuyến tính, rõ ràng          |

---

## 8. Lựa chọn giải pháp

Lựa chọn **Giải pháp 2 - Guard Clauses và Step-by-Step Calculation**.

Lý do:

* Dữ liệu không hợp lệ được loại bỏ ngay từ đầu.
* Giảm độ sâu của các câu lệnh `if`.
* Tách riêng kiểm tra dữ liệu và tính toán.
* Hạn chế trùng lặp công thức.
* Dễ thay đổi quy tắc tính cước.
* Dễ mở rộng khi hệ thống phát sinh thêm các quy tắc mới.

---

## 9. Test Case

| STT | `distance_km` | `is_surge` |              Kết quả |
| --: | ------------: | ---------: | -------------------: |
|   1 |           1.5 |          0 |               12.000 |
|   2 |           2.0 |          0 |               12.000 |
|   3 |           5.0 |          0 |               25.500 |
|   4 |           5.0 |          1 |               30.600 |
|   5 |          -5.0 |          0 |      Lỗi khoảng cách |
|   6 |           0.0 |          0 |      Lỗi khoảng cách |
|   7 |           5.0 |          2 | Lỗi trạng thái Surge |
|   8 |           5.0 |         -1 | Lỗi trạng thái Surge |

---

## 10. Kết luận

Chương trình sử dụng Guard Clause để kiểm tra dữ liệu đầu vào trước khi tính toán. Sau khi dữ liệu hợp lệ, chương trình thực hiện tính cước cơ bản theo khoảng cách rồi mới áp dụng phụ phí Surge.

Cách tổ chức này giúp mã nguồn dễ đọc, giảm lồng ghép điều kiện, hạn chế trùng lặp và thuận tiện hơn cho việc bảo trì.
