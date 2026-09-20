```c
#include <stdio.h>

int main() {
    int ma_mon;
    float don_gia;
    int so_luong;
    float khoang_cach;
    int gio_cao_diem;
    int cua_hang_mo;
    int ton_kho;
    char loai_tai_khoan;

    printf("Nhap ma mon an: ");
    scanf("%d", &ma_mon);

    printf("Nhap don gia mon an (VND): ");
    scanf("%f", &don_gia);

    printf("Nhap so luong dat mua: ");
    scanf("%d", &so_luong);

    printf("Nhap khoang cach giao hang (km): ");
    scanf("%f", &khoang_cach);

    printf("Nhap trang thai gio cao diem (1: Co, 0: Khong): ");
    scanf("%d", &gio_cao_diem);

    printf("Nhap trang thai cua hang (1: Mo, 0: Dong): ");
    scanf("%d", &cua_hang_mo);

    printf("Nhap so luong ton kho: ");
    scanf("%d", &ton_kho);

    printf("Nhap loai tai khoan (V: VIP, N: Normal): ");
    scanf(" %c", &loai_tai_khoan);

    float subtotal = don_gia * so_luong;
    float phi_giao_hang = khoang_cach * 5000.0;

    int dat_freeship = ((subtotal >= 100000.0 && khoang_cach <= 5.0)
                        || loai_tai_khoan == 'V');

    float giam_freeship = 15000.0 * dat_freeship;

    giam_freeship = giam_freeship * (giam_freeship <= phi_giao_hang)
                   + phi_giao_hang * (giam_freeship > phi_giao_hang);

    float phu_phi = 10000.0 * gio_cao_diem;

    int don_hang_hop_le = (cua_hang_mo == 1)
                         && (ton_kho >= so_luong)
                         && (so_luong > 0)
                         && (don_gia > 0);

    float tong_tien = (subtotal + phi_giao_hang - giam_freeship + phu_phi)
                     * don_hang_hop_le;

    printf("\n==================================================\n");
    printf("          SHOPEEFOOD ORDER CHECKOUT SYSTEM\n");
    printf("==================================================\n");

    printf("Ma mon an : %d\n", ma_mon);
    printf("Don gia : %.2f VND\n", don_gia);
    printf("So luong dat : %d\n", so_luong);
    printf("Khoang cach giao : %.1f km\n", khoang_cach);

    printf("Khung gio cao diem : ");
    printf("%s (%d)\n", gio_cao_diem == 1 ? "Co" : "Khong", gio_cao_diem);

    printf("Trang thai quan : ");
    printf("%s (%d)\n", cua_hang_mo == 1 ? "Mo cua" : "Dong cua", cua_hang_mo);

    printf("So luong ton kho : %d\n", ton_kho);

    printf("Loai tai khoan : %c ", loai_tai_khoan);
    printf("%s\n", loai_tai_khoan == 'V' ? "(VIP)" : "(Normal)");

    printf("--------------------------------------------------\n");
    printf("TONG TIEN MON AN : %.2f VND\n", subtotal);
    printf("PHI GIAO HANG CO BAN: %.2f VND\n", phi_giao_hang);
    printf("GIAM GIA FREESHIP : %.2f VND\n", giam_freeship);
    printf("PHU PHI GIO CAO DIEM: %.2f VND\n", phu_phi);
    printf("--------------------------------------------------\n");

    printf("DON HANG HOP LE : %d (1: HOP LE / 0: TU CHOI)\n",
           don_hang_hop_le);
    printf("TONG THANH TIEN : %.2f VND\n", tong_tien);

    printf("==================================================\n");

    return 0;
}
```

