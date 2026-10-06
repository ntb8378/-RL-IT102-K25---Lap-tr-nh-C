#include <stdio.h>

#define MAX_SIZE 50

int main(void) {
    // B1: Khoi tao các bien, dai luong can thiet
    //                     0    1   2   3   4  5
    int stock[MAX_SIZE] = {10, 25, 30, 15, 40};
    int n = 5;
    int choice;
    int loop = 1;
    int value;
    int pos;
    while (loop == 1) {
        // B2: D?ng khung cho chuong trình menu
        // B2.1: Hi?n th? menu
        printf("=====================================================\n");
        printf("        CHUONG TRINH QUAN LY TON KHO MINIMART        \n");
        printf("=====================================================\n");
        printf("1. Them so luong ton kho\n");
        printf("2. Sua so luong ton kho\n");
        printf("3. Xoa so luong ton kho\n");
        printf("4. Tim kiem so luong ton kho\n");
        printf("0. Thoat chuong trinh\n");
        printf("=====================================================\n");

        // B2.2: Cho ngu?i dùng nh?p vào các s? l?a ch?n d?a vào menu dã du?c hi?n th? ra
        printf("Vui long nhap vao su lua chon cua ban (0 - 4): ");
        scanf("%d", &choice);
        // B2.3: D?a vào s? l?a ch?n c?a ngu?i --> Ði?u hu?ng, r? nhánh chuong trình
        switch(choice) {
            case 1:
                printf("Them ton kho\n");
                printf("Cac phan tu dang co trong mang: \n");
                for (int i = 0; i < n; i++) {
                    printf("%d ", stock[i]);
                }
                if (n == MAX_SIZE) {
                    printf("Mang da day, khong the them phan tu\n");
                    break;
                }
                printf("Moi ban nhap vao gia tri ton kho can them: ");
                scanf("%d", &value);
                if (value < 0) {
                    printf("So luong ton kho khong hop le\n");
                    break;
                }
                printf("Moi ban nhap vao vi tri muon chen (1 - %d): ", n + 1);
                scanf("%d", &pos);
                if (pos < 1 || pos > n + 1) {
                    printf("Vi tri chen khong hop le\n");
                    break;
                }
                for (int i = n; i >= pos; i--) {
                    stock[i] = stock[i - 1];
                }
                stock[pos - 1] = value;
                n++;
                printf("Chen thanh cong\n");
                for (int i = 0; i < n; i++) {
                    printf("%d ", stock[i]);
                }
                break;
            case 2:
                printf("Sua ton kho\n");
                printf("Cac phan tu dang co trong mang: \n");
                for (int i = 0; i < n; i++) {
                    printf("%d ", stock[i]);
                }
                printf("moi ban nhap vi tri can sua: ");
                scanf("%d", &pos);
                if (pos < 1 || pos > n+1){
					printf("vi tri  khong hop le");
					break;
				}
				printf("moi ban nhap so thay the:");
				scanf("%d", &value);
				if (value < 0) {
                    printf("Gia tri khong hop le!\n");
                    break;
                }
                stock[pos-1]=value;
                printf("Sua thanh cong\n");
                for (int i = 0; i < n; i++) {
                    printf("%d ", stock[i]);
                }
                break;
            case 3:
                printf("Xoa ton kho\n");
                printf("Cac phan tu dang co trong mang: \n");
                for (int i = 0; i < n; i++) {
                    printf("%d ", stock[i]);
                }
                printf("nhap vi tri muon xoa");
                scanf("%d", &pos);
                if (pos < 1 || pos > n+1){
					printf("vi tri  khong hop le");
					break;
				}
				for (int i = pos - 1; i < n - 1; i++) {
					stock[i] = stock[i + 1];
				}
				n --;
				printf("xoa thanh cong");
				for (int i=0 ; i< n; i++){
					printf("%d ", stock[i]);
				}
                break;
            case 4:
                printf("Tim kiem ton kho\n");
                printf("Cac phan tu dang co trong mang: \n");
                for (int i = 0; i < n; i++) {
                    printf("%d ", stock[i]);
                }
                printf("Moi ban nhap gia tri can tim (target): ");
                scanf("%d", &value);
                int count = 0;
                int positions[MAX_SIZE];
                
                for (int i = 0; i < n; i++) {
                    if (stock[i] == value) {
                        positions[count] = i + 1; 
                        count++;
                    }
                }
                if (count == 0) {
                    printf("Khong tim thay gia tri trong mang!\n");
                } else {
                    printf("Gia tri can tim : %d\n", value);
                    printf("Vi tri          : ");
                    for (int i = 0; i < count; i++) {
                        printf("%d", positions[i]);
                        if (i < count - 1) printf(", ");
                    }
                    printf("\n");
                    printf("So lan xuat hien: %d\n", count);
                }
                break;
            case 0:
                printf("Thoat\n");
                loop = 0;
                break;
            default:
                printf("Lua chon khong hop le, vui long nhap lai\n");
                break;
        }
    }
    return 0;
}
