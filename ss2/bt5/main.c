```c
#include <stdio.h>

int main(void)
{
    float distance;
    int has_promo;
    float base_fare;
    float total_fare;

    printf("Nhap quang duong (km): ");
    scanf("%f", &distance);

    printf("Nhap trang thai ma giam gia (0-Khong, 1-Co): ");
    scanf("%d", &has_promo);

    // Kiem tra du lieu dau vao
    if (distance <= 0)
    {
        printf("Loi: Du lieu dau vao khong hop le!\n");
        return 0;
    }

    if (has_promo != 0 && has_promo != 1)
    {
        printf("Loi: Du lieu dau vao khong hop le!\n");
        return 0;
    }

    // Tinh cuoc goc
    base_fare = distance * 20000;

    // Ap dung ma giam gia 20%
    if (has_promo == 1)
    {
        total_fare = base_fare * 0.8;
    }
    else
    {
        total_fare = base_fare;
    }

    // Kiem tra cuoc san
    if (total_fare < 15000)
    {
        total_fare = 15000;
    }

    printf("Tong cuoc phi: %.2f VNÐ\n", total_fare);

    return 0;
}
```

### C?u trúc thu m?c

```text
grab_ride_fare_module
+-- main.c
```

B?n ch? c?n t?o thu m?c `grab_ride_fare_module`, t?o file **`main.c`**, r?i copy do?n code trên vào.

