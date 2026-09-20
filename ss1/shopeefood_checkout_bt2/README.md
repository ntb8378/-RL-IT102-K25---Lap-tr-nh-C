+1

Lily: 1, 3, 6, 8, 9, 10
# Bài tập 02/07: Xây dựng Phân hệ Quyết toán Đơn hàng Đa tầng ShopeeFood bằng C

## 1. Phân tích bài toán I/O

### Input

| Biến             | Kiểu dữ liệu | Ý nghĩa                           |
| ---------------- | ------------ | --------------------------------- |
| `ma_mon`         | `int`        | Mã món ăn                         |
| `don_gia`        | `float`      | Đơn giá món ăn                    |
| `so_luong`       | `int`        | Số lượng đặt mua                  |
| `khoang_cach`    | `float`      | Khoảng cách giao hàng             |
| `gio_cao_diem`   | `int`        | Trạng thái giờ cao điểm, 1 hoặc 0 |
| `cua_hang_mo`    | `int`        | Trạng thái cửa hàng, 1 hoặc 0     |
| `ton_kho`        | `int`        | Số lượng món còn trong kho        |
| `loai_tai_khoan` | `char`       | `V` là VIP, `N` là Normal         |

### Output

* Tiền món ăn `subtotal`
* Phí giao hàng cơ bản
* Giảm giá Freeship
* Phụ phí giờ cao điểm
* Trạng thái đơn hàng hợp lệ
* Tổng thành tiền cuối cùng

---

## 2. Công thức tính toán

### Tiền món ăn

```text
Subtotal = Đơn giá × Số lượng
```

Trong C:

```c
float subtotal = don_gia * so_luong;
```

### Phí giao hàng

```text
Phí giao hàng = Khoảng cách × 5000
```

Trong C:

```c
float phi_giao_hang = khoang_cach * 5000.0;
```

### Điều kiện Freeship

Đơn hàng đạt Freeship khi:

```text
(Subtotal >= 100000 AND Khoảng cách <= 5)
OR
Tài khoản là VIP
```

Trong C:

```c
int dat_freeship = ((subtotal >= 100000.0 && khoang_cach <= 5.0)
                    || loai_tai_khoan == 'V');
```

Kết quả của biểu thức logic là `0` hoặc `1`.

Sau đó:

```text
Giảm Freeship = 15000 × dat_freeship
```

Nếu đạt Freeship thì kết quả là `15000`, nếu không đạt thì kết quả là `0`.

### Giới hạn giảm giá

Số tiền giảm không được vượt quá phí giao hàng.

Do không được sử dụng `if/else`, sử dụng giá trị `0` hoặc `1` của biểu thức logic:

```c
giam_freeship = giam_freeship * (giam_freeship <= phi_giao_hang)
               + phi_giao_hang * (giam_freeship > phi_giao_hang);
```

Nếu `giam_freeship <= phi_giao_hang` thì giữ nguyên mức giảm.

Nếu `giam_freeship > phi_giao_hang` thì mức giảm được giới hạn bằng phí giao hàng.

### Phụ phí giờ cao điểm

```text
Phụ phí = 10000 × Trạng thái giờ cao điểm
```

Trong C:

```c
float phu_phi = 10000.0 * gio_cao_diem;
```

Nếu giờ cao điểm bằng `1` thì phụ phí là `10000`.

Nếu bằng `0` thì phụ phí là `0`.

---

## 3. Kiểm tra điều kiện hợp lệ của đơn hàng

Đơn hàng hợp lệ khi đồng thời thỏa mãn:

1. Cửa hàng đang mở.
2. Tồn kho đủ số lượng đặt.
3. Số lượng đặt lớn hơn 0.
4. Đơn giá lớn hơn 0.

Biểu thức logic:

```c
int don_hang_hop_le = (cua_hang_mo == 1)
                     && (ton_kho >= so_luong)
                     && (so_luong > 0)
                     && (don_gia > 0);
```

Kết quả:

* `1`: Đơn hàng hợp lệ.
* `0`: Đơn hàng không hợp lệ.

---

## 4. Tính tổng tiền cuối cùng

Công thức:

```text
Tổng tiền =
(Subtotal + Phí giao hàng - Giảm Freeship + Phụ phí)
× Kết quả hợp lệ
```

Trong C:

```c
float tong_tien = (subtotal + phi_giao_hang - giam_freeship + phu_phi)
                 * don_hang_hop_le;
```

Nếu đơn hàng hợp lệ:

```text
don_hang_hop_le = 1
```

nên tổng tiền được giữ nguyên.

Nếu đơn hàng không hợp lệ:

```text
don_hang_hop_le = 0
```

nên:

```text
Tổng tiền × 0 = 0
```

Do đó đơn hàng không hợp lệ luôn có tổng thanh toán bằng `0 VNĐ`.

---

## 5. Xử lý lỗi bộ đệm `scanf`

Khi nhập dữ liệu kiểu `char` sau các biến số, ký tự xuống dòng `\n` có thể còn trong bộ đệm.

Vì vậy sử dụng:

```c
scanf(" %c", &loai_tai_khoan);
```

Dấu cách trước `%c` giúp bỏ qua khoảng trắng và ký tự xuống dòng trước khi đọc ký tự tài khoản.

---

## 6. Các bước xử lý

### Bước 1

Nhập thông tin món ăn, đơn giá và số lượng.

### Bước 2

Nhập khoảng cách giao hàng.

### Bước 3

Nhập trạng thái giờ cao điểm, trạng thái cửa hàng và số lượng tồn kho.

### Bước 4

Nhập loại tài khoản khách hàng.

### Bước 5

Tính tiền món ăn.

### Bước 6

Tính phí giao hàng cơ bản.

### Bước 7

Kiểm tra điều kiện Freeship bằng biểu thức logic.

### Bước 8

Tính giảm giá Freeship và giới hạn mức giảm không vượt quá phí giao hàng.

### Bước 9

Tính phụ phí giờ cao điểm.

### Bước 10

Kiểm tra tính hợp lệ của đơn hàng bằng toán tử `&&`.

### Bước 11

Nhân tổng tiền với kết quả hợp lệ `0` hoặc `1`.

### Bước 12

In thông tin hóa đơn và tổng thành tiền.

---

## 7. Ví dụ kiểm thử

### Trường hợp 1: Đơn hàng hợp lệ

Dữ liệu:

```text
Mã món: 1024
Đơn giá: 50000
Số lượng: 3
Khoảng cách: 4
Giờ cao điểm: 1
Cửa hàng mở: 1
Tồn kho: 10
Tài khoản: V
```

Tính:

```text
Subtotal = 50000 × 3 = 150000

Phí giao hàng = 4 × 5000 = 20000

Freeship = 15000

Phụ phí = 10000

Đơn hàng hợp lệ = 1

Tổng tiền = (150000 + 20000 - 15000 + 10000) × 1
          = 165000 VNĐ
```

### Trường hợp 2: Cửa hàng đóng cửa

Nếu:

```text
cua_hang_mo = 0
```

thì:

```text
don_hang_hop_le = 0
```

Do đó:

```text
Tổng tiền = Tổng tiền trước đó × 0
          = 0 VNĐ
```

### Trường hợp 3: Số lượng đặt bằng 0

Nếu:

```text
so_luong = 0
```

thì:

```text
so_luong > 0
```

có giá trị `0`.

Vì điều kiện hợp lệ sử dụng `&&`, nên:

```text
don_hang_hop_le = 0
```

và:

```text
Tổng tiền = 0 VNĐ
```

### Trường hợp 4: Đơn 20.000 VNĐ, khoảng cách 1 km, tài khoản Normal

```text
Subtotal = 20000
Khoảng cách = 1 km
Tài khoản = N
```

Điều kiện Freeship:

```text
(20000 >= 100000 && 1 <= 5) || N == V
= (0 && 1) || 0
= 0
```

Vì vậy:

```text
Giảm Freeship = 0 VNĐ
```

---

## 8. Kết luận

Chương trình sử dụng các kiểu dữ liệu cơ bản, phép tính số học, phép so sánh và phép logic để xử lý toàn bộ nghiệp vụ.

Không sử dụng:

* `if`
* `else`
* `switch`
* `for`
* `while`
* `do-while`
* Hàm tự định nghĩa
* Mảng
* `struct`

Các biểu thức logic trả về `0` hoặc `1` được sử dụng trực tiếp trong công thức để kiểm soát kết quả tính toán.

Timmy: 2, 4, 5, 7, 11, 12