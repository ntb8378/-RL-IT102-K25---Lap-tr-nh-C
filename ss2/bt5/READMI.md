# BÀI TẬP 05: TỔNG HỢP THỰC HÀNH DEMO XÂY DỰNG HỆ THỐNG TÍNH CƯỚC GRAB

## 1. Phân tích dữ liệu đầu vào và đầu ra

### Dữ liệu đầu vào

Chương trình nhận 2 dữ liệu:

* `distance`: kiểu `float`, biểu diễn quãng đường di chuyển tính bằng km.
* `has_promo`: kiểu `int`, biểu diễn trạng thái mã giảm giá:

  * `0`: không áp dụng mã giảm giá.
  * `1`: có áp dụng mã giảm giá 20%.

### Dữ liệu đầu ra

Nếu dữ liệu không hợp lệ:

```text
Loi: Du lieu dau vao khong hop le!
```

Nếu dữ liệu hợp lệ:

```text
Tong cuoc phi: [So tien] VNĐ
```

---

## 2. Phân tích điều kiện dữ liệu

Dữ liệu không hợp lệ trong hai trường hợp:

### Trường hợp 1: Khoảng cách không hợp lệ

```text
distance <= 0
```

Khi đó chương trình thông báo lỗi và dừng.

### Trường hợp 2: Trạng thái mã giảm giá không hợp lệ

`has_promo` chỉ được nhận giá trị `0` hoặc `1`.

Điều kiện kiểm tra:

```text
has_promo != 0 && has_promo != 1
```

Nếu điều kiện đúng thì dữ liệu không hợp lệ.

---

## 3. Công thức tính cước

Giá cước tiêu chuẩn:

```text
20.000 VNĐ/km
```

Cước gốc:

```text
base_fare = distance × 20.000
```

Nếu không có mã giảm giá:

```text
total_fare = base_fare
```

Nếu có mã giảm giá:

```text
total_fare = base_fare × 0.8
```

Sau khi giảm giá, nếu tổng cước nhỏ hơn mức sàn 15.000 VNĐ:

```text
total_fare = 15.000
```

---

## 4. Luồng xử lý

```text
Nhập distance và has_promo
          ↓
Kiểm tra distance <= 0 ?
          ↓
       Có → Báo lỗi và dừng
          ↓ Không
Kiểm tra has_promo khác 0 và 1 ?
          ↓
       Có → Báo lỗi và dừng
          ↓ Không
Tính cước gốc = distance × 20.000
          ↓
Có mã giảm giá?
     ↙             ↘
   Có               Không
   ↓                  ↓
Giảm 20%          Giữ nguyên
     ↘             ↙
      Kiểm tra cước sàn
             ↓
Nếu < 15.000 → 15.000
             ↓
       Xuất tổng cước
```

---

## 5. Mã nguồn `main.c`

```c
#include <stdio.h>

int main(void)
{
    float distance;
    int has_promo;
    float base_fare;
    float total_fare;

    printf("Nhap quang duong (km): ");
    scanf("%f", &distance);

    printf("Nhap trang thai ma giam gia (0-Khong, 1-Co): ");
    scanf("%d", &has_promo);

    // Kiem tra du lieu dau vao
    if (distance <= 0)
    {
        printf("Loi: Du lieu dau vao khong hop le!\n");
        return 0;
    }

    if (has_promo != 0 && has_promo != 1)
    {
        printf("Loi: Du lieu dau vao khong hop le!\n");
        return 0;
    }

    // Tinh cuoc goc
    base_fare = distance * 20000;

    // Ap dung ma giam gia
    if (has_promo == 1)
    {
        total_fare = base_fare * 0.8;
    }
    else
    {
        total_fare = base_fare;
    }

    // Kiem tra muc cuoc san
    if (total_fare < 15000)
    {
        total_fare = 15000;
    }

    printf("Tong cuoc phi: %.2f VNĐ\n", total_fare);

    return 0;
}
```

---

## 6. Kiểm thử chương trình

### Trường hợp 1: Không giảm giá

Input:

```text
distance = 5.0
has_promo = 0
```

Tính:

```text
5 × 20.000 = 100.000
```

Output:

```text
Tong cuoc phi: 100000.00 VNĐ
```

---

### Trường hợp 2: Có giảm giá

Input:

```text
distance = 10.0
has_promo = 1
```

Tính:

```text
10 × 20.000 = 200.000
200.000 × 80% = 160.000
```

Output:

```text
Tong cuoc phi: 160000.00 VNĐ
```

---

### Trường hợp 3: Áp dụng cước sàn

Input:

```text
distance = 0.8
has_promo = 1
```

Tính:

```text
0.8 × 20.000 = 16.000
16.000 × 80% = 12.800
```

Do:

```text
12.800 < 15.000
```

nên áp dụng cước sàn:

```text
15.000
```

Output:

```text
Tong cuoc phi: 15000.00 VNĐ
```

---

### Trường hợp 4: Khoảng cách không hợp lệ

Input:

```text
distance = -2.5
has_promo = 0
```

Do:

```text
distance <= 0
```

nên chương trình dừng và xuất:

```text
Loi: Du lieu dau vao khong hop le!
```

---

### Trường hợp 5: Mã giảm giá không hợp lệ

Input:

```text
distance = 3.0
has_promo = 5
```

Do `has_promo` chỉ được phép là `0` hoặc `1`, chương trình xuất:

```text
Loi: Du lieu dau vao khong hop le!
```

---

## 7. Bảng kiểm thử

| Case | Distance | Has Promo |       Kết quả |
| ---- | -------: | --------: | ------------: |
| 1    |      5.0 |         0 | 100000.00 VNĐ |
| 2    |     10.0 |         1 | 160000.00 VNĐ |
| 3    |      0.8 |         1 |  15000.00 VNĐ |
| 4    |     -2.5 |         0 |       Báo lỗi |
| 5    |      3.0 |         5 |       Báo lỗi |

---

## 8. Clean Code

Chương trình sử dụng các tên biến có ý nghĩa:

* `distance`: khoảng cách.
* `has_promo`: trạng thái mã giảm giá.
* `base_fare`: cước gốc.
* `total_fare`: tổng cước sau xử lý.

Chương trình tách riêng:

1. Nhập dữ liệu.
2. Kiểm tra dữ liệu.
3. Tính cước gốc.
4. Áp dụng giảm giá.
5. Kiểm tra cước sàn.
6. Xuất kết quả.

Việc kiểm tra dữ liệu được thực hiện trước khi tính toán nhằm tránh xử lý dữ liệu không hợp lệ.

## 9. Kết luận

Chương trình đã áp dụng cấu trúc `if` và `else` để xử lý bài toán tính cước GrabRide. Chương trình kiểm tra dữ liệu đầu vào trước khi tính toán, áp dụng mã giảm giá 20% khi hợp lệ và đảm bảo tổng cước sau giảm không thấp hơn mức cước sàn 15.000 VNĐ.
