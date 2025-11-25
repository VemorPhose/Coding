import pyautogui
import time
import pygetwindow as gw
import sys
import random # Imported for generating random intervals

# --- Configuration ---
# You must change this to the exact name of the window title of the app you want to switch to.
# Example: 'Untitled - Notepad', 'Mozilla Firefox', 'Google Chrome'
TARGET_WINDOW_TITLE = 'EVE - Vemor Phose'
INITIAL_WAIT_TIME = 2  # Seconds to wait after focusing and after clicking

# Set a very small pause between all pyautogui commands for stability
# This can sometimes resolve key registration issues.
pyautogui.PAUSE = 0.01 

def find_and_focus_app(title):
    """
    Finds and activates the specified window by its title.
    """
    try:
        # Find all windows that match the title (case-insensitive)
        windows = gw.getWindowsWithTitle(title)
        if not windows:
            print(f"Error: Could not find any window with title matching '{title}'.")
            print("Please ensure the application is open and the title is exactly correct.")
            sys.exit(1)

        # Use the first found window
        target_window = windows[0]

        # Activate (focus) the window
        target_window.activate()
        print(f"Successfully focused window: {target_window.title}")

        return target_window

    except Exception as e:
        print(f"An error occurred during window focusing: {e}")
        sys.exit(1)

def perform_initial_click(window):
    """
    Performs a single left-click in the center of the provided window.
    """
    # Calculate the center coordinates relative to the screen
    center_x = window.left + window.width // 2
    center_y = window.top + window.height // 2

    # Move mouse and click
    pyautogui.click(center_x, center_y)
    print(f"Performed left click at center of window ({center_x}, {center_y})")

def perform_key_combination():
    """
    Manually presses the generic Ctrl, then /, then releases Ctrl quickly.
    Using 'ctrl' (generic) instead of 'rightctrl' is often necessary for games.
    """
    print("Executing manual 'Ctrl + /' sequence...")
    try:
        # 1. Press and hold generic Ctrl key
        pyautogui.keyDown('ctrl')
        
        # 2. Press '/' (while Ctrl is still down)
        pyautogui.press('/')
        
        # 3. Release Ctrl (clean up)
        pyautogui.keyUp('ctrl')
        
        print("Key combination executed successfully.")
    except Exception as e:
        print(f"Error during key press: {e}")


def main():
    print("--- Starting Windows Automation Script ---")
    print("WARNING: You must physically move your mouse or use Ctrl+C to stop the script!")

    # 1. Find and focus the target application
    target_window = find_and_focus_app(TARGET_WINDOW_TITLE)

    # 2. Wait 2 seconds
    time.sleep(INITIAL_WAIT_TIME)

    # 3. Left click center of screen (relative to the focused window)
    perform_initial_click(target_window)

    # 4. Wait 2 seconds
    time.sleep(INITIAL_WAIT_TIME)

    # 5. Start the infinite loop
    while True:
        start_time = time.time()
        
        # Perform the key combination
        perform_key_combination()

        # Generate a random target interval between 25 and 35 seconds
        random_interval = random.uniform(25, 35)

        # Calculate time spent and the remaining time to sleep
        elapsed_time = time.time() - start_time
        sleep_duration = random_interval - elapsed_time

        if sleep_duration > 0:
            print(f"Waiting for {sleep_duration:.2f} seconds (Target: {random_interval:.2f}s) until next key press...")
            time.sleep(sleep_duration)
        else:
            print(f"Warning: Automation loop is running too slow to maintain the {random_interval:.2f}-second interval.")


if __name__ == "__main__":
    main()