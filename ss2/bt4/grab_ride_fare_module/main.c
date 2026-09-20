#include <stdio.h>

int main(void)
{
    double distance_km;
    int is_surcharge;

    double base_fare;
    double surcharge;
    double total_fare;

    printf("Nhap khoang cach (km): ");
    scanf("%lf", &distance_km);

    printf("Nhap trang thai phu phi (0-Khong, 1-Co): ");
    scanf("%d", &is_surcharge);

    // Kiem tra khoang cach
    if (distance_km <= 0)
    {
        printf("Loi: Khoang cach khong hop le.\n");
        return 0;
    }
    else
    {
        // Tinh cuoc co ban
        if (distance_km <= 2)
        {
            base_fare = 12000;
        }
        else
        {
            base_fare = 12000 + (distance_km - 2) * 4500;
        }

        // Tinh phu phi
        if (is_surcharge == 1)
        {
            surcharge = base_fare * 0.2;
        }
        else
        {
            surcharge = 0;
        }

        // Tinh tong tien
        total_fare = base_fare + surcharge;

        // Xuat hoa don
        printf("\n===== HOA DON CHUYEN XE =====\n");
        printf("Khoang cach: %.2f km\n", distance_km);
        printf("Cuoc co ban: %.0f VND\n", base_fare);
        printf("Tien phu phi: %.0f VND\n", surcharge);
        printf("Tong chi phi: %.0f VND\n", total_fare);
    }

    return 0;
}
