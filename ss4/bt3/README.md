# Highlands POS – Tái cấu trúc hệ thống kiểm toán doanh thu ca

## 1. Phân tích điểm yếu của mã cũ

Mã cũ viết theo kiểu điều kiện lồng nhau nhiều tầng (Deeply Nested Logic), nên có các điểm yếu sau:

- **Khó đọc, khó sửa.** Phần tính tiền nằm ở tầng trong cùng. Mỗi `else` báo lỗi nằm cách xa `if` của nó, phải dò từng cặp ngoặc mới biết lỗi đó thuộc điều kiện nào.
- **Không ngắt khẩn cấp được ngay.** Khi không dùng `break`, gặp mã `-1` chỉ có thể bật một biến cờ. Chương trình vẫn chạy nốt phần còn lại của vòng lặp hiện tại rồi mới dừng.
- **Dễ tính sai giảm giá.** Công thức tính tiền dễ bị viết lặp ở nhiều nhánh. Sửa nhánh này mà quên nhánh kia thì khách Gold và khách thường bị tính theo hai cách khác nhau.
- **Xử lý thừa với dữ liệu rác.** Đơn hủy hoặc mã rác vẫn phải đi qua nhiều tầng `if-else` mới bị loại.

## 2. Phân tích Input / Output

### Biến đầu vào

| Tên biến | Kiểu dữ liệu | Ý nghĩa nghiệp vụ | Giá trị hợp lệ |
|---|---|---|---|
| `n` | `int` | Tổng số giao dịch trong ca | `n > 0` |
| `ma_mon` | `int` | Mã đồ uống hoặc tín hiệu điều khiển | `1` Phin Sữa Đá, `2` Trà Sen Vàng, `3` Freeze; `0` hủy đơn; `-1` ngắt ca |
| `size` | `int` | Kích thước ly | `1` S, `2` M, `3` L |
| `so_topping` | `int` | Số topping gọi thêm | Từ `0` đến `5` |
| `the_gold` | `int` | Thẻ thành viên Vàng | `1` có thẻ, `0` không có |

### Biến tính toán

| Tên biến | Kiểu dữ liệu | Ý nghĩa |
|---|---|---|
| `tong_tien_mon` | `int` | Tiền của 1 giao dịch = giá cơ bản + phụ thu size + topping × 8.000, sau đó giảm 10% nếu có thẻ Gold |

### Biến đầu ra

| Tên biến | Kiểu dữ liệu | Ý nghĩa |
|---|---|---|
| `so_gd_thanh_cong` | `int` | Số giao dịch tính tiền thành công |
| `so_gd_huy` | `int` | Số giao dịch khách hủy (mã `0`) |
| `so_gd_loi` | `int` | Số giao dịch bị bỏ qua do lỗi dữ liệu |
| `doanh_thu` | `long long` | Tổng doanh thu thực tế trong ca (VNĐ) |
| `bi_ngat` | `int` | `1` nếu ca bị ngắt khẩn cấp, `0` nếu bình thường |

## 3. Đề xuất 2 giải pháp

### Giải pháp 1 – Cấu trúc lồng ghép (Nested if-else)

Giữ cách kiểm tra điều kiện lồng nhau. Mỗi điều kiện đúng lại mở thêm một tầng `if`, chỉ tính tiền ở tầng trong cùng khi mọi điều kiện đều đúng. Không dùng `continue`/`break`, nên muốn ngắt ca phải dùng biến cờ và đưa cờ vào điều kiện của vòng `for`.

```c
for (int i = 1; i <= n && dung_ca == 0; i++) {
    scanf("%d", &ma_mon);
    if (ma_mon == -1) {
        dung_ca = 1;
    } else {
        if (ma_mon != 0) {
            if (ma_mon >= 1 && ma_mon <= 3) {
                scanf("%d", &size);
                if (size >= 1 && size <= 3) {
                    scanf("%d", &so_topping);
                    if (so_topping >= 0 && so_topping <= 5) {
                        scanf("%d", &the_gold);
                        /* tính tiền */
                    } else {
                        /* lỗi topping */
                    }
                } else {
                    /* lỗi size */
                }
            } else {
                /* mã rác */
            }
        } else {
            /* hủy đơn */
        }
    }
}
```

### Giải pháp 2 – Loại bỏ sớm (Guard Clauses)

Kiểm tra từng lỗi riêng lẻ ngay khi nhập, gặp lỗi thì thoát sớm:

- Mã `-1` → `break`: thoát hẳn vòng lặp, ngắt ca ngay.
- Mã `0`, mã rác, size sai, topping sai → `continue`: bỏ qua giao dịch, sang giao dịch tiếp theo.
- Phần tính tiền nằm phẳng ở cuối vòng lặp. Chỉ giao dịch vượt qua mọi điều kiện mới tới được đây.

```c
for (int i = 1; i <= n; i++) {
    scanf("%d", &ma_mon);
    if (ma_mon == -1) break;              /* ngắt ca */
    if (ma_mon == 0) continue;            /* hủy đơn */
    if (mã món rác) continue;
    scanf("%d", &size);
    if (size sai) continue;
    scanf("%d", &so_topping);
    if (topping sai) continue;
    scanf("%d", &the_gold);
    /* tính tiền */
}
```

## 4. So sánh và lựa chọn

| Tiêu chí | Giải pháp 1 – Nested if-else | Giải pháp 2 – Guard Clauses |
|---|---|---|
| Số tầng lồng logic (Nesting Depth) | 6–7 tầng | 2 tầng (`for` + `if`) |
| Độ phức tạp duy trì (Maintainability) | Khó: `else` báo lỗi nằm cách xa `if` của nó, phải dò cặp ngoặc | Dễ: mỗi lỗi và thông báo của nó nằm liền nhau, đọc từ trên xuống |
| Tốc độ loại bỏ dữ liệu rác | Chậm hơn: dữ liệu sai phải đi qua các tầng `else`; tín hiệu ngắt chỉ bật cờ, phải chạy nốt vòng hiện tại | Nhanh: `continue` / `break` thoát ngay tại dòng phát hiện lỗi, không hỏi thêm dữ liệu thừa |
| Khả năng mở rộng nghiệp vụ mới | Thêm quy tắc phải chèn thêm một tầng vào giữa, dễ đặt sai `else` | Chỉ cần thêm một khối `if ... continue;` độc lập |

### Lựa chọn: Giải pháp 2

Cả hai giải pháp đều duyệt qua N giao dịch, nhưng Giải pháp 2 tốt hơn ở mọi tiêu chí:

- Ngắt ca **ngay lập tức** khi gặp mã `-1`, đúng yêu cầu an ninh.
- Loại đơn hủy và đơn rác sớm, không bắt thu ngân nhập thêm dữ liệu thừa.
- Mã nguồn phẳng, dễ đọc, dễ thêm quy tắc mới.
- Công thức tính tiền chỉ viết một lần nên không bị tính lệch giảm giá giữa các nhánh.

**Lưu ý:** đề cho phép dùng `switch-case`, nhưng bài làm dùng `if-else`. Lý do là lệnh `break` bên trong `switch` chỉ thoát khỏi `switch`, không thoát khỏi vòng `for`, nên tín hiệu `-1` sẽ không dừng được ca.

## 5. Mã giả (Pseudocode) cho Giải pháp 2

```
BẮT ĐẦU
  Gán so_gd_thanh_cong = 0, so_gd_huy = 0, so_gd_loi = 0, doanh_thu = 0, bi_ngat = 0
  Nhập n
  NẾU n <= 0:
      In "Lỗi nghiệp vụ", KẾT THÚC chương trình
  LẶP i từ 1 đến n:
      Nhập ma_mon
      NẾU ma_mon = -1:
          bi_ngat = 1, THOÁT VÒNG LẶP (break)
      NẾU ma_mon = 0:
          so_gd_huy tăng 1, SANG VÒNG SAU (continue)
      NẾU ma_mon = 1: tong_tien_mon = 29000
      NẾU ma_mon = 2: tong_tien_mon = 39000
      NẾU ma_mon = 3: tong_tien_mon = 49000
      NGƯỢC LẠI:
          Cảnh báo mã rác, so_gd_loi tăng 1, SANG VÒNG SAU
      Nhập size
      NẾU size = 1: cộng 0
      NẾU size = 2: cộng 6000
      NẾU size = 3: cộng 10000
      NGƯỢC LẠI:
          Báo lỗi size, so_gd_loi tăng 1, SANG VÒNG SAU
      Nhập so_topping
      NẾU so_topping < 0 HOẶC so_topping > 5:
          Báo lỗi topping, so_gd_loi tăng 1, SANG VÒNG SAU
      tong_tien_mon = tong_tien_mon + so_topping × 8000
      Nhập the_gold
      NẾU the_gold = 1:
          tong_tien_mon = tong_tien_mon × 90 / 100
      so_gd_thanh_cong tăng 1
      doanh_thu = doanh_thu + tong_tien_mon
  HẾT LẶP
  In báo cáo: trạng thái ca, số giao dịch thành công, bị hủy, lỗi, tổng doanh thu
KẾT THÚC
```

## 6. Xử lý các lỗi thường gặp

| Lỗi | Cách xử lý trong `main.c` |
|---|---|
| Lỗi 1 – `N <= 0` | In lỗi nghiệp vụ và `return 0` để dừng chương trình |
| Lỗi 2 – Mã món rác (99, -5, …) | Nhánh `else` cuối chuỗi tra giá: cảnh báo và `continue` |
| Lỗi 3 – Size ngoài `{1, 2, 3}` hoặc topping `< 0` hay `> 5` | Báo lỗi order và `continue`, không cộng doanh thu |
| Lỗi 4 – Mã `-1` ở giao dịch đầu tiên | `break` ngay; `doanh_thu` vẫn là giá trị ban đầu `0` |
| Lỗi 5 – Làm tròn giảm giá | Tính `tong_tien_mon * 90 / 100` bằng số nguyên, không dùng số thực |

## 7. Kết quả chạy thử

| Kịch bản | Dữ liệu vào (`mã size topping thẻ`) | Doanh thu ca |
|---|---|---|
| Ca bình thường | N = 3: `1 2 1 1`, `3 3 0 0`, `3 1 5 1` | 177.800 VNĐ |
| Có đơn hủy | N = 3: `1 1 0 0`, `0`, `2 2 2 0` | 90.000 VNĐ |
| Có mã rác | N = 3: `99`, `-5`, `3 3 1 1` | 60.300 VNĐ |
| Size / topping sai | N = 3: `1 4`, `2 1 6`, `3 2 -1` | 0 VNĐ (3 giao dịch lỗi) |
| Ngắt giữa ca | N = 4: `1 1 0 0`, `-1`, … | 29.000 VNĐ |
| Ngắt ở giao dịch đầu | N = 3: `-1`, … | 0 VNĐ |
| N không hợp lệ | N = 0 | Báo lỗi nghiệp vụ, dừng chương trình |
