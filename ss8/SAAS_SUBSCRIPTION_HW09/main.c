#include <stdio.h>

struct UserAccount {
    int user_id;
    char username[50];
    int plan_type;
    int days_overdue;
    int active_devices;
};

int main() {
    struct UserAccount users[100];

    int n;
    int i;
    int total_revenue = 0;
    int downgraded_count = 0;

    /* Nhap so luong tai khoan */
    do {
        printf("Nhap so luong tai khoan (1-100): ");
        scanf("%d", &n);

        if (n < 1 || n > 100) {
            printf("Loi! So luong tai khoan phai tu 1 den 100.\n");
        }
    } while (n < 1 || n > 100);

    /* Nhap thong tin tai khoan */
    for (i = 0; i < n; i++) {
        printf("\n--- Tai khoan %d ---\n", i + 1);

        printf("Nhap ma tai khoan: ");
        scanf("%d", &users[i].user_id);

        printf("Nhap ten tai khoan: ");
        scanf("%49s", users[i].username);

        do {
            printf("Nhap loai goi (1-Free, 2-Personal, 3-Family): ");
            scanf("%d", &users[i].plan_type);

            if (users[i].plan_type < 1 || users[i].plan_type > 3) {
                printf("Loi! Loai goi phai tu 1 den 3.\n");
            }
        } while (users[i].plan_type < 1 || users[i].plan_type > 3);

        do {
            printf("Nhap so ngay no cuoc: ");
            scanf("%d", &users[i].days_overdue);

            if (users[i].days_overdue < 0) {
                printf("Loi! So ngay no khong duoc am.\n");
            }
        } while (users[i].days_overdue < 0);

        do {
            printf("Nhap so thiet bi dang ket noi: ");
            scanf("%d", &users[i].active_devices);

            if (users[i].active_devices < 0) {
                printf("Loi! So thiet bi khong duoc am.\n");
            }
        } while (users[i].active_devices < 0);
    }

    /* Xu ly va tinh doanh thu */
    for (i = 0; i < n; i++) {
        int actual_fee = 0;

        /* Quy tac 1: No cuoc tu 3 ngay tro len */
        if (users[i].days_overdue >= 3) {
            users[i].plan_type = 1;
            actual_fee = 0;
            downgraded_count++;
        } else {
            /* Tinh phi theo goi hien tai */
            if (users[i].plan_type == 1) {
                actual_fee = 0;
            } else if (users[i].plan_type == 2) {
                actual_fee = 120000;

                /* Quy tac 2: Personal vuot qua 1 thiet bi */
                if (users[i].active_devices > 1) {
                    actual_fee += (users[i].active_devices - 1) * 30000;
                }
            } else if (users[i].plan_type == 3) {
                actual_fee = 250000;
            }
        }

        total_revenue += actual_fee;

        /* Tam luu phi thuc thu vao monthly_fee khong co trong struct,
           nen actual_fee duoc tinh va dung de cong doanh thu. */
        printf("");
    }

    /* In bao cao */
    printf("\n=== BAO CAO DOI SOAT TAI KHOAN ===\n");
    printf("%-10s %-15s %-8s %-15s %-12s %-20s\n",
           "MA TK", "TEN TK", "MA GOI", "SO THIET BI",
           "SO NGAY NO", "PHI DICH VU THUC THU");
    printf("-------------------------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        int actual_fee = 0;

        if (users[i].days_overdue >= 3) {
            actual_fee = 0;
        } else if (users[i].plan_type == 1) {
            actual_fee = 0;
        } else if (users[i].plan_type == 2) {
            actual_fee = 120000;

            if (users[i].active_devices > 1) {
                actual_fee += (users[i].active_devices - 1) * 30000;
            }
        } else if (users[i].plan_type == 3) {
            actual_fee = 250000;
        }

        printf("%-10d %-15s %-8d %-15d %-12d %-20d\n",
               users[i].user_id,
               users[i].username,
               users[i].plan_type,
               users[i].active_devices,
               users[i].days_overdue,
               actual_fee);
    }

    printf("-------------------------------------------------------------------------------\n");
    printf("Tong doanh thu thuc thu: %d VND\n", total_revenue);
    printf("Tong so tai khoan bi ha cap: %d\n", downgraded_count);

    return 0;
}
