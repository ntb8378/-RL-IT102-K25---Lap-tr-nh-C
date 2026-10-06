#include<stdio.h>

#define MAX_SIZE 50

int main(void){
	int choice;
	int stock[MAX_SIZE] = {10, 25, 30, 15, 40};
	int n = 5;
	do{
	printf("1.them so luong ton kho\n2.Sua so luong ton kho\n3.Xoa so luong ton kho\n4.Tim kiem so luong ton kho\n0.Thoat chuong trinh\n");
	printf("moi ban nhap lua chon:\n");
	scanf("%d", &choice);
	switch(choice){
		case 1:
			printf("them so luong\n");
			printf("cac phan tu hien co trong mang");
			for(int i = 0 ; i < n ; i++){
				printf("%d ", &stock[i]);
			}
			break;
		case 2:
			printf("sua so luong\n");
			break;
		case 3:
			printf("Xoa so luong\n");
			break;
		case 4:
			printf("Tim kiem\n");
			break;
		case 0:
			printf("thoat chuong trinh\n");
			break;
		default:
			printf("xin vui long nhap lai\n");
		}
	}while(choice != 0);
	return 0;
}
