from ultralytics import YOLO
import cv2
import serial

ser = serial.Serial('COM5', 9600)
ser.timeout = 1

# load yolov8 model
model = YOLO('yolov8n.pt')
names = model.names
# load video
video_path = "E:\DATN_24_25/New_folder/test.mp4"
cap = cv2.VideoCapture(0)

ret = True
play = True

# read frames
while ret:
    ret, frame = cap.read()
    nb_car = 0
    if play:
        results = model.predict(frame)
        frame_ = results[0].plot()
        for r in results:
            for c in r.boxes.cls:
                #print(names[int(c)])
                if names[int(c)]=='person':
                    nb_car+=1
        print(nb_car)
        # visualize
        cv2.putText(frame_, 'NB: ' + str(nb_car), (50,50), cv2.FONT_HERSHEY_SIMPLEX,  1, (255, 0, 0) , 2, cv2.LINE_AA)
        cv2.imshow('frame', frame_)
    if nb_car < 3:
        send = 'mode1'
        ser.write(send.encode())
    if nb_car >= 3:
        send = 'mode2'
        ser.write(send.encode())
    key = cv2.waitKey(1)
    if key == ord('c'):
        play = True
    if key == ord('p'):
        play = False
    if key == ord('q'):
        break