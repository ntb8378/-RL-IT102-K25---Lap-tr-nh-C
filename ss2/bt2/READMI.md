Bước 1: Nhập vehicle_type, distance, is_peak_or_rain.

Bước 2: Kiểm tra distance.
Nếu distance <= 0 hoặc distance > 300 thì báo lỗi và dừng.

Bước 3: Kiểm tra vehicle_type.
Nếu vehicle_type khác 1 và 2 thì báo lỗi và dừng.

Bước 4: Kiểm tra is_peak_or_rain.
Nếu khác 0 và 1 thì báo lỗi và dừng.

Bước 5: Nếu vehicle_type = 1:
    Nếu distance <= 2:
        base_fare = 12000
    Ngược lại:
        base_fare = 12000 + (distance - 2) * 4500

Bước 6: Nếu vehicle_type = 2:
    Nếu distance <= 2:
        base_fare = 25000
    Ngược lại:
        base_fare = 25000 + (distance - 2) * 10000

Bước 7: Nếu is_peak_or_rain = 1:
    surcharge = base_fare * 0.2
    Ngược lại:
    surcharge = 0

Bước 8:
    total_fare = base_fare + surcharge

Bước 9: In kết quả.