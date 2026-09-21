#include <stdio.h>

int main() {
    int tuoi;
    int ma_phim;
    int ma_ghe;
    int ma_doi_tuong;

    float phu_thu_ghe;
    float giam_gia;
    float gia_sau_giam;
    float tong_tien;

    printf("--- HE THONG BAN VE PHIM CGV ---\n");

    printf("Nhap tuoi khang gia: ");
    scanf("%d", &tuoi);

    printf("Nhap ma loai phim (1-P, 2-T18): ");
    scanf("%d", &ma_phim);

    printf("Nhap ma loai ghe (1-Thuong, 2-VIP, 3-Couple): ");
    scanf("%d", &ma_ghe);

    printf("Nhap ma doi tuong (1-Thuong, 2-HS/SV): ");
    scanf("%d", &ma_doi_tuong);

    if (tuoi <= 0 ||
        (ma_phim != 1 && ma_phim != 2) ||
        (ma_ghe != 1 && ma_ghe != 2 && ma_ghe != 3) ||
        (ma_doi_tuong != 1 && ma_doi_tuong != 2)) {

        printf("LOI: Du lieu nhap vao khong hop le!\n");
        return 0;
    }

    if (ma_phim == 2 && tuoi < 18) {
        printf("TU CHOI BAN VE: Khang gia chua du 18 tuoi de xem phim T18!\n");
        return 0;
    }

    switch (ma_ghe) {
        case 1:
            phu_thu_ghe = 0;
            break;

        case 2:
            phu_thu_ghe = 15000;
            break;

        case 3:
            phu_thu_ghe = 30000;
            break;
    }

    if (ma_doi_tuong == 2) {
        giam_gia = 80000.0 * 0.20;
    } else {
        giam_gia = 0.0;
    }

    gia_sau_giam = 80000.0 - giam_gia;
    tong_tien = gia_sau_giam + phu_thu_ghe;

    printf("\n--- HOA DON THANH TOAN ---\n");

    if (ma_doi_tuong == 1) {
        printf("Doi tuong: Khach hang thong thuong\n");
    } else {
        printf("Doi tuong: Hoc sinh / Sinh vien\n");
    }

    if (ma_ghe == 1) {
        printf("Loai ghe: Ghe Thuong\n");
    } else if (ma_ghe == 2) {
        printf("Loai ghe: VIP\n");
    } else {
        printf("Loai ghe: Couple\n");
    }

    printf("Gia ve goc: %.0f VND\n", 80000.0);
    printf("Giam gia uu dai: %.0f VND\n", giam_gia);
    printf("Phu thu ghe: %.0f VND\n", phu_thu_ghe);
    printf("Tong tien thanh toan: %.0f VND\n", tong_tien);

    return 0;
}
