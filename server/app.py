from flask import Flask, request, render_template
import datetime
import requests

app = Flask(__name__)
alerts = []

# ======== THÔNG TIN TELEGRAM BOT ========
BOT_TOKEN = '8010685579:AAFywYXWUwnXtem4JkvnH1FjV-I3BVgZ_70'
CHAT_ID = '7929791430'

def send_telegram_message(message):
    url = f"https://api.telegram.org/bot{BOT_TOKEN}/sendMessage"
    payload = {
        'chat_id': CHAT_ID,
        'text': message,
        'parse_mode': 'Markdown'
    }
    try:
        requests.post(url, data=payload)
    except Exception as e:
        print("Lỗi gửi Telegram:", e)

@app.route('/alert', methods=['POST'])
def alert():
    data = request.get_json()
    floor = data.get('floor')
    temperature = float(data.get('temperature', 0))
    smoke = int(data.get('smoke', 0))
    flame = int(data.get('flame', 1))  # 0: Có lửa, 1: Không

    time_str = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    flame_status = "🔥 Có lửa" if flame == 0 else "✅ Bình thường"

    status = {
        'time': time_str,
        'floor': floor,
        'temperature': temperature,
        'smoke': smoke,
        'flame': flame_status
    }

    alerts.append(status)

    # ======= CHỈ GỬI TELEGRAM NẾU CÓ CẢNH BÁO =========
    if flame == 0 or temperature > 50 or smoke > 1000:
        message = (
            f"🚨 *CẢNH BÁO CHÁY*\n"
            f"Tầng: {floor}\n"
            f"Nhiệt độ: {temperature} °C\n"
            f"Khói: {smoke}\n"
            f"Lửa: {flame_status}\n"
            f"🕒 Thời gian: {time_str}"
        )
        send_telegram_message(message)

    return 'Alert received', 200

@app.route('/')
def index():
    return render_template('index.html', alerts=alerts[::-1])

if __name__ == '__main__':
    app.run(host='192.168.11.78', port=5000, debug=True)
