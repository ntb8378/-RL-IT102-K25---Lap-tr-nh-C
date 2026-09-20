#include <stdio.h>

int main() {
    float distance;
    int is_raining;
    double total_fare = 0.0;

    printf("Nhap quang duong di chuyen (km): ");
    scanf("%f", &distance);

    printf("Thoi tiet co mua khong (1: Co, 0: Khong): ");
    scanf("%d", &is_raining);

    if (distance <= 2.0) {
        total_fare = 12000.0;
    } else {
        total_fare = 12000.0 + (distance - 2.0) * 4500.0;
    }

    if (is_raining == 1) {
        total_fare = total_fare * 1.2;
    }

    printf("Tong cuoc phi chuyen xe: %.0f VND\n", total_fare);

    return 0;
}
