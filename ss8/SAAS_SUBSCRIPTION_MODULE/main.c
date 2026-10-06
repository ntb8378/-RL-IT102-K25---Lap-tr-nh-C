#include <stdio.h>
#include <string.h>

#define MAX 50

struct Subscription {
    int user_id;
    char account_name[31];
    int plan_type;
    int active_devices;
    int max_devices;
    int days_overdue;
    int account_status;
};

int main(void) {
    struct Subscription users[MAX];

    int n;
    int downgraded_count = 0;
    int violation_count = 0;

    printf("=============================================\n");
    printf("     STREAMFLIX - SUBSCRIPTION AUDITOR\n");
    printf("=============================================\n");

    printf("Nhap so luong tai khoan (1-%d): ", MAX);
    scanf("%d", &n);

    /* Kiem tra so luong tai khoan */
    if (n < 1 || n > MAX) {
        printf("Loi: So luong tai khoan khong hop le!\n");
        return 0;
    }

    /*
     * =====================================================
     * BUOC 1: NHAP DU LIEU
     * =====================================================
     */
    for (int i = 0; i < n; i++) {
        printf("\n--- Tai khoan %d ---\n", i + 1);

        printf("User ID: ");
        scanf("%d", &users[i].user_id);

        printf("Account Name: ");
        scanf("%30s", users[i].account_name);

        printf("Plan Type (1-Free, 2-Individual, 3-Family): ");
        scanf("%d", &users[i].plan_type);

        printf("Active Devices: ");
        scanf("%d", &users[i].active_devices);

        printf("Days Overdue: ");
        scanf("%d", &users[i].days_overdue);

        /*
         * =================================================
         * BUOC 2: XAC DINH SO THIET BI TOI DA
         *
         * Free       -> 1 thiet bi
         * Individual -> 1 thiet bi
         * Family     -> 5 thiet bi
         * =================================================
         */
        if (users[i].plan_type == 1) {
            users[i].max_devices = 1;
        } 
        else if (users[i].plan_type == 2) {
            users[i].max_devices = 1;
        } 
        else if (users[i].plan_type == 3) {
            users[i].max_devices = 5;
        } 
        else {
            /*
             * Neu nhap plan khong hop le,
             * dua ve Free.
             */
            users[i].plan_type = 1;
            users[i].max_devices = 1;
        }

        /*
         * Mac dinh tai khoan dang Active.
         */
        users[i].account_status = 1;
    }

    /*
     * =====================================================
     * BUOC 3: XU LY BUSINESS RULE
     *
     * Neu days_overdue > 3:
     * - Ha cap ve Free
     * - plan_type = 1
     * - max_devices = 1
     * - account_status = 0
     * =====================================================
     */
    for (int i = 0; i < n; i++) {

        if (users[i].days_overdue > 3) {

            users[i].plan_type = 1;
            users[i].max_devices = 1;
            users[i].account_status = 0;

            downgraded_count++;
        }
    }

    /*
     * =====================================================
     * BUOC 4: KIEM TRA VI PHAM THIET BI
     *
     * Phai kiem tra SAU KHI ha cap.
     * Vi du:
     * Family co 5 thiet bi -> khong vi pham.
     * Nhung neu bi ha cap ve Free:
     * max_devices = 1
     * active_devices = 4
     * => vi pham.
     * =====================================================
     */
    for (int i = 0; i < n; i++) {

        if (users[i].active_devices > users[i].max_devices) {
            violation_count++;
        }
    }

    /*
     * =====================================================
     * BUOC 5: XUAT BANG BAO CAO
     * =====================================================
     */

    printf("\n\n");
    printf("==========================================================================\n");
    printf("                    BAO CAO RA SOAT TAI KHOAN\n");
    printf("==========================================================================\n");

    printf("%-8s %-20s %-12s %-12s %-12s %-12s\n",
           "ID",
           "Account Name",
           "Plan",
           "Devices",
           "Overdue",
           "Status");

    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {

        char plan_name[15];
        char status_name[15];

        /*
         * Hien thi ten goi thay vi chi hien thi so.
         */
        if (users[i].plan_type == 1) {
            strcpy(plan_name, "Free");
        } 
        else if (users[i].plan_type == 2) {
            strcpy(plan_name, "Individual");
        } 
        else {
            strcpy(plan_name, "Family");
        }

        /*
         * Hien thi trang thai tai khoan.
         */
        if (users[i].account_status == 1) {
            strcpy(status_name, "Active");
        } 
        else {
            strcpy(status_name, "Downgraded");
        }

        printf("%-8d %-20s %-12s %d/%-8d %-12d %-12s\n",
               users[i].user_id,
               users[i].account_name,
               plan_name,
               users[i].active_devices,
               users[i].max_devices,
               users[i].days_overdue,
               status_name);
    }

    printf("==========================================================================\n");

    /*
     * =====================================================
     * BUOC 6: BAO CAO THONG KE VAN HANH
     * =====================================================
     */

    printf("\n");
    printf("=============================================\n");
    printf("       BAO CAO THONG KE VAN HANH\n");
    printf("=============================================\n");

    printf("Tong so tai khoan da ra soat       : %d\n", n);

    printf("So tai khoan bi ha cap ve Free     : %d\n",
           downgraded_count);

    printf("So tai khoan vi pham thiet bi      : %d\n",
           violation_count);

    printf("=============================================\n");

    return 0;

