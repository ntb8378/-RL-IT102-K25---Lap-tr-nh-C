#include <stdio.h>

int main(void)
{
    double distance_km;
    int is_surge;

    double base_fare;
    double total_fare;

    // Nhap du lieu
    printf("Nhap khoang cach (km): ");
    scanf("%lf", &distance_km);

    printf("Nhap trang thai surge (0-Binh thuong, 1-Co phu phi): ");
    scanf("%d", &is_surge);

    // Guard Clause: kiem tra khoang cach
    if (distance_km <= 0.0)
    {
        printf("Loi: Khoang cach khong hop le.\n");
        return 0;
    }

    // Guard Clause: kiem tra trang thai surge
    if (is_surge != 0 && is_surge != 1)
    {
        printf("Loi: Trang thai surge khong hop le.\n");
        return 0;
    }

    // Tinh cuoc co ban theo khoang cach
    if (distance_km <= 2.0)
    {
        base_fare = 12000;
    }
    else
    {
        base_fare = 12000 + (distance_km - 2.0) * 4500;
    }

    // Ap dung phu phi
    if (is_surge == 1)
    {
        total_fare = base_fare * 1.2;
    }
    else
    {
        total_fare = base_fare;
    }

    // Hien thi ket qua
    printf("\n===== KET QUA =====\n");
    printf("Khoang cach: %.2f km\n", distance_km);
    printf("Cuoc co ban: %.2f VND\n", base_fare);
    printf("Tong cuoc: %.2f VND\n", total_fare);

    return 0;
}
