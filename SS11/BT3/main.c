
#include <stdio.h>

#define TAI_TRONG_TOI_DA 500.0
#define NHIET_DO_MIN (-18.0)
#define NHIET_DO_MAX 5.0

// Kiem tra dieu kien nhap pallet vao kho lanh
// Tra ve 1 neu hop le, 0 neu vi pham
int kiem_tra_nhap_kho_lanh(float khoi_luong_pallet,
                           float nhiet_do_bao_quan,
                           float tai_trong_hien_tai) {
    // Kiem tra tong tai trong sau khi nhap pallet
    if (tai_trong_hien_tai + khoi_luong_pallet >
        TAI_TRONG_TOI_DA) {
        printf("Loi: Tai trong vuot qua muc cho phep (Toi da %.1f kg)!\n",
               TAI_TRONG_TOI_DA);
        return 0;
    }

    // Nhiet do phai dong thoi >= -18 do C va <= 5 do C.
    // Dung && thay cho || de dam bao nam trong ca hai gioi han.
    if (nhiet_do_bao_quan >= NHIET_DO_MIN &&
        nhiet_do_bao_quan <= NHIET_DO_MAX) {
        return 1;
    } else {
        printf("Loi: Nhiet do bao quan %.1f do C khong phu hop kho lanh!\n",
               nhiet_do_bao_quan);
        return 0;
    }
}

int main(void) {
    float tai_trong_hien_tai = 320.0;
    float khoi_luong_pallet;
    float nhiet_do_bao_quan;

    printf("=== HE THONG KIEM DINH NHAP KHO LANH SMARTLOG ===\n");
    printf("Tai trong hien tai: %.1f kg / %.1f kg\n\n",
           tai_trong_hien_tai, TAI_TRONG_TOI_DA);

    printf("Nhap khoi luong pallet (kg): ");
    if (scanf("%f", &khoi_luong_pallet) != 1 ||
        khoi_luong_pallet <= 0.0f) {
        printf("Loi: Khoi luong pallet khong hop le!\n");
        return 1;
    }

    printf("Nhap nhiet do bao quan (do C): ");
    if (scanf("%f", &nhiet_do_bao_quan) != 1) {
        printf("Loi: Nhiet do khong hop le!\n");
        return 1;
    }

    int ket_qua = kiem_tra_nhap_kho_lanh(
        khoi_luong_pallet,
        nhiet_do_bao_quan,
        tai_trong_hien_tai
    );

    if (ket_qua == 1) {
        tai_trong_hien_tai += khoi_luong_pallet;
        printf("\n=> PHE DUYET: Nhap kho thanh cong!\n");
        printf("Tai trong sau khi nhap: %.1f kg\n",
               tai_trong_hien_tai);
    } else {
        printf("\n=> TU CHOI: Kien hang khong du dieu kien!\n");
        printf("Tai trong ke kho giu nguyen: %.1f kg\n",
               tai_trong_hien_tai);
    }

    return 0;
}

