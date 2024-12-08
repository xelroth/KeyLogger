# -*- coding: utf-8 -*-
#!/usr/bin/env python3

from socket import gethostbyname, gethostname
from websockets.server import serve
from datetime import datetime
from platform import uname, node
import subprocess
import requests
import asyncio
import os

class WebSocketServer:
    def __init__(self, host='0.0.0.0', port=8989):
        self.host = host
        self.port = port
        self.data_directory = "data"
        os.makedirs(self.data_directory, exist_ok=True)

    def __WriteDataToUserFile__(self, username, message):
        current_time = datetime.now()
        ip_info = requests.get("http://ip-api.com/json").json()
        timestamp = f"{current_time.year}/{current_time.month}/{current_time.day} - {current_time.hour}:{current_time.minute}:{current_time.second}"

        with open(f"{self.data_directory}/{username}.txt", 'a+') as file:
            file.write(
                f"\n 🌟 -------- Session Started -------- 🌟 \n" \
                f"🖥 HWID: {subprocess.Popen('dmidecode.exe -s system-uuid'.split()) if "nt" in os.name else subprocess.Popen('hal-get-property --udi /org/freedesktop/Hal/devices/computer --key system.hardware.uuid'.split())}\n" \
                f"💻 Computer Name: {node()}\n" \
                f"🖥️ OS: {uname()[0]}" \
                f"⌨️ OS Version: {uname()[2]}\n" \
                f"IP 🌍 : {ip_info['query']}\n" \
                f"Country ⛰ : {ip_info['country']}\n" \
                f"City 🏠 : {ip_info['city']}\n" \
                f"TimeZone 🧭 : {ip_info['timezone']}\n" \
                f"ISP 📡 : {ip_info['isp']}\n" \
                f"Local IP 🌐 :* {gethostbyname(gethostname())}\n" \
                f"➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖"
                f"{timestamp} : 📝 Message : {message}\n"
            )

    async def __EchoMessage__(self, websocket):
        async for message in websocket:
            ip, port = websocket.remote_address
            self.__WriteDataToUserFile__(ip, (str(message)))

    async def __StartServer__(self):
        async with serve(self.__EchoMessage__, self.host, self.port):
            await asyncio.Future()

    def run(self):
        asyncio.run(self.__StartServer__())

if __name__ == "__main__":
    server = WebSocketServer()
    server.run()
