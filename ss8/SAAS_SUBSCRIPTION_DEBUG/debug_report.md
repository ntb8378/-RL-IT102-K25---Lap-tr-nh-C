# Debug Report – SaaS Subscription

## 1. Lỗi phát hiện

Trong vòng lặp for, chương trình sử dụng user_list[0]
thay vì user_list[i] khi kiểm tra days_overdue và tính
total_revenue.

Lỗi:

if (user_list[0].days_overdue <= 3) {
    total_revenue += user_list[0].monthly_fee;
}

Nguyên nhân là user_list[0] luôn trỏ đến phần tử đầu tiên
của mảng. Vì vậy dù biến i thay đổi từ 0 đến 3, chương trình
vẫn luôn kiểm tra tài khoản có user_id = 1001.

## 2. Hậu quả

Tài khoản 1002 quá hạn 5 ngày và tài khoản 1004 quá hạn 4 ngày
vẫn bị đánh dấu "Hop le".

Ngoài ra, phí 180000 VND của tài khoản đầu tiên bị cộng 4 lần,
làm tổng doanh thu sai thành 720000 VND.

## 3. Cách sửa

Thay user_list[0] bằng user_list[i]:

if (user_list[i].days_overdue <= 3) {
    total_revenue += user_list[i].monthly_fee;
}

Biến i đại diện cho vị trí của tài khoản hiện tại trong mỗi
lần lặp.

## 4. Kết quả sau khi sửa

Tài khoản có days_overdue <= 3 được đánh dấu "Hop le" và
được tính doanh thu.

Tài khoản có days_overdue > 3 được đánh dấu "Qua han" và
không được tính doanh thu.

Tổng doanh thu đúng là 440000 VND.