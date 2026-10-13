
#include <stdio.h>
#include <string.h>

#define MAX_ZONES 10
#define MAX_QRS 50
#define MAX_MUA 4

struct TicketZone {
    int zone_id;
    char zone_name[30];
    float ticket_price;
    int total_capacity;
    int sold_tickets;
};

struct QrCheckIn {
    int qr_code;
    int zone_id;
    int is_used;
};

/* Function prototypes */
int timKhuVuc(const struct TicketZone zones[],
              int total_zones, int zone_id);

float tinhGiaVe(float ticket_price, int is_early_bird);

int banVe(struct TicketZone zones[], int total_zones,
          int zone_id, int quantity, int is_early_bird);

int timQR(const struct QrCheckIn qrs[],
          int total_qrs, int qr_code);

int checkInQR(struct QrCheckIn qrs[], int total_qrs,
              int qr_code);

void hienThiKhuVuc(const struct TicketZone zones[],
                   int total_zones);

int main(void) {
    struct TicketZone zones[MAX_ZONES] = {
        {1, "VIP", 2000000.0f, 10, 8},
        {2, "Zone A", 1200000.0f, 20, 5},
        {3, "GA", 800000.0f, 30, 10}
    };

    struct QrCheckIn qrs[MAX_QRS] = {
        {1001, 1, 0},
        {1002, 1, 0},
        {2001, 2, 1}
    };

    int total_zones = 3;
    int total_qrs = 3;

    printf("=== TICKETBOX LIVE CONCERT ===\n");

    printf("\n1. DANH SACH KHU VUC BAN DAU\n");
    hienThiKhuVuc(zones, total_zones);

    printf("\n2. BAN 2 VE VIP - EARLY BIRD\n");
    banVe(zones, total_zones, 1, 2, 1);

    printf("\n3. KIEM TRA SO LUONG MUA KHONG HOP LE\n");
    banVe(zones, total_zones, 1, -2, 0);
    banVe(zones, total_zones, 1, 0, 0);
    banVe(zones, total_zones, 1, 5, 0);

    printf("\n4. KIEM TRA VUOT SUC CHUA\n");
    banVe(zones, total_zones, 1, 3, 0);

    printf("\n5. KIEM TRA KHU VUC KHONG TON TAI\n");
    banVe(zones, total_zones, 99, 1, 0);

    printf("\n6. CHECK-IN QR 1001\n");
    checkInQR(qrs, total_qrs, 1001);

    printf("\n7. QUET LAI QR 1001\n");
    checkInQR(qrs, total_qrs, 1001);

    printf("\n8. CHECK-IN QR KHONG TON TAI\n");
    checkInQR(qrs, total_qrs, 9999);

    printf("\n9. KIEM TRA DANH SACH RONG\n");
    banVe(zones, 0, 1, 1, 0);
    checkInQR(qrs, 0, 1001);

    printf("\n10. DANH SACH KHU VUC SAU KIEM THU\n");
    hienThiKhuVuc(zones, total_zones);

    return 0;
}

/* Tim khu vuc theo ma */
int timKhuVuc(const struct TicketZone zones[],
              int total_zones, int zone_id) {
    int i;

    for (i = 0; i < total_zones; i++) {
        if (zones[i].zone_id == zone_id) {
            return i;
        }
    }

    return -1;
}

/* Tinh gia ve sau khi giam gia */
float tinhGiaVe(float ticket_price, int is_early_bird) {
    if (is_early_bird == 1) {
        return ticket_price * 0.85f;
    }

    return ticket_price;
}

/* Xu ly giao dich ban ve */
int banVe(struct TicketZone zones[], int total_zones,
          int zone_id, int quantity, int is_early_bird) {
    int viTri;
    float giaVe;

    if (total_zones <= 0) {
        printf("[LOI] Danh sach khu vuc dang rong!\n");
        return 0;
    }

    if (quantity < 1 || quantity > MAX_MUA) {
        printf("[LOI] So luong mua phai tu 1 den %d!\n",
               MAX_MUA);
        return 0;
    }

    if (is_early_bird != 0 && is_early_bird != 1) {
        printf("[LOI] Trang thai Early Bird khong hop le!\n");
        return 0;
    }

    viTri = timKhuVuc(zones, total_zones, zone_id);

    if (viTri == -1) {
        printf("[LOI] Khu vuc %d khong ton tai!\n", zone_id);
        return 0;
    }

    if (zones[viTri].sold_tickets + quantity >
        zones[viTri].total_capacity) {
        printf("[LOI] Khu vuc %s khong du ve!\n",
               zones[viTri].zone_name);
        return 0;
    }

    giaVe = tinhGiaVe(zones[viTri].ticket_price,
                      is_early_bird);

    zones[viTri].sold_tickets += quantity;

    printf("[THANH CONG] Da ban %d ve khu vuc %s.\n",
           quantity, zones[viTri].zone_name);
    printf("Gia moi ve: %.0f VND\n", giaVe);
    printf("Tong tien: %.0f VND\n", giaVe * quantity);
    printf("So ve da ban: %d/%d\n",
           zones[viTri].sold_tickets,
           zones[viTri].total_capacity);

    return 1;
}

/* Tim QR theo ma */
int timQR(const struct QrCheckIn qrs[],
          int total_qrs, int qr_code) {
    int i;

    for (i = 0; i < total_qrs; i++) {
        if (qrs[i].qr_code == qr_code) {
            return i;
        }
    }

    return -1;
}

/* Check-in QR chi mot lan */
int checkInQR(struct QrCheckIn qrs[], int total_qrs,
              int qr_code) {
    int viTri;

    if (total_qrs <= 0) {
        printf("[LOI] Danh sach QR dang rong!\n");
        return 0;
    }

    viTri = timQR(qrs, total_qrs, qr_code);

    if (viTri == -1) {
        printf("[TU CHOI] Ma QR %d khong ton tai!\n",
               qr_code);
        return 0;
    }

    if (qrs[viTri].is_used == 1) {
        printf("[CANH BAO] QR %d da duoc su dung!\n",
               qr_code);
        return 0;
    }

    qrs[viTri].is_used = 1;

    printf("[THANH CONG] Check-in QR %d thanh cong!\n",
           qr_code);

    return 1;
}

/* Hien thi thong tin khu vuc */
void hienThiKhuVuc(const struct TicketZone zones[],
                   int total_zones) {
    int i;

    if (total_zones <= 0) {
        printf("Khong co khu vuc nao.\n");
        return;
    }

    for (i = 0; i < total_zones; i++) {
        printf("Ma: %d | Ten: %s | Gia: %.0f VND"
               " | Da ban: %d | Con lai: %d\n",
               zones[i].zone_id,
               zones[i].zone_name,
               zones[i].ticket_price,
               zones[i].sold_tickets,
               zones[i].total_capacity -
                   zones[i].sold_tickets);
    }
}

