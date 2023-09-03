import vgamepad as vg
import numpy as np
import time
import socket
import json


HOST = '0.0.0.0'
PORT = 5006
BUFFER_SIZE = 1024


if __name__ == '__main__':
    print('You have 3s to change windows')
    time.sleep(3)
    gamepad = vg.VX360Gamepad()
    print('Gamepad should be connected')
    time.sleep(3)
    print('Running...')

    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        s.bind((HOST, PORT))
        while (True):
            try:
                received_data = json.loads(s.recvfrom(BUFFER_SIZE)[0].decode('utf-8'))
            except:
                continue

            if (not ('acceleration' in received_data and 'steering' in received_data)):
                continue
            acceleration = received_data['acceleration']
            steering = received_data['steering']

            # Sanity check
            if (not ((-1 <= acceleration <= 1) or (-1 <= steering <= 1))):
                continue
            acceleration = float(acceleration)
            steering = float(steering)

            if (acceleration < 0):
                gamepad.right_trigger_float(0)
                gamepad.left_trigger_float(abs(acceleration))
            else:
                gamepad.right_trigger_float(acceleration)
                gamepad.left_trigger_float(0)

            gamepad.left_joystick_float(steering, 0)

            gamepad.update()

            print('acceleration:', acceleration, 'steering:', steering)
