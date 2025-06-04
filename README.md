Cảnh báo cháy cho các tòa nhà cao tầng

Hệ thống cảnh báo cháy thông minh được thiết kế để phát hiện và cảnh báo sớm các rủi ro cháy nổ trong không gian sống hoặc làm việc. Dựa trên dữ liệu từ cảm biến khói, nhiệt độ và lửa, hệ thống gửi cảnh báo trực tiếp đến người dùng thông qua giao diện web và Telegram.

Mục tiêu của đề tài là mô phỏng một hệ thống giám sát cháy đơn giản, giá thành thấp nhưng có độ tin cậy cao, có thể áp dụng trong gia đình, văn phòng hoặc trường học.
CÔNG NGHỆ SỬ DỤNG
-ESP32 (NodeMCU): dùng để thu thập dữ liệu từ các cảm biến và gửi đến server.

-Cảm biến MQ-2: phát hiện mức độ khói trong không khí.

-Cảm biến nhiệt độ DHT22: đo nhiệt độ môi trường.

-Cảm biến lửa: phát hiện ánh sáng lửa trực tiếp.

-Python Flask: dùng để xây dựng server nhận dữ liệu và xử lý cảnh báo.

-Telegram Bot API: gửi tin nhắn cảnh báo tự động khi có cháy.

-HTML (Flask template): giao diện hiển thị dữ liệu cảnh báo.
