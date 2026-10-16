
#include <stdio.h>

#define MAX_SHELF_WEIGHT 500.0

typedef struct {
    int pallet_id;
    float weight_kg;
    float temp_celsius;
} PalletItem;

typedef struct {
    int shelf_id;
    int is_cold_storage;
    float current_weight_kg;
} WarehouseShelf;

int kiem_tra_an_toan_nhap_kho(WarehouseShelf shelf, PalletItem item) {
    // 1. Kiem tra nhiet do kho lanh
    if (shelf.is_cold_storage == 1) {
        if (item.temp_celsius < -18.0 ||
            item.temp_celsius > 5.0) {
            printf("[LOI KHO LANH] Nhiet do %.1f C khong dat chuan!\n",
                   item.temp_celsius);
            return 0;
        }
    }

    // 2. Kiem tra tong tai trong sau khi nhap
    if (shelf.current_weight_kg + item.weight_kg >
        MAX_SHELF_WEIGHT) {
        printf("[LOI QUA TAI] Tong tai trong sau khi nhap: %.1f kg!\n",
               shelf.current_weight_kg + item.weight_kg);
        return 0;
    }

    return 1;
}

int main() {
    WarehouseShelf ke_lanh_101 = {101, 1, 400.0};
    PalletItem pallet_moi = {5001, 150.0, 12.0};

    printf("=== HE THONG KIEM DINH AN TOAN KHO HANG ===\n");
    printf("Ma ke: %d | Tai trong hien tai: %.1f kg | Loai kho: %s\n",
           ke_lanh_101.shelf_id,
           ke_lanh_101.current_weight_kg,
           ke_lanh_101.is_cold_storage ? "Kho lanh" : "Kho thuong");

    printf("Ma pallet: %d | Trong luong: %.1f kg | Nhiet do: %.1f C\n",
           pallet_moi.pallet_id,
           pallet_moi.weight_kg,
           pallet_moi.temp_celsius);

    printf("---------------------------------------------\n");

    int ket_qua = kiem_tra_an_toan_nhap_kho(
        ke_lanh_101, pallet_moi
    );

    if (ket_qua == 1) {
        printf("KET QUA: [DUYET] Du dieu kien nhap kho!\n");
    } else {
        printf("KET QUA: [TU CHOI] Vi pham quy dinh an toan!\n");
    }

    return 0;
}

