```c
#include <stdio.h>

int main() {
    int maPhim;
    int tuoi;
    int loaiGhe;
    int doiTuong;

    int gia_co_ban = 80000;
    int phuThu;
    int tong_truoc_giam;

    float ti_le_giam;
    float tien_giam;
    float tong_tien_thanh_toan;

    printf("=== HE THONG BAN VE PHIM CGV / LOTTE ===\n");

    printf("Nhap ma loai phim (1: Phim P, 2: Phim C18): ");
    scanf("%d", &maPhim);

    printf("Nhap tuoi cua khan gia: ");
    scanf("%d", &tuoi);

    printf("Nhap loai ghe (1: Ghe Thuong, 2: Ghe VIP): ");
    scanf("%d", &loaiGhe);

    printf("Nhap doi tuong (1: Khach thong thuong, 2: HSSV): ");
    scanf("%d", &doiTuong);

    if (maPhim == 2 && tuoi < 18) {
        printf("\n[THONG BAO] Tu choi ban ve: Khach gia chua du 18 tuoi de xem phim mac C18!\n");
        return 0;
    }

    switch (loaiGhe) {
        case 1:
            phuThu = 0;
            break;

        case 2:
            phuThu = 15000;
            break;

        default:
            printf("\n[LOI] Ma loai ghe khong hop le! Vui long chon 1 (Thuong) hoac 2 (VIP).\n");
            return 0;
    }

    tong_truoc_giam = gia_co_ban + phuThu;

    ti_le_giam = 0;

    if (doiTuong == 2) {
        ti_le_giam = 0.2;
    }

    tien_giam = tong_truoc_giam * ti_le_giam;
    tong_tien_thanh_toan = tong_truoc_giam - tien_giam;

    printf("\n=== HOA DON THANH TOAN VE PHIM ===\n");
    printf("Gia ve chuan: %d VND\n", gia_co_ban);

    if (phuThu > 0) {
        printf("Phu thu ghe VIP: %d VND\n", phuThu);
    } else {
        printf("Phu thu ghe VIP: 0 VND\n");
    }

    printf("Tong phi dich vu: %d VND\n", tong_truoc_giam);

    if (doiTuong == 2) {
        printf("Giam gia HSSV (20%%): %.0f VND\n", tien_giam);
    } else {
        printf("Giam gia: 0 VND\n");
    }

    printf("-----------------------------------\n");
    printf("TONG TIEN PHAI THANH TOAN: %.0f VND\n", tong_tien_thanh_toan);

    return 0;
}
```

