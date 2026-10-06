#include <stdio.h>

#define MAX 100

struct Subscription {
    int sub_id;
    char plan_name[31];
    float monthly_fee;
    int user_limit;
};

int main(void) {
    struct Subscription subscriptions[MAX];

    int n;
    float total_revenue = 0;

    /*
     * Nhap so luong goi dich vu
     */
    printf("Nhap so luong goi dich vu: ");
    scanf("%d", &n);

    /*
     * Kiem tra so luong goi dich vu
     * N phai nam trong khoang tu 1 den 100
     */
    if (n <= 0 || n > MAX) {
        printf("So luong goi dich vu khong hop le!\n");
        return 0;
    }

    /*
     * Nhap thong tin tung goi dich vu
     */
    for (int i = 0; i < n; i++) {
        printf("\nNhap thong tin goi thu %d:\n", i + 1);

        printf("Ma goi: ");
        scanf("%d", &subscriptions[i].sub_id);

        printf("Ten goi: ");
        scanf("%30s", subscriptions[i].plan_name);

        printf("Cuoc phi hang thang (USD): ");
        scanf("%f", &subscriptions[i].monthly_fee);

        printf("Gioi han user: ");
        scanf("%d", &subscriptions[i].user_limit);

        /*
         * Cong don doanh thu hang thang
         */
        total_revenue += subscriptions[i].monthly_fee;
    }

    /*
     * In bang danh sach cac goi dich vu
     */
    printf("\n");
    printf("===============================================================\n");
    printf("%-10s %-20s %-18s %-15s\n",
           "MA GOI",
           "TEN GOI",
           "CUOC PHI (USD)",
           "GIOI HAN USER");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("%-10d %-20s %-18.2f %-15d\n",
               subscriptions[i].sub_id,
               subscriptions[i].plan_name,
               subscriptions[i].monthly_fee,
               subscriptions[i].user_limit);
    }

    printf("---------------------------------------------------------------\n");

    /*
     * In tong doanh thu hang thang
     */
    printf("TONG DOANH THU HANG THANG: %.2f USD\n", total_revenue);

    return 0;
}
