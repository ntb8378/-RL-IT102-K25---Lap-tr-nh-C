#include <stdio.h>

int main() {
    // ===== BIẾN ĐẦU VÀO =====
    int n;                    // Tổng số giao dịch trong ca
    int ma_mon;               // 1, 2, 3: đồ uống | 0: hủy đơn | -1: ngắt khẩn cấp
    int size;                 // 1: S, 2: M, 3: L
    int so_topping;           // Hợp lệ từ 0 đến 5
    int the_gold;             // 1: có thẻ Gold, 0: không có thẻ

    // ===== BIẾN TÍNH TOÁN =====
    int tong_tien_mon;        // Tiền của 1 giao dịch

    // ===== BIẾN ĐẦU RA (THỐNG KÊ CA) =====
    int so_gd_thanh_cong = 0; // Số giao dịch tính tiền thành công
    int so_gd_huy = 0;        // Số giao dịch khách hủy
    int so_gd_loi = 0;        // Số giao dịch lỗi dữ liệu
    long long doanh_thu = 0;  // Tổng doanh thu ca (bắt đầu = 0)
    int bi_ngat = 0;          // 1: ca bị ngắt khẩn cấp, 0: bình thường

    printf("=== HIGHLANDS POS - KIỂM TOÁN DOANH THU CA ===\n");
    printf("Nhập tổng số giao dịch: ");
    scanf("%d", &n);

    // LỖI 1: N <= 0 là số lượng ca không hợp lệ.
    // Lý do dùng return: đề yêu cầu báo lỗi và DỪNG chương trình,
    // không cần chạy vòng lặp hay in báo cáo.
    if (n <= 0) {
        printf("LỖI NGHIỆP VỤ: Tổng số giao dịch phải lớn hơn 0.\n");
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        printf("\n--- Giao dịch %d ---\n", i);
        printf("Mã món (1: Phin Sữa Đá, 2: Trà Sen Vàng, 3: Freeze, 0: Hủy, -1: Ngắt ca): ");
        scanf("%d", &ma_mon);

        // TÍN HIỆU NGẮT KHẨN CẤP (mã -1): kiểm tra ĐẦU TIÊN để phản ứng ngay.
        // Lý do dùng break: thoát hẳn khỏi vòng for, không xử lý giao dịch nào nữa.
        // LỖI 4: nếu -1 ở giao dịch đầu tiên thì chưa có tiền nào được cộng,
        // doanh thu vẫn giữ giá trị ban đầu là 0 VNĐ.
        if (ma_mon == -1) {
            printf("NGẮT KHẨN CẤP! Dừng ca tại giao dịch %d.\n", i);
            bi_ngat = 1;
            break;
        }

        // TÍN HIỆU HỦY ĐƠN (mã 0).
        // Lý do dùng continue: bỏ qua giao dịch này, sang ngay giao dịch tiếp theo.
        if (ma_mon == 0) {
            printf("Khách hủy đơn. Bỏ qua giao dịch %d.\n", i);
            so_gd_huy++;
            continue;
        }

        // Lấy giá cơ bản theo mã món.
        // Dùng if-else thay cho switch vì lệnh break trong switch
        // chỉ thoát khỏi switch, không thoát được vòng for.
        if (ma_mon == 1) {
            tong_tien_mon = 29000;
        } else if (ma_mon == 2) {
            tong_tien_mon = 39000;
        } else if (ma_mon == 3) {
            tong_tien_mon = 49000;
        } else {
            // LỖI 2: mã món rác (ví dụ 99, -5).
            // Lý do dùng continue: bỏ qua ngay, không hỏi size/topping vô ích.
            printf("CẢNH BÁO: Mã món %d không hợp lệ. Bỏ qua giao dịch %d.\n", ma_mon, i);
            so_gd_loi++;
            continue;
        }

        // --- Nhập và kiểm tra size ---
        printf("Size (1: S, 2: M, 3: L): ");
        scanf("%d", &size);

        if (size == 1) {
            tong_tien_mon = tong_tien_mon + 0;
        } else if (size == 2) {
            tong_tien_mon = tong_tien_mon + 6000;
        } else if (size == 3) {
            tong_tien_mon = tong_tien_mon + 10000;
        } else {
            // LỖI 3: size không thuộc {1, 2, 3}.
            // Lý do dùng continue: bỏ qua món này, không cộng vào doanh thu.
            printf("LỖI ORDER: Size không hợp lệ. Bỏ qua giao dịch %d.\n", i);
            so_gd_loi++;
            continue;
        }

        // --- Nhập và kiểm tra topping ---
        printf("Số topping (0-5): ");
        scanf("%d", &so_topping);

        // LỖI 3: topping < 0 hoặc > 5.
        // Lý do dùng continue: bỏ qua món này, không cộng vào doanh thu.
        if (so_topping < 0 || so_topping > 5) {
            printf("LỖI ORDER: Số topping không hợp lệ. Bỏ qua giao dịch %d.\n", i);
            so_gd_loi++;
            continue;
        }

        tong_tien_mon = tong_tien_mon + so_topping * 8000;

        // --- Nhập thẻ thành viên ---
        printf("Thẻ Gold (1: Có, 0: Không): ");
        scanf("%d", &the_gold);

        // LỖI 5: giảm 10% cho thẻ Gold.
        // Lý do nhân 90 trước rồi chia 100: toàn bộ là phép tính số nguyên
        // nên kết quả là số VNĐ chính xác, không bị lẻ số thập phân.
        if (the_gold == 1) {
            tong_tien_mon = tong_tien_mon * 90 / 100;
        }

        printf("Thành tiền: %d VNĐ\n", tong_tien_mon);

        // --- Cập nhật thống kê (chỉ giao dịch hợp lệ mới tới được đây) ---
        so_gd_thanh_cong++;
        doanh_thu = doanh_thu + tong_tien_mon;
    }

    // ===== BÁO CÁO CHỐT CA =====
    printf("\n========== BÁO CÁO KIỂM TOÁN CA ==========\n");
    if (bi_ngat == 1) {
        printf("Trạng thái: CA BỊ NGẮT KHẨN CẤP\n");
    } else {
        printf("Trạng thái: Hoàn tất ca bình thường\n");
    }
    printf("Giao dịch thành công: %d\n", so_gd_thanh_cong);
    printf("Giao dịch bị hủy: %d\n", so_gd_huy);
    printf("Giao dịch lỗi: %d\n", so_gd_loi);
    printf("Tổng doanh thu ca: %lld VNĐ\n", doanh_thu);

    return 0;
}
