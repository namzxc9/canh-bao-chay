CẢNH BÁO CHÁY CHO CÁC TÒA NHÀ CAO TẦNG

Hệ thống cảnh báo cháy thông minh được thiết kế để phát hiện và cảnh báo sớm các rủi ro cháy nổ trong không gian sống hoặc làm việc. Dựa trên dữ liệu từ cảm biến khói, nhiệt độ và lửa, hệ thống gửi cảnh báo trực tiếp đến người dùng thông qua giao diện web và Telegram.

Mục tiêu của đề tài là mô phỏng một hệ thống giám sát cháy đơn giản, giá thành thấp nhưng có độ tin cậy cao, có thể áp dụng trong gia đình, văn phòng hoặc trường học.

CÔNG NGHỆ SỬ DỤNG

- Cảm biến khói (MQ-2): Phát hiện khí gas, khói và hơi dễ cháy trong môi trường. Dữ liệu trả về là mức khói tương đối (analog).

- Cảm biến nhiệt độ DHT22: Đo nhiệt độ môi trường xung quanh, gửi dữ liệu về vi điều khiển.

- Cảm biến lửa (flame sensor): Phát hiện ánh sáng từ ngọn lửa trong vùng nhìn thấy, phản hồi mức HIGH/LOW.

- Vi điều khiển (ESP32 - NodeMCU): Điều khiển trung tâm, đọc dữ liệu từ cảm biến, kết nối Wi-Fi và gửi dữ liệu về server Flask qua HTTP.

- Server Flask (Python): Tiếp nhận dữ liệu từ ESP8266, hiển thị cảnh báo trên giao diện web và gửi cảnh báo Telegram nếu cần.

- Telegram Bot API: Tự động gửi tin nhắn đến người dùng khi phát hiện cháy.

- Giao diện web (HTML, Flask): Hiển thị dữ liệu cảnh báo theo thời gian thực gồm tầng, thời gian, nhiệt độ, khói và tình trạng lửa.

- Nguồn điện: ESP32 sử dụng nguồn 5V (USB hoặc pin dự phòng), hoạt động độc lập.


🔁 Chu trình hoạt động cơ bản
Khởi động hệ thống:

ESP32 kết nối Wi-Fi, khởi tạo các chân kết nối cảm biến và xác định địa chỉ IP server Flask.

Đọc dữ liệu cảm biến:
ESP32 định kỳ đọc:

- Mức nhiệt độ từ cảm biến DHT22.

- Mức khói từ MQ-2 (giá trị analog).

- Tình trạng lửa từ cảm biến flame (LOW = có lửa).

Gửi dữ liệu về server:
ESP32 tạo một gói JSON chứa: tầng, nhiệt độ, khói, lửa → gửi qua HTTP POST đến Flask server.

Xử lý tại server Flask:
Flask nhận dữ liệu, ghi lại thời gian và nội dung cảnh báo. Nếu có điều kiện nguy hiểm xảy ra (nhiệt độ > 50°C, khói > 1000, hoặc có lửa), hệ thống sẽ:

Gửi tin nhắn cảnh báo ngay đến Telegram.

Hiển thị thông tin cảnh báo trên giao diện web.

Hiển thị trên giao diện:
Trang web hiển thị thông tin cảnh báo gần nhất dưới dạng bảng, cập nhật tự động mỗi lần có dữ liệu mới.

Lặp lại chu trình:
ESP32 tiếp tục đo, gửi dữ liệu mỗi vài giây, hệ thống luôn hoạt động trong thời gian thực.
