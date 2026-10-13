/*
 * QUAN LY HANH LY KY GUI VE MAY BAY (Vietjet / Vietnam Airlines)
 * Chuan C11. Bien dich: gcc -std=c11 -Wall -o main main.c
 *
 * Pham vi: struct + mang struct, vong lap, if/else - toan bo xu ly trong main().
 * Cuoc hanh ly (50,000 VND/kg):
 *   Business    : <= 20 kg -> 0 ; > 20 kg -> (kg - 20) * 50000
 *   Eco / Deluxe: kg * 50000 (tinh tu kg dau tien)
 */
#include <stdio.h>
#include <string.h>

#define MAX_VE 100

struct VeMayBay {
    char   maVe[16];            /* toi da 15 ky tu + '\0' */
    char   tenHanhKhach[51];    /* toi da 50 ky tu + '\0' */
    char   hangVe[21];          /* toi da 20 ky tu + '\0' */
    float  canNangHanhLy;       /* kg */
    double cuocHanhLy;          /* VND */
};

int main(void) {
    const double DON_GIA_KG = 50000.0;
    const float  MIEN_PHI_BUSINESS = 20.0f;

    struct VeMayBay danhSachVe[MAX_VE];
    int    soLuong = 0;
    int    i, j, nhapOK, hopLe, viTri, viTriNangNhat;
    char   maTim[16];
    float  canNangMoi;
    double tongCuoc;
    size_t len;

    /* ======================= 1. NHAP SO LUONG VE ======================= */
    printf("Nhap so luong ve may bay: ");
    nhapOK = scanf("%d", &soLuong);
    while (getchar() != '\n');
    if (nhapOK != 1 || soLuong < 1 || soLuong > MAX_VE) {
        printf("Loi: So luong ve phai la so nguyen trong khoang [1, %d]. Ket thuc chuong trinh!\n",
               MAX_VE);
        return 1;
    }

    /* ======================= 2. NHAP DANH SACH VE + 3. TINH CUOC ======================= */
    for (i = 0; i < soLuong; i++) {
        printf("\n--- Nhap thong tin ve thu %d ---\n", i + 1);

        /* Ma ve PNR: khong khoang trang, khong trung */
        do {
            printf("Ma ve PNR: ");
            if (scanf("%15s", danhSachVe[i].maVe) != 1) {
                danhSachVe[i].maVe[0] = '\0';
            }
            while (getchar() != '\n');          /* lam sach bo dem truoc khi fgets ho ten */

            hopLe = 1;
            for (j = 0; j < i; j++) {
                if (strcmp(danhSachVe[j].maVe, danhSachVe[i].maVe) == 0) {
                    printf("Loi: Ma ve '%s' da ton tai, vui long nhap ma khac!\n", danhSachVe[i].maVe);
                    hopLe = 0;
                    break;
                }
            }
        } while (!hopLe);

        /* Ho ten hanh khach: fgets nhan khoang trang, loai bo '\n' cuoi chuoi */
        do {
            printf("Ho ten hanh khach: ");
            if (fgets(danhSachVe[i].tenHanhKhach, sizeof(danhSachVe[i].tenHanhKhach), stdin) == NULL) {
                danhSachVe[i].tenHanhKhach[0] = '\0';
            }
            len = strlen(danhSachVe[i].tenHanhKhach);
            if (len > 0 && danhSachVe[i].tenHanhKhach[len - 1] == '\n') {
                danhSachVe[i].tenHanhKhach[len - 1] = '\0';
            } else if (len == sizeof(danhSachVe[i].tenHanhKhach) - 1) {
                while (getchar() != '\n');      /* ten qua dai: bo phan thua trong bo dem */
            }
            hopLe = (strlen(danhSachVe[i].tenHanhKhach) > 0);
            if (!hopLe) {
                printf("Loi: Ho ten khong duoc de trong!\n");
            }
        } while (!hopLe);

        /* Hang ve: Business / Deluxe / Eco */
        do {
            printf("Hang ve (Business/Deluxe/Eco): ");
            if (scanf("%20s", danhSachVe[i].hangVe) != 1) {
                danhSachVe[i].hangVe[0] = '\0';
            }
            while (getchar() != '\n');
            hopLe = (strcmp(danhSachVe[i].hangVe, "Business") == 0
                     || strcmp(danhSachVe[i].hangVe, "Deluxe") == 0
                     || strcmp(danhSachVe[i].hangVe, "Eco") == 0);
            if (!hopLe) {
                printf("Loi: Hang ve chi nhan Business, Deluxe hoac Eco!\n");
            }
        } while (!hopLe);

        /* Khoi luong hanh ly: >= 0, nhap am hoac chu thi bat nhap lai */
        do {
            printf("Khoi luong hanh ly ky gui (kg): ");
            nhapOK = scanf("%f", &danhSachVe[i].canNangHanhLy);
            while (getchar() != '\n');
            hopLe = (nhapOK == 1 && danhSachVe[i].canNangHanhLy >= 0.0f);
            if (!hopLe) {
                printf("Loi: Khoi luong hanh ly phai la so khong am. Vui long nhap lai!\n");
            }
        } while (!hopLe);

        /* Tinh cuoc hanh ly */
        if (strcmp(danhSachVe[i].hangVe, "Business") == 0) {
            if (danhSachVe[i].canNangHanhLy <= MIEN_PHI_BUSINESS) {
                danhSachVe[i].cuocHanhLy = 0.0;
            } else {
                danhSachVe[i].cuocHanhLy =
                    (danhSachVe[i].canNangHanhLy - MIEN_PHI_BUSINESS) * DON_GIA_KG;
            }
        } else {
            danhSachVe[i].cuocHanhLy = danhSachVe[i].canNangHanhLy * DON_GIA_KG;
        }
    }

    /* ======================= 4. HIEN THI DANH SACH ======================= */
    printf("\n================================== DANH SACH VE MAY BAY CHUYEN BAY ==================================\n");
    printf("%-5s %-12s %-25s %-12s %12s %15s\n",
           "STT", "MA VE", "HO TEN HANH KHACH", "HANG VE", "HANH LY (KG)", "CUOC PHI (VND)");
    printf("-----------------------------------------------------------------------------------------------------\n");
    tongCuoc = 0.0;
    viTriNangNhat = 0;
    for (i = 0; i < soLuong; i++) {
        printf("%-5d %-12s %-25s %-12s %12.1f %15.0f\n",
               i + 1, danhSachVe[i].maVe, danhSachVe[i].tenHanhKhach, danhSachVe[i].hangVe,
               danhSachVe[i].canNangHanhLy, danhSachVe[i].cuocHanhLy);
        tongCuoc += danhSachVe[i].cuocHanhLy;
        if (danhSachVe[i].canNangHanhLy > danhSachVe[viTriNangNhat].canNangHanhLy) {
            viTriNangNhat = i;                  /* bang nhau giu ve xuat hien truoc */
        }
    }
    printf("-----------------------------------------------------------------------------------------------------\n");
    printf("Tong tien cuoc hanh ly toan chuyen: %.0f VND\n", tongCuoc);
    printf("Ve co hanh ly ky gui nang nhat: %s - %s (%.1f kg)\n",
           danhSachVe[viTriNangNhat].maVe, danhSachVe[viTriNangNhat].tenHanhKhach,
           danhSachVe[viTriNangNhat].canNangHanhLy);

    /* ======================= 5. CAP NHAT THONG TIN HANH LY ======================= */
    printf("\n--- CAP NHAT THONG TIN HANH LY ---\n");
    printf("Nhap ma ve PNR can cap nhat hanh ly: ");
    if (scanf("%15s", maTim) != 1) {
        maTim[0] = '\0';
    }
    while (getchar() != '\n');

    viTri = -1;
    for (i = 0; i < soLuong; i++) {
        if (strcmp(danhSachVe[i].maVe, maTim) == 0) {
            viTri = i;
            break;
        }
    }

    if (viTri == -1) {
        printf("Khong tim thay ma ve PNR nay trong he thong!\n");
        return 0;
    }

    printf("Tim thay ma ve %s - %s (%s, %.1f kg).\n", danhSachVe[viTri].maVe,
           danhSachVe[viTri].tenHanhKhach, danhSachVe[viTri].hangVe, danhSachVe[viTri].canNangHanhLy);
    do {
        printf("Nhap can nang hanh ly ky gui moi (kg): ");
        nhapOK = scanf("%f", &canNangMoi);
        while (getchar() != '\n');
        hopLe = (nhapOK == 1 && canNangMoi >= 0.0f);
        if (!hopLe) {
            printf("Loi: Khoi luong hanh ly phai la so khong am. Vui long nhap lai!\n");
        }
    } while (!hopLe);

    danhSachVe[viTri].canNangHanhLy = canNangMoi;
    if (strcmp(danhSachVe[viTri].hangVe, "Business") == 0) {
        if (danhSachVe[viTri].canNangHanhLy <= MIEN_PHI_BUSINESS) {
            danhSachVe[viTri].cuocHanhLy = 0.0;
        } else {
            danhSachVe[viTri].cuocHanhLy =
                (danhSachVe[viTri].canNangHanhLy - MIEN_PHI_BUSINESS) * DON_GIA_KG;
        }
    } else {
        danhSachVe[viTri].cuocHanhLy = danhSachVe[viTri].canNangHanhLy * DON_GIA_KG;
    }
    printf("Da cap nhat cuoc hanh ly moi: %.0f VND.\n", danhSachVe[viTri].cuocHanhLy);

    /* In lai bang sau cap nhat */
    printf("\n================================ DANH SACH VE MAY BAY SAU CAP NHAT ================================\n");
    printf("%-5s %-12s %-25s %-12s %12s %15s\n",
           "STT", "MA VE", "HO TEN HANH KHACH", "HANG VE", "HANH LY (KG)", "CUOC PHI (VND)");
    printf("-----------------------------------------------------------------------------------------------------\n");
    tongCuoc = 0.0;
    viTriNangNhat = 0;
    for (i = 0; i < soLuong; i++) {
        printf("%-5d %-12s %-25s %-12s %12.1f %15.0f\n",
               i + 1, danhSachVe[i].maVe, danhSachVe[i].tenHanhKhach, danhSachVe[i].hangVe,
               danhSachVe[i].canNangHanhLy, danhSachVe[i].cuocHanhLy);
        tongCuoc += danhSachVe[i].cuocHanhLy;
        if (danhSachVe[i].canNangHanhLy > danhSachVe[viTriNangNhat].canNangHanhLy) {
            viTriNangNhat = i;
        }
    }
    printf("-----------------------------------------------------------------------------------------------------\n");
    printf("Tong tien cuoc hanh ly toan chuyen: %.0f VND\n", tongCuoc);
    printf("Ve co hanh ly ky gui nang nhat: %s - %s (%.1f kg)\n",
           danhSachVe[viTriNangNhat].maVe, danhSachVe[viTriNangNhat].tenHanhKhach,
           danhSachVe[viTriNangNhat].canNangHanhLy);

    return 0;
}
