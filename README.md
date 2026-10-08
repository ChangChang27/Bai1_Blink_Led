# ESP32 OneButton LED Control

## 1. Giới thiệu

Đây là dự án điều khiển LED bằng nút nhấn sử dụng ESP32 và thư viện OneButton.

Dự án được phát triển từ chương trình ban đầu có hai chức năng:

* Single click: bật/tắt LED.
* Nhấn giữ lâu hơn 1 giây: LED nhấp nháy.

Sau khi sửa đổi, chức năng nhấn giữ lâu được thay thế bằng **double click**.

Chức năng của chương trình sau khi sửa đổi:

* **Single click:** bật/tắt LED (ON/OFF).
* **Double click:** chuyển LED sang chế độ nhấp nháy.
* Không sử dụng thao tác nhấn giữ lâu để nháy LED.

## 2. Phần cứng

Các linh kiện sử dụng:

* ESP32 DOIT DevKit V1.
* Một LED ngoài.
* Điện trở 1kΩ 
* Một nút nhấn.
* Breadboard và dây nối.

Ví dụ kết nối LED:

```text
GPIO4 ---- Điện trở  1kΩ ---- LED ---- GND
```

Nút nhấn:

```text
GPIO18 ---- Nút nhấn ---- GND
```

## 3. Phần mềm

* Visual Studio Code.
* PlatformIO.
* Arduino Framework.
* Thư viện OneButton.

## 4. Chức năng chương trình

### 4.1. Single click

Khi nhấn nút một lần, hàm `btnPush()` được gọi:

```cpp
void btnPush()
{
    led.flip();
}
```

Hàm `led.flip()` sẽ đảo trạng thái của LED:

* LED đang OFF → chuyển sang ON.
* LED đang ON → chuyển sang OFF.

### 4.2. Double click

Khi nhấn nút hai lần liên tiếp, hàm `btnDoubleClick()` được gọi:

```cpp
void btnDoubleClick()
{
    led.blink(200);
}
```

LED chuyển sang chế độ nhấp nháy với khoảng thời gian 200 ms.

### 4.3. OneButton

Chương trình sử dụng thư viện OneButton để nhận dạng thao tác nhấn nút:

```cpp
button.attachClick(btnPush);
button.attachDoubleClick(btnDoubleClick);
```

| Thao tác     | Hàm xử lý          | Chức năng  |
| ------------ | ------------------ | ---------- |
| Single click | `btnPush()`        | ON/OFF LED |
| Double click | `btnDoubleClick()` | Nháy LED   |

Chức năng long press được loại bỏ.

## 5. Cấu hình nút nhấn

Chương trình sử dụng:

```cpp
button.setClickMs(250);
button.setDebounceMs(50);
```

Trong đó:

* `setClickMs(250)`: thiết lập thời gian nhận dạng thao tác click.
* `setDebounceMs(50)`: chống dội phím trong 50 ms.

Trong vòng lặp chính:

```cpp
button.tick();
```

được gọi liên tục để OneButton cập nhật trạng thái nút.

## 6. So sánh trước và sau khi sửa

### Trước khi sửa

```text
Single click  → ON/OFF
Long press    → Blink
```

### Sau khi sửa

```text
Single click  → ON/OFF
Double click  → Blink
```

Thay đổi chính là sử dụng:

```cpp
button.attachDoubleClick(btnDoubleClick);
```

thay cho chức năng nhấn giữ lâu.

## 7. Serial Monitor

Tốc độ Serial Monitor:

```text
115200 baud
```

Khi single click:

```text
Single click - LED ON/OFF
```

Khi double click:

```text
Double click - LED blink
```

## 8. Build và Upload

Dự án được xây dựng bằng PlatformIO.

Sau khi kết nối ESP32 với máy tính:

1. Nhấn **Build** để biên dịch chương trình.
2. Nhấn **Upload** để nạp chương trình vào ESP32.
3. Mở Serial Monitor với tốc độ 115200 baud để theo dõi hoạt động.

## 9. Git

Khởi tạo Git repository bằng:

```bash
git init
```

Thêm các file vào Git:

```bash
git add .
```

Tạo commit:

```bash
git commit -m "Update OneButton LED double click"
```

## 10. GitHub

Repository được tạo trên GitHub ở chế độ **Public**.

Kết nối repository local với GitHub:

```bash
git remote add origin https://github.com/YOUR_USERNAME/esp32-onebutton-led.git
```

Đổi branch chính thành `main`:

```bash
git branch -M main
```

Push mã nguồn:

```bash
git push -u origin main
```

## 11. Kết quả mong đợi

Sau khi hoàn thành:

* Single click → LED ON/OFF.
* Double click → LED nhấp nháy.
* Không cần giữ nút lâu hơn 1 giây.
* Mã nguồn được quản lý bằng Git.
* Mã nguồn được push lên GitHub.
* Repository GitHub ở chế độ Public.
