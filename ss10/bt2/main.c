
#include <stdio.h>

#define MAX_VE 50

struct VeSuKien {
    int maVe;
    char tenSuKien[50];
    char loaiVe[20];
    float giaGoc;
    int isEarlyBird;
    int daCheckIn;
};

/* Khai bao prototype */
float tinhGiaThanhToan(struct VeSuKien ve);
int timVeTheoMa(const struct VeSuKien dsVe[], int soLuongVe, int maVe);
int phatHanhVe(struct VeSuKien dsVe[], int soLuongVe,
               struct VeSuKien veMoi);
int checkInQR(struct VeSuKien dsVe[], int soLuongVe, int maVe);
int huyVe(struct VeSuKien dsVe[], int soLuongVe, int maVe);
void hienThiDanhSachVe(const struct VeSuKien dsVe[], int soLuongVe);

int main(void) {
    struct VeSuKien dsVe[MAX_VE] = {
        {1001, "Live Concert VIBE 2025", "VIP", 2000000.0f, 1, 0},
        {1002, "Live Concert VIBE 2025", "Zone A", 1200000.0f, 0, 0},
        {1003, "Live Concert VIBE 2025", "GA", 800000.0f, 1, 0}
    };

    int soLuongVe = 3;

    struct VeSuKien veMoi = {
        1004, "Live Concert VIBE 2025", "VIP",
        2500000.0f, 0, 0
    };

    printf("=== HE THONG QUAN LY VE TICKETBOX ===\n");

    printf("\n1. DANH SACH VE BAN DAU\n");
    hienThiDanhSachVe(dsVe, soLuongVe);

    printf("\n2. PHAT HANH VE MOI\n");
    soLuongVe = phatHanhVe(dsVe, soLuongVe, veMoi);

    printf("\n3. CHECK-IN QR VE 1001\n");
    checkInQR(dsVe, soLuongVe, 1001);

    printf("\n4. QUET LAI MA VE 1001\n");
    checkInQR(dsVe, soLuongVe, 1001);

    printf("\n5. HUY VE 1002\n");
    soLuongVe = huyVe(dsVe, soLuongVe, 1002);

    printf("\n6. CHECK-IN MA VE KHONG TON TAI 9999\n");
    checkInQR(dsVe, soLuongVe, 9999);

    printf("\n7. DANH SACH VE SAU CAC THAO TAC\n");
    hienThiDanhSachVe(dsVe, soLuongVe);

    return 0;
}

/* Tinh gia ve sau khi ap dung Early Bird */
float tinhGiaThanhToan(struct VeSuKien ve) {
    if (ve.isEarlyBird == 1) {
        return ve.giaGoc * 0.85f;
    }

    return ve.giaGoc;
}

/* Tim vi tri ve theo ma, khong tim thay thi tra ve -1 */
int timVeTheoMa(const struct VeSuKien dsVe[],
                int soLuongVe, int maVe) {
    int i;

    for (i = 0; i < soLuongVe; i++) {
        if (dsVe[i].maVe == maVe) {
            return i;
        }
    }

    return -1;
}

/* Phat hanh ve moi */
int phatHanhVe(struct VeSuKien dsVe[], int soLuongVe,
               struct VeSuKien veMoi) {
    if (soLuongVe >= MAX_VE) {
        printf("[LOI] Danh sach da day, khong the phat hanh ve!\n");
        return soLuongVe;
    }

    if (timVeTheoMa(dsVe, soLuongVe, veMoi.maVe) != -1) {
        printf("[LOI] Ma ve %d da ton tai!\n", veMoi.maVe);
        return soLuongVe;
    }

    dsVe[soLuongVe] = veMoi;
    soLuongVe++;

    printf("[THANH CONG] Da phat hanh ve %d (%s).\n",
           veMoi.maVe, veMoi.loaiVe);

    return soLuongVe;
}

/* Check-in QR */
int checkInQR(struct VeSuKien dsVe[], int soLuongVe, int maVe) {
    int viTri;

    if (soLuongVe == 0) {
        printf("[LOI] Danh sach ve dang rong!\n");
        return 0;
    }

    viTri = timVeTheoMa(dsVe, soLuongVe, maVe);

    if (viTri == -1) {
        printf("[TU CHOI] Ma ve %d khong ton tai!\n", maVe);
        return 0;
    }

    if (dsVe[viTri].daCheckIn == 1) {
        printf("[CANH BAO] Ve %d da check-in truoc do! "
               "Tu choi quet lai.\n", maVe);
        return 0;
    }

    dsVe[viTri].daCheckIn = 1;

    printf("[THANH CONG] Check-in ve %d thanh cong!\n", maVe);
    return 1;
}

/* Huy ve va don mang */
int huyVe(struct VeSuKien dsVe[], int soLuongVe, int maVe) {
    int viTri;
    int i;

    if (soLuongVe == 0) {
        printf("[LOI] Danh sach ve dang rong, khong the huy!\n");
        return soLuongVe;
    }

    viTri = timVeTheoMa(dsVe, soLuongVe, maVe);

    if (viTri == -1) {
        printf("[LOI] Khong tim thay ve %d de huy!\n", maVe);
        return soLuongVe;
    }

    for (i = viTri; i < soLuongVe - 1; i++) {
        dsVe[i] = dsVe[i + 1];
    }

    soLuongVe--;

    printf("[THANH CONG] Da huy ve %d.\n", maVe);
    return soLuongVe;
}

/* Hien thi danh sach ve */
void hienThiDanhSachVe(const struct VeSuKien dsVe[],
                       int soLuongVe) {
    int i;

    if (soLuongVe == 0) {
        printf("Danh sach hien chua co ve nao.\n");
        return;
    }

    printf("Tong so ve: %d\n", soLuongVe);

    for (i = 0; i < soLuongVe; i++) {
        printf("Ma ve: %d | Khu vuc: %s | "
               "Gia thanh toan: %.0f VND | ",
               dsVe[i].maVe,
               dsVe[i].loaiVe,
               tinhGiaThanhToan(dsVe[i]));

        if (dsVe[i].daCheckIn == 1) {
            printf("Da check-in\n");
        } else {
            printf("Chua check-in\n");
        }
    }
}

