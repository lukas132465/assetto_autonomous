import vgamepad as vg
import time

# ToDo: Multithreading

time.sleep(3)
gamepad = vg.VX360Gamepad()
time.sleep(3)
print("Running")


while (True):
    with open("C:\\Users\\lukas\\Documents\\Projects\\autonomous-racing\\DataTransfer\\SharedData\\shared_data_linux_to_windows.txt", 'r') as f:
        lines = f.readlines()
        if (len(lines) != 3):
            continue
        acceleration, steering, _ = lines
        acceleration = acceleration[:-1]
        steering = steering[:-1]
        
        key, value_acceleration = acceleration.split(' ')
        value_acceleration = float(value_acceleration)
        # Sanity check
        if (not (0<=value_acceleration<=1) and not (key == "acceleration")):
            continue
        

        key, value_steering = steering.split(' ')
        value_steering = float(value_steering)
        # Sanity check
        if (not (-1<=value_steering<=1) and not (key == "steering")):
            continue


        if (value_acceleration < 0):
            gamepad.right_trigger_float(0)
            gamepad.left_trigger_float(abs(value_acceleration))
        else:
            gamepad.right_trigger_float(value_acceleration)
            gamepad.left_trigger_float(0)
        
        gamepad.left_joystick_float(value_steering, 0)

        gamepad.update()
        print("acceleration:", value_acceleration, "steering:", value_steering)
