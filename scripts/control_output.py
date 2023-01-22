import vgamepad as vg
import mmap
import numpy as np
import time

CPP_FLOAT_SIZE = 4
SHARED_MEMORY_NAME = "sm_control"

print("You have 3s to change windows")
time.sleep(3)
gamepad = vg.VX360Gamepad()
print("Gamepad should be connected")
time.sleep(3)
print("Running...")

if __name__ == "__main__":
    shared_memory = mmap.mmap(-1, 2*CPP_FLOAT_SIZE, SHARED_MEMORY_NAME)
    while (True):
        shared_memory.seek(0)
        buf = shared_memory.read(2*CPP_FLOAT_SIZE)
        acceleration, steering = np.frombuffer(buf, dtype=np.float32)

        # Sanity check
        if (not (-1 <= acceleration <= 1) or not (-1 <= steering <= 1)):
            print(acceleration, steering)
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

        print("acceleration:", acceleration, "steering:", steering)
