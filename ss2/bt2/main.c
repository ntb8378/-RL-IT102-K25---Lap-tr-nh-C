#include <stdio.h>

int main(void)
{
    int vehicle_type;
    double distance;
    int is_peak_or_rain;

    printf("Nhap loai xe (1-Bike, 2-Car): ");
    scanf("%d", &vehicle_type);

    printf("Nhap khoang cach (km): ");
    scanf("%lf", &distance);

    printf("Nhap trang thai phu phi (1-Co, 0-Khong): ");
    scanf("%d", &is_peak_or_rain);

    if (distance <= 0.0 || distance > 300.0)
    {
        printf("Loi: Khoang cach khong hop le.\n"); 
        return 0;
    }

    if (vehicle_type != 1 && vehicle_type != 2)
    {
        printf("Loi: Ma loai xe khong hop le.\n");
        return 0;
    }

    if (is_peak_or_rain != 0 && is_peak_or_rain != 1)
    {
        printf("Loi: Trang thai phu phi khong hop le.\n");
        return 0;
    }

    printf("Du lieu hop le.\n");

    return 0;
}
