from ultralytics import YOLO
import cv2
import serial

ser         = serial.Serial('COM5',9600)
ser.timeout = 1

# load yolov8 model
model       = YOLO('yolov8n.pt')
names       = model.names
# load video
video_path  = './test.mp4'
cap         = cv2.VideoCapture(video_path)

ret         = True
play        = True

# read frames
while ret:
    nb                         = 0
    if play:
        ret, frame             = cap.read()
    results                    = model.predict(frame)
    frame_                     = results[0].plot()
    for r in results:
        for c in r.boxes.cls:
            if ((names[int(c)] == 'car') | \
                (names[int(c)] == 'truck') | \
                (names[int(c)] == 'motobike') | \
                (names[int(c)] == 'bicycle') | \
                (names[int(c)] == 'bus')):
                nb             +=1
    print(nb)
    # visualize
    cv2.putText
    cv2.putText(frame_, 'NB: '+ str(nb), (50,50), cv2.FONT_HERSHEY_SIMPLEX,  1, (255, 0, 0) , 2, cv2.LINE_AA)
    cv2.imshow('frame', frame_)
    if nb <= 3 :
        send = 'mode1'
        ser.write(send.encode())
    if nb > 3 :
        send = 'mode2'
        ser.write(send.encode())
    key=cv2.waitKey(1)
    if key == ord('c'):
        play = True
    if key == ord('p'):
        play = False
    if key == ord('q'):
        break
