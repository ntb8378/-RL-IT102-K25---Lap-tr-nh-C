/*
 * HE THONG CHECK-IN VE MAY BAY
 * Bien dich: gcc -std=c11 -Wall -o main main.c
 *
 * Phu thu hanh ly: trongLuong > 7.0 kg -> (trongLuong - 7.0) * 50000 VND; nguoc lai 0.
 */
#include <stdio.h>
#include <string.h>

struct VeMayBay {
    char  maPNR[10];
    char  tenHanhKhach[50];
    char  hangVe[15];
    float trongLuongHanhLy;
    long  phiPhuThu;
};

int main() {
    struct VeMayBay ds[50];
    int   n, i, j, viTri, hopLe, len;
    char  buffer[100];
    float trongLuongMoi;

    printf("=== HE THONG CHECK-IN VE MAY BAY ===\n");

    /* ======================= 1. NHAP SO LUONG VE ======================= */
    do {
        printf("Nhap so luong ve (1 - 50): ");
        hopLe = scanf("%d", &n);
        while (getchar() != '\n');              /* lam sach bo dem sau scanf */
        if (hopLe != 1 || n < 1 || n > 50) {
            printf("Loi: So luong ve phai la so nguyen tu 1 den 50. Vui long nhap lai!\n");
            hopLe = 0;
        }
    } while (hopLe == 0);

    /* ======================= 2. NHAP DANH SACH VE ======================= */
    for (i = 0; i < n; i++) {
        printf("\n--- Nhap thong tin ve thu %d ---\n", i + 1);

        /* Ma PNR: tu 1 den 9 ky tu, khong trung */
        do {
            printf("Nhap ma PNR: ");
            fgets(buffer, 100, stdin);
            len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';         /* xoa '\n' thua cuoi chuoi */
                len--;
            }

            hopLe = 1;
            if (len == 0 || len > 9) {
                printf("Loi: Ma PNR phai co tu 1 den 9 ky tu!\n");
                hopLe = 0;
            } else {
                for (j = 0; j < i; j++) {
                    if (strcmp(ds[j].maPNR, buffer) == 0) {
                        printf("Loi: Ma PNR '%s' da ton tai, vui long nhap ma khac!\n", buffer);
                        hopLe = 0;
                        break;
                    }
                }
            }
        } while (hopLe == 0);
        strcpy(ds[i].maPNR, buffer);

        /* Ho ten hanh khach: tu 1 den 49 ky tu */
        do {
            printf("Nhap ho ten hanh khach: ");
            fgets(buffer, 100, stdin);
            len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
                len--;
            }

            hopLe = 1;
            if (len == 0 || len > 49) {
                printf("Loi: Ho ten phai co tu 1 den 49 ky tu!\n");
                hopLe = 0;
            }
        } while (hopLe == 0);
        strcpy(ds[i].tenHanhKhach, buffer);

        /* Hang ve: chi nhan Eco / Deluxe / Business */
        do {
            printf("Nhap hang ve (Eco/Deluxe/Business): ");
            fgets(buffer, 100, stdin);
            len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
            }

            hopLe = 1;
            if (strcmp(buffer, "Eco") != 0 && strcmp(buffer, "Deluxe") != 0
                && strcmp(buffer, "Business") != 0) {
                printf("Loi: Hang ve chi nhan Eco, Deluxe hoac Business!\n");
                hopLe = 0;
            }
        } while (hopLe == 0);
        strcpy(ds[i].hangVe, buffer);

        /* Trong luong hanh ly: so thuc tu 0 den 1000 kg */
        do {
            printf("Nhap trong luong hanh ly (kg): ");
            hopLe = scanf("%f", &ds[i].trongLuongHanhLy);
            while (getchar() != '\n');          /* lam sach truoc fgets cua ve tiep theo */
            if (hopLe != 1 || ds[i].trongLuongHanhLy < 0 || ds[i].trongLuongHanhLy > 1000) {
                printf("Loi: Trong luong phai la so tu 0 den 1000 kg. Vui long nhap lai!\n");
                hopLe = 0;
            }
        } while (hopLe == 0);

        /* ======================= 3. TINH PHI PHU THU ======================= */
        /* Cong 0.5 de lam tron: float khong luu chinh xac so thap phan,
         * vd 7.1 kg -> 4999.99 -> neu khong lam tron se bi cat thanh 4999 thay vi 5000. */
        if (ds[i].trongLuongHanhLy > 7.0f) {
            ds[i].phiPhuThu = (ds[i].trongLuongHanhLy - 7.0f) * 50000 + 0.5f;
        } else {
            ds[i].phiPhuThu = 0;
        }
    }

    /* ======================= 4. XUAT DANH SACH VE ======================= */
    printf("\n=== DANH SACH VE MAY BAY CHUYEN BAY ===\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("%-5s %-10s %-25s %-12s %-12s %-15s\n",
           "STT", "MA PNR", "HO TEN HANH KHACH", "HANG VE", "HANH LY(KG)", "PHI PHU THU(VND)");
    printf("-----------------------------------------------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("%-5d %-10s %-25s %-12s %-12.1f %-15ld\n",
               i + 1, ds[i].maPNR, ds[i].tenHanhKhach, ds[i].hangVe,
               ds[i].trongLuongHanhLy, ds[i].phiPhuThu);
    }
    printf("-----------------------------------------------------------------------------------------\n");

    /* ======================= 5. TIM KIEM & CAP NHAT ======================= */
    printf("\n=== CAP NHAT THONG TIN HANH LY ===\n");
    printf("Nhap ma PNR can cap nhat: ");
    fgets(buffer, 100, stdin);
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    /* Tim kiem tuyen tinh bang strcmp */
    viTri = -1;
    for (i = 0; i < n; i++) {
        if (strcmp(ds[i].maPNR, buffer) == 0) {
            viTri = i;
            break;
        }
    }

    if (viTri == -1) {
        printf("Khong tim thay ma PNR hop le!\n");
    } else {
        printf("Tim thay ve cua hanh khach: %s\n", ds[viTri].tenHanhKhach);
        printf("  Ma PNR: %s | Hang ve: %s | Hanh ly hien tai: %.1f kg | Phu thu hien tai: %ld VND\n",
               ds[viTri].maPNR, ds[viTri].hangVe,
               ds[viTri].trongLuongHanhLy, ds[viTri].phiPhuThu);

        do {
            printf("Nhap trong luong hanh ly moi (kg): ");
            hopLe = scanf("%f", &trongLuongMoi);
            while (getchar() != '\n');
            if (hopLe != 1 || trongLuongMoi < 0 || trongLuongMoi > 1000) {
                printf("Loi: Trong luong phai la so tu 0 den 1000 kg. Vui long nhap lai!\n");
                hopLe = 0;
            }
        } while (hopLe == 0);

        ds[viTri].trongLuongHanhLy = trongLuongMoi;
        if (ds[viTri].trongLuongHanhLy > 7.0f) {
            ds[viTri].phiPhuThu = (ds[viTri].trongLuongHanhLy - 7.0f) * 50000 + 0.5f;
        } else {
            ds[viTri].phiPhuThu = 0;
        }
        printf("Cap nhat thanh cong! Phi phu thu moi: %ld VND\n", ds[viTri].phiPhuThu);

        printf("\n=== DANH SACH VE MAY BAY SAU CAP NHAT ===\n");
        printf("-----------------------------------------------------------------------------------------\n");
        printf("%-5s %-10s %-25s %-12s %-12s %-15s\n",
               "STT", "MA PNR", "HO TEN HANH KHACH", "HANG VE", "HANH LY(KG)", "PHI PHU THU(VND)");
        printf("-----------------------------------------------------------------------------------------\n");
        for (i = 0; i < n; i++) {
            printf("%-5d %-10s %-25s %-12s %-12.1f %-15ld\n",
                   i + 1, ds[i].maPNR, ds[i].tenHanhKhach, ds[i].hangVe,
                   ds[i].trongLuongHanhLy, ds[i].phiPhuThu);
        }
        printf("-----------------------------------------------------------------------------------------\n");
    }

    return 0;
}
