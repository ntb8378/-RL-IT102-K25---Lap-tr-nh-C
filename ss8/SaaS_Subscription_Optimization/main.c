#include <stdio.h>

#define MAX 100

struct UserAccount {
    int account_id;
    int plan_type;
    int monthly_fee;
    int remaining_days;
    int active_devices;
};

int main(void) {
    struct UserAccount users[MAX];
    struct UserAccount active[MAX];
    struct UserAccount free_accounts[MAX];

    int n;
    int active_count = 0;
    int free_count = 0;

    long long mrr_before = 0;
    long long mrr_after = 0;

    printf("Nhap so luong tai khoan: ");
    scanf("%d", &n);

    /* Nhap danh sach tai khoan */
    for (int i = 0; i < n; i++) {
        printf("\nTai khoan %d\n", i + 1);

        printf("Account ID: ");
        scanf("%d", &users[i].account_id);

        printf("Plan type (0-Free, 1-Standard, 2-Premium): ");
        scanf("%d", &users[i].plan_type);

        printf("Monthly fee: ");
        scanf("%d", &users[i].monthly_fee);

        printf("Remaining days: ");
        scanf("%d", &users[i].remaining_days);

        printf("Active devices: ");
        scanf("%d", &users[i].active_devices);

        /*
         * MRR truoc kiem toan:
         * Lay monthly_fee tu du lieu ban dau.
         */
        mrr_before += users[i].monthly_fee;
    }

    /*
     * =========================================================
     * BUOC 1: KIEM TOAN VA CHUAN HOA DU LIEU
     * =========================================================
     */
    for (int i = 0; i < n; i++) {

        /* Neu so thiet bi <= 0 thi dua ve toi thieu 1 */
        if (users[i].active_devices <= 0) {
            users[i].active_devices = 1;
        }

        /*
         * QUY TAC HET HAN:
         * remaining_days <= 0
         * => ha cap ve Free
         * => monthly_fee = 0
         */
        if (users[i].remaining_days <= 0) {

            users[i].plan_type = 0;
            users[i].monthly_fee = 0;

            /*
             * Goi Free cho phep toi da 1 thiet bi.
             */
            if (users[i].active_devices > 1) {
                users[i].active_devices = 1;
            }

        } else {

            /*
             * Tai khoan chua het han.
             * Chuan hoa monthly_fee theo plan_type.
             */

            if (users[i].plan_type == 0) {

                users[i].monthly_fee = 0;

                /* Free toi da 1 thiet bi */
                if (users[i].active_devices > 1) {
                    users[i].active_devices = 1;
                }

            } else if (users[i].plan_type == 1) {

                users[i].monthly_fee = 120000;

                /* Standard toi da 2 thiet bi */
                if (users[i].active_devices > 2) {
                    users[i].active_devices = 2;
                }

            } else if (users[i].plan_type == 2) {

                users[i].monthly_fee = 300000;

                /* Premium toi da 5 thiet bi */
                if (users[i].active_devices > 5) {
                    users[i].active_devices = 5;
                }

            } else {

                /*
                 * Neu plan_type khong hop le,
                 * dua ve Free de dam bao du lieu hop le.
                 */
                users[i].plan_type = 0;
                users[i].monthly_fee = 0;

                if (users[i].active_devices > 1) {
                    users[i].active_devices = 1;
                }
            }
        }

        /* Tinh MRR sau khi kiem toan */
        mrr_after += users[i].monthly_fee;
    }

    /*
     * =========================================================
     * BUOC 2: CHIA THANH 2 NHOM
     *
     * active[]       : tai khoan tra phi
     * free_accounts[]: Free / bi ha cap
     * =========================================================
     */
    for (int i = 0; i < n; i++) {

        if (users[i].plan_type > 0) {
            active[active_count] = users[i];
            active_count++;
        } else {
            free_accounts[free_count] = users[i];
            free_count++;
        }
    }

    /*
     * =========================================================
     * BUOC 3: SAP XEP NHOM ACTIVE
     *
     * Sap xep monthly_fee giam dan.
     *
     * Su dung insertion sort.
     *
     * Quan trong:
     * Chi dich cac phan tu co monthly_fee nho hon.
     * Neu bang nhau thi khong dich.
     * => giu nguyen thu tu ban dau (STABLE).
     * =========================================================
     */
    for (int i = 1; i < active_count; i++) {

        struct UserAccount temp = active[i];

        int j = i - 1;

        while (j >= 0 && active[j].monthly_fee < temp.monthly_fee) {
            active[j + 1] = active[j];
            j--;
        }

        active[j + 1] = temp;
    }

    /*
     * =========================================================
     * BUOC 4: GHEP LAI MANG CHINH
     *
     * Active dat truoc
     * Free dat sau
     * =========================================================
     */
    int index = 0;

    for (int i = 0; i < active_count; i++) {
        users[index] = active[i];
        index++;
    }

    for (int i = 0; i < free_count; i++) {
        users[index] = free_accounts[i];
        index++;
    }

    /*
     * =========================================================
     * BUOC 5: IN KET QUA KIEM TOAN
     * =========================================================
     */

    printf("\n===============================================================\n");
    printf("              KET QUA KIEM TOAN TAI KHOAN\n");
    printf("===============================================================\n");

    printf("%-10s %-10s %-15s %-15s %-15s\n",
           "ID",
           "Plan",
           "Monthly Fee",
           "Remain Days",
           "Devices");

    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {

        printf("%-10d %-10d %-15d %-15d %-15d\n",
               users[i].account_id,
               users[i].plan_type,
               users[i].monthly_fee,
               users[i].remaining_days,
               users[i].active_devices);
    }

    printf("===============================================================\n");

    /*
     * =========================================================
     * BUOC 6: BAO CAO MRR
     * =========================================================
     */

    printf("\nBAO CAO DOANH THU MRR\n");
    printf("------------------------------\n");
    printf("MRR truoc kiem toan : %lld VND\n", mrr_before);
    printf("MRR sau kiem toan   : %lld VND\n", mrr_after);
    printf("Chenh lech MRR      : %lld VND\n",
           mrr_after - mrr_before);

    if (mrr_after < mrr_before) {
        printf("=> MRR giam sau khi kiem toan.\n");
    } else if (mrr_after > mrr_before) {
        printf("=> MRR tang sau khi kiem toan.\n");
    } else {
        printf("=> MRR khong thay doi.\n");
    }

    printf("\nSo tai khoan Active : %d\n", active_count);
    printf("So tai khoan Free   : %d\n", free_count);

    return 0;
}
