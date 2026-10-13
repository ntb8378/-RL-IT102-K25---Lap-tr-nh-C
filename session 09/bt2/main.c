/*
 * QUAN LY DANH SACH HANH KHACH & CUOC HANH LY KY GUI
 * Bien dich: gcc -std=c11 -Wall -o main main.c
 *
 * Cuoc hanh ly:
 *   Business (3)         -> 0
 *   Eco (1) / Deluxe (2) -> weight <= 7.0 ? 0 : (weight - 7.0) * 50000.0
 */
#include <stdio.h>
#include <string.h>

struct FlightTicket {
    char  pnrCode[15];
    char  passengerName[50];
    int   ticketClass;      /* 1: Eco, 2: Deluxe, 3: Business */
    float baggageWeight;    /* kg */
    float baggageFee;       /* VND */
};

int main() {
    struct FlightTicket danhSachVe[100];
    int   soLuong = 0;
    int   luaChon, i, viTri, hopLe, len;
    char  pnrInput[15];
    float trongLuongMoi;

    do {
        printf("\n=== HE THONG BAN VE VA CHECK-IN MAY BAY ===\n");
        printf("1. Them ve may bay moi\n");
        printf("2. Hien thi danh sach ve\n");
        printf("3. Cap nhat hanh ly theo PNR\n");
        printf("4. Xoa ve theo PNR\n");
        printf("5. Thoat\n");
        printf("Lua chon cua ban: ");

        if (scanf("%d", &luaChon) != 1) {
            luaChon = -1;                       /* nhap chu -> lua chon khong hop le */
        }
        while (getchar() != '\n');              /* lam sach bo dem */

        switch (luaChon) {

        /* ============================ 1. THEM VE ============================ */
        case 1:
            if (soLuong >= 100) {
                printf("Danh sach ve da day, khong the them moi!\n");
                break;
            }

            /* Ma PNR: khong khoang trang, khong trung */
            do {
                printf("\nNhap ma PNR: ");
                scanf("%14s", danhSachVe[soLuong].pnrCode);
                while (getchar() != '\n');      /* xoa '\n' con dong TRUOC khi goi fgets */

                hopLe = 1;
                for (i = 0; i < soLuong; i++) {
                    if (strcmp(danhSachVe[i].pnrCode, danhSachVe[soLuong].pnrCode) == 0) {
                        printf("Loi: Ma PNR '%s' da ton tai, vui long nhap ma khac!\n",
                               danhSachVe[soLuong].pnrCode);
                        hopLe = 0;
                        break;
                    }
                }
            } while (hopLe == 0);

            /* Ho ten: fgets de nhan khoang trang, cat '\n' cuoi chuoi */
            do {
                printf("Nhap ho ten hanh khach: ");
                fgets(danhSachVe[soLuong].passengerName, 50, stdin);
                len = strlen(danhSachVe[soLuong].passengerName);
                if (len > 0 && danhSachVe[soLuong].passengerName[len - 1] == '\n') {
                    danhSachVe[soLuong].passengerName[len - 1] = '\0';
                    len--;
                }
                if (len == 0) {
                    printf("Loi: Ho ten khong duoc de trong!\n");
                }
            } while (len == 0);

            /* Hang ve: 1 - 3 */
            do {
                printf("Nhap hang ve (1-Eco, 2-Deluxe, 3-Business): ");
                hopLe = scanf("%d", &danhSachVe[soLuong].ticketClass);
                while (getchar() != '\n');
                if (hopLe != 1 || danhSachVe[soLuong].ticketClass < 1
                    || danhSachVe[soLuong].ticketClass > 3) {
                    printf("Loi: Hang ve chi nhan 1, 2 hoac 3!\n");
                    hopLe = 0;
                }
            } while (hopLe == 0);

            /* Khoi luong: so thuc tu 0 den 1000 kg */
            do {
                printf("Nhap khoi luong hanh ly (kg): ");
                hopLe = scanf("%f", &danhSachVe[soLuong].baggageWeight);
                while (getchar() != '\n');
                if (hopLe != 1 || danhSachVe[soLuong].baggageWeight < 0
                    || danhSachVe[soLuong].baggageWeight > 1000) {
                    printf("Loi: Khoi luong phai la so tu 0 den 1000 kg!\n");
                    hopLe = 0;
                }
            } while (hopLe == 0);

            /* Tinh cuoc hanh ly */
            if (danhSachVe[soLuong].ticketClass == 3) {
                danhSachVe[soLuong].baggageFee = 0.0f;
            } else if (danhSachVe[soLuong].baggageWeight <= 7.0f) {
                danhSachVe[soLuong].baggageFee = 0.0f;
            } else {
                danhSachVe[soLuong].baggageFee = (danhSachVe[soLuong].baggageWeight - 7.0f) * 50000.0f;
            }

            printf("=> Them ve thanh cong! Cuoc phat hanh ly qua can: %.0f VND.\n",
                   danhSachVe[soLuong].baggageFee);
            soLuong++;
            break;

        /* ============================ 2. HIEN THI ============================ */
        case 2:
            if (soLuong == 0) {
                printf("Danh sach ve dang rong!\n");
                break;
            }
            printf("\n==========================================================================================\n");
            printf("%-4s | %-10s | %-25s | %-9s | %-12s | %s\n",
                   "STT", "Ma PNR", "Ho ten hanh khach", "Hang ve", "Hanh ly (kg)", "Cuoc qua cuoc");
            printf("==========================================================================================\n");
            for (i = 0; i < soLuong; i++) {
                printf("%-4d | %-10s | %-25s | ", i + 1, danhSachVe[i].pnrCode, danhSachVe[i].passengerName);
                if (danhSachVe[i].ticketClass == 1) {
                    printf("%-9s | ", "Eco");
                } else if (danhSachVe[i].ticketClass == 2) {
                    printf("%-9s | ", "Deluxe");
                } else {
                    printf("%-9s | ", "Business");
                }
                printf("%12.1f | %10.0f VND\n", danhSachVe[i].baggageWeight, danhSachVe[i].baggageFee);
            }
            printf("==========================================================================================\n");
            printf("Tong so ve: %d\n", soLuong);
            break;

        /* ============================ 3. CAP NHAT ============================ */
        case 3:
            if (soLuong == 0) {
                printf("Danh sach ve dang rong!\n");
                break;
            }
            printf("Nhap ma PNR can cap nhat hanh ly: ");
            scanf("%14s", pnrInput);
            while (getchar() != '\n');

            viTri = -1;
            for (i = 0; i < soLuong; i++) {
                if (strcmp(danhSachVe[i].pnrCode, pnrInput) == 0) {
                    viTri = i;
                    break;
                }
            }
            if (viTri == -1) {
                printf("Khong tim thay ve co ma PNR da nhap!\n");
                break;
            }

            printf("Tim thay hanh khach: %s\n", danhSachVe[viTri].passengerName);
            do {
                printf("Nhap trong luong hanh ly moi (kg): ");
                hopLe = scanf("%f", &trongLuongMoi);
                while (getchar() != '\n');
                if (hopLe != 1 || trongLuongMoi < 0 || trongLuongMoi > 1000) {
                    printf("Loi: Khoi luong phai la so tu 0 den 1000 kg!\n");
                    hopLe = 0;
                }
            } while (hopLe == 0);

            danhSachVe[viTri].baggageWeight = trongLuongMoi;
            if (danhSachVe[viTri].ticketClass == 3) {
                danhSachVe[viTri].baggageFee = 0.0f;
            } else if (danhSachVe[viTri].baggageWeight <= 7.0f) {
                danhSachVe[viTri].baggageFee = 0.0f;
            } else {
                danhSachVe[viTri].baggageFee = (danhSachVe[viTri].baggageWeight - 7.0f) * 50000.0f;
            }
            printf("=> Cap nhat thanh cong! Phi hanh ly qua cuoc moi: %.0f VND.\n",
                   danhSachVe[viTri].baggageFee);
            break;

        /* ============================ 4. XOA ============================ */
        case 4:
            if (soLuong == 0) {
                printf("Danh sach ve dang rong!\n");
                break;
            }
            printf("Nhap ma PNR can xoa: ");
            scanf("%14s", pnrInput);
            while (getchar() != '\n');

            viTri = -1;
            for (i = 0; i < soLuong; i++) {
                if (strcmp(danhSachVe[i].pnrCode, pnrInput) == 0) {
                    viTri = i;
                    break;
                }
            }
            if (viTri == -1) {
                printf("Khong tim thay ve co ma PNR da nhap!\n");
                break;
            }

            /* Don mang: dich cac phan tu phia sau len 1 vi tri */
            for (i = viTri; i < soLuong - 1; i++) {
                danhSachVe[i] = danhSachVe[i + 1];
            }
            soLuong--;
            printf("=> Da xoa thanh cong ve co ma PNR: %s ra khoi he thong.\n", pnrInput);
            break;

        /* ============================ 5. THOAT ============================ */
        case 5:
            printf("Cam on ban da su dung he thong. Tam biet!\n");
            break;

        default:
            printf("Lua chon khong hop le! Vui long chon tu 1 den 5.\n");
        }
    } while (luaChon != 5);

    return 0;
}
