from ultralytics import YOLO
import cv2
import serial
import time

# Mở cổng serial tới Arduino
ser = serial.Serial('COM5', 9600)
ser.timeout = 1
time.sleep(2)  # Đợi Arduino sẵn sàng

# Load model YOLO
model = YOLO('yolov8n.pt')
names = model.names

# Load video
video_path = './test.mp4'
cap = cv2.VideoCapture(video_path)

# Biến lưu trạng thái gửi lần trước
previous_mode = ""

# Xử lý khung hình liên tục
while True:
    ret, frame = cap.read()
    if not ret:
        break

    nb = 0
    results = model.predict(frame, verbose=False)
    frame_ = results[0].plot()

    for r in results:
        for c in r.boxes.cls:
            if names[int(c)] in ['car', 'truck', 'motorbike', 'bicycle', 'bus']:
                nb += 1

    if nb >= 3:
        current_mode = 'mode2'
        ser.write(current_mode.encode())
    # Xác định mode hiện tại
    else:
        current_mode = 'mode1'
        ser.write(current_mode.encode())

    # Chỉ gửi nếu có thay đổi
    if current_mode != previous_mode:
        print(f"Sent: {current_mode}")
        previous_mode = current_mode

    # Hiển thị kết quả
    cv2.putText(frame_, f'Vehicles: {nb}', (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 2)
    cv2.imshow('Traffic Detection', frame_)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Dọn tài nguyên
cap.release()
cv2.destroyAllWindows()
ser.close()
