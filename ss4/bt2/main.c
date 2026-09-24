#include <stdio.h>

int main() {
    // ===== BIẾN ĐẦU VÀO =====
    int n;                    // Số hóa đơn trong ca
    int gia_co_so;            // Giá niêm yết Size S (VNĐ)
    char size;                // Ký tự size: S, M, L (chữ hoa hoặc chữ thường)
    int so_topping;           // Số topping gọi thêm
    int hoi_vien;             // 1: Hội viên Vàng, 0: Khách thường

    // ===== BIẾN TÍNH TOÁN =====
    int phu_thu_size;         // Tiền phụ thu theo size
    int tien_hoa_don;         // Tiền của 1 hóa đơn

    // ===== BIẾN ĐẦU RA (THỐNG KÊ CA) =====
    int so_don_hop_le = 0;    // Số đơn thanh toán thành công
    int so_don_loi = 0;       // Số đơn bị hủy / lỗi dữ liệu
    long long doanh_thu = 0;  // Tổng doanh thu ca
    int don_lon_nhat = 0;     // Giá trị đơn lớn nhất
    int bi_ngat = 0;          // 1: ca bị ngắt khẩn cấp, 0: bình thường

    // LỖI 3: Tất cả biến thống kê đều gán = 0 ngay từ đầu.
    // Lý do: nếu ca trống hoặc toàn đơn rác thì không có đơn nào được cộng,
    // doanh thu và đơn lớn nhất vẫn giữ nguyên 0 VNĐ đúng yêu cầu.

    printf("=== CHỐT SỔ DOANH THU CA ===\n");
    printf("Nhập số hóa đơn trong ca: ");
    scanf("%d", &n);

    // LỖI 3: Ca làm việc trống (N <= 0).
    // Lý do: với N <= 0 thì điều kiện i <= n của vòng for sai ngay từ đầu,
    // vòng lặp không chạy lần nào nên chương trình không bị lỗi,
    // chỉ cần thông báo cho thu ngân rồi in báo cáo toàn số 0.
    if (n <= 0) {
        printf("Ca làm việc không có hóa đơn nào.\n");
    }

    for (int i = 1; i <= n; i++) {
        printf("\n--- Hóa đơn %d ---\n", i);

        // --- Nhập và kiểm tra giá cơ sở ---
        printf("Giá cơ sở (Size S): ");
        scanf("%d", &gia_co_so);

        // LỖI 1: Giá cơ sở <= 0 là đơn rác.
        // Lý do dùng continue: continue bỏ qua phần tính tiền bên dưới
        // và chuyển ngay sang hóa đơn tiếp theo, ca làm việc KHÔNG bị dừng.
        if (gia_co_so <= 0) {
            printf("CẢNH BÁO: Giá cơ sở không hợp lệ. Bỏ qua hóa đơn %d.\n", i);
            so_don_loi++;
            continue;
        }

        // --- Nhập và kiểm tra size ---
        printf("Size (S/M/L): ");
        scanf(" %c", &size);   // Dấu cách trước %c để bỏ qua phím Enter còn sót lại

        // So sánh cả chữ hoa và chữ thường để chấp nhận 'S' lẫn 's'
        if (size == 'S' || size == 's') {
            phu_thu_size = 0;
        } else if (size == 'M' || size == 'm') {
            phu_thu_size = 6000;
        } else if (size == 'L' || size == 'l') {
            phu_thu_size = 10000;
        } else {
            // LỖI 1: Ký tự size không tồn tại là đơn rác.
            // Lý do dùng continue: giống lỗi giá, chỉ bỏ qua đơn này,
            // các đơn sau vẫn được nhận bình thường.
            printf("CẢNH BÁO: Size '%c' không tồn tại. Bỏ qua hóa đơn %d.\n", size, i);
            so_don_loi++;
            continue;
        }

        // --- Nhập và kiểm tra topping ---
        printf("Số topping: ");
        scanf("%d", &so_topping);

        // LỖI 2: Topping âm là tín hiệu gian lận / sự cố thiết bị.
        // Lý do dùng break: break thoát hẳn khỏi vòng for,
        // KHÔNG nhận thêm hóa đơn nào nữa. Doanh thu đã cộng trước đó
        // vẫn được giữ lại để in báo cáo lũy kế tới lúc bị ngắt.
        if (so_topping < 0) {
            printf("CẢNH BÁO AN NINH: Số topping âm! Ngắt ca làm việc ngay.\n");
            bi_ngat = 1;
            break;
        }

        // --- Nhập trạng thái hội viên ---
        printf("Hội viên Vàng (1: Có, 0: Không): ");
        scanf("%d", &hoi_vien);

        // --- Tính tiền hóa đơn (chỉ đơn hợp lệ mới tới được đây) ---
        tien_hoa_don = gia_co_so + phu_thu_size + so_topping * 8000;

        // Hội viên Vàng giảm 10%, tức là chỉ trả 90%.
        // Nhân 90 trước rồi mới chia 100 để kết quả là số nguyên chính xác.
        if (hoi_vien == 1) {
            tien_hoa_don = tien_hoa_don * 90 / 100;
        }

        printf("Thành tiền: %d VNĐ\n", tien_hoa_don);

        // --- Cập nhật thống kê ca ---
        so_don_hop_le++;
        doanh_thu = doanh_thu + tien_hoa_don;
        if (tien_hoa_don > don_lon_nhat) {
            don_lon_nhat = tien_hoa_don;
        }
    }

    // ===== BÁO CÁO CUỐI CA =====
    printf("\n========== BÁO CÁO CUỐI CA ==========\n");
    if (bi_ngat == 1) {
        printf("Trạng thái: CA BỊ NGẮT KHẨN CẤP\n");
    } else {
        printf("Trạng thái: Hoàn tất ca bình thường\n");
    }
    printf("Số đơn hợp lệ: %d\n", so_don_hop_le);
    printf("Số đơn bị hủy / lỗi: %d\n", so_don_loi);
    printf("Tổng doanh thu: %lld VNĐ\n", doanh_thu);
    printf("Đơn lớn nhất: %d VNĐ\n", don_lon_nhat);

    return 0;
}
