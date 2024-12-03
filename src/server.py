from websockets.server import serve
from datetime import datetime
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
        timestamp = f"{current_time.year}/{current_time.month}/{current_time.day} - {current_time.hour}:{current_time.minute}:{current_time.second}"
        with open(f"{self.data_directory}/{username}.txt", 'a+') as file:
            file.write(f"{timestamp} : Message : {message}\n")

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

