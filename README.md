## Overview
This repository contains a sophisticated keylogger programmed in Python and C++. The keylogger is designed to operate seamlessly across various operating systems, including Windows and Linux.

## Features
- **Cross-Platform Compatibility**: Works on multiple operating systems.
- **Responsive Design**: Fully responsive interface for ease of use.
- **Telegram Integration**: Sends logged keystrokes via a Telegram bot.
- **WebSocket Communication**: Utilizes Python for real-time data transmission.
- **Self-Metling**: The keylogger hides itself in a directory with a 16-character name in the C:\ directory.
- **Startup Integration**: Automatically adds itself to the system startup via the registry.
- **Inline Panel**: Displays targets and allows selection for log transmission.

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/keylogger.git
2. Navigate to the project directory:
   ```bash
   cd keylogger
3. Install required Python packages:
  ```
  pyrogram
  tgcrypto
  datetime
  websocket
  ```
4. Compile the C++ Project for the OS that you want.

### Code Structure
- C++ Keylogger: Responsible for capturing keystrokes.
- Python WebSocket: Handles real-time communication.
- Python Telegram Bot: Sends logs to the specified Telegram chat.

### Contributing
- Contributions are welcome! Please fork the repository and submit a pull request.

### License
This project is licensed under the MIT License - see the LICENSE file for details.

### Disclaimer
This software is intended for educational purposes only. Use responsibly and ensure compliance with local laws and regulations. 🚨
