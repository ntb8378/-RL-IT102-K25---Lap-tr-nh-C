#include <stdio.h>

int main() {
    int order_id;
    int subtotal;
    float distance_km;
    int booking_hour;
    int is_store_open;
    int inventory_qty;

    int is_peak_hour;
    int is_discount_eligible;
    int is_valid_order;

    int base_fee = 15000;
    int surcharge;
    int discount;
    int final_delivery_fee;
    int total_payment;

    printf("Nhap ma don hang: ");
    scanf("%d", &order_id);

    printf("Nhap gia tri tien mon an (VND): ");
    scanf("%d", &subtotal);

    printf("Nhap khoang cach giao hang (km): ");
    scanf("%f", &distance_km);

    printf("Nhap gio dat hang (0-23): ");
    scanf("%d", &booking_hour);

    printf("Nhap trang thai cua hang (1: Mo, 0: Dong): ");
    scanf("%d", &is_store_open);

    printf("Nhap so luong ton kho: ");
    scanf("%d", &inventory_qty);

    is_peak_hour = ((booking_hour >= 11 && booking_hour <= 13)
                    || (booking_hour >= 18 && booking_hour <= 20));

    is_discount_eligible = (subtotal >= 100000);

    surcharge = 10000 * is_peak_hour;
    discount = 15000 * is_discount_eligible;

    is_valid_order = (is_store_open == 1)
                     && (inventory_qty > 0)
                     && (distance_km > 0.0)
                     && (distance_km <= 15.0)
                     && (booking_hour >= 0)
                     && (booking_hour <= 23)
                     && (subtotal >= 0);

    final_delivery_fee = (base_fee + surcharge - discount) * is_valid_order;

    total_payment = (subtotal + final_delivery_fee) * is_valid_order;

    printf("\n==================================================\n");
    printf("             SHOPEEFOOD ORDER RECEIPT\n");
    printf("==================================================\n");

    printf("Ma don hang          : %d\n", order_id);
    printf("Tien mon an          : %d VND\n", subtotal);
    printf("Khoang cach          : %.1f km\n", distance_km);
    printf("Gio dat hang         : %d\n", booking_hour);
    printf("Cua hang mo          : %d\n", is_store_open);
    printf("Ton kho              : %d\n", inventory_qty);

    printf("--------------------------------------------------\n");
    printf("Phi giao hang co ban : %d VND\n", base_fee);
    printf("Phu phi cao diem     : %d VND\n", surcharge);
    printf("Giam phi giao hang   : %d VND\n", discount);
    printf("Phi giao hang thuc te: %d VND\n", final_delivery_fee);

    printf("--------------------------------------------------\n");
    printf("Don hang hop le      : %d\n", is_valid_order);
    printf("TONG THANH TOAN      : %d VND\n", total_payment);

    printf("==================================================\n");

    return 0;
}
