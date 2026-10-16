
#include <stdio.h>

// Dinh nghia cau truc kien hang
typedef struct {
    char ma_kien_hang[20];
    float trong_luong;
    float nhiet_do_yeu_cau;
} PalletItem;

// Dinh nghia cau truc ke kho
typedef struct {
    char ma_ke[20];
    float trong_luong_hien_tai;
    float tai_trong_toi_da;
    int la_kho_lanh;
} WarehouseShelf;

// Kiem tra an toan khi nhap kien hang vao ke kho
// Tra ve 1 neu hop le, 0 neu vi pham
int kiem_tra_nhap_kho(WarehouseShelf ke, PalletItem kien) {
    // Kiem tra tong tai trong
    if (ke.trong_luong_hien_tai + kien.trong_luong >
        ke.tai_trong_toi_da) {
        return 0;
    }

    // Kiem tra nhiet do neu la kho lanh
    if (ke.la_kho_lanh == 1) {
        if (kien.nhiet_do_yeu_cau >= -18.0 &&
            kien.nhiet_do_yeu_cau <= 5.0) {
            return 1;
        } else {
            return 0;
        }
    }

    return 1;
}

// In ket qua kiem tra
void kiem_thu(WarehouseShelf ke, PalletItem kien) {
    printf("\nKe kho: %s | Kien hang: %s\n",
           ke.ma_ke, kien.ma_kien_hang);
    printf("Tai trong hien tai: %.1f kg | Kien moi: %.1f kg\n",
           ke.trong_luong_hien_tai, kien.trong_luong);
    printf("Nhiet do yeu cau: %.1f C\n",
           kien.nhiet_do_yeu_cau);

    int ket_qua = kiem_tra_nhap_kho(ke, kien);

    if (ket_qua == 1) {
        printf("KET QUA: CHO PHEP NHAP KHO!\n");
    } else {
        printf("KET QUA: TU CHOI NHAP KHO (Vi pham an toan)!\n");
    }
}

int main(void) {
    WarehouseShelf ke_lanh = {
        "KE-COLD-01", 350.0, 500.0, 1
    };

    // Test 1: Nhiet do hop le, tong tai trong 450 kg
    PalletItem kien_hop_le = {
        "PL-COLD-01", 100.0, -10.0
    };

    // Test 2: Nhiet do khong hop le
    PalletItem kien_sai_nhiet_do = {
        "PL-DRY-88", 80.0, 25.0
    };

    // Test 3: Tong tai trong 550 kg, vuot gioi han
    PalletItem kien_qua_tai = {
        "PL-HEAVY-01", 200.0, 0.0
    };

    printf("=== KIEM THU HE THONG NHAP KHO ===\n");

    printf("\n--- TEST 1: Kien hang hop le ---");
    kiem_thu(ke_lanh, kien_hop_le);

    printf("\n--- TEST 2: Nhiet do khong hop le ---");
    kiem_thu(ke_lanh, kien_sai_nhiet_do);

    printf("\n--- TEST 3: Vuot tai trong ---");
    kiem_thu(ke_lanh, kien_qua_tai);

    return 0;
}

