#!/usr/bin/env python3

import os
import openai
import argparse
import queue
import sys
import json
import sounddevice as sd

from vosk import Model, KaldiRecognizer
from dotenv import load_dotenv
import pyttsx3

load_dotenv()

class Listener:
    def __init__(self):
        self.q = queue.Queue()

    def int_or_str(self, text):
        """Helper function for argument parsing."""
        try:
            return int(text)
        except ValueError:
            return text

    def callback(self, indata, frames, time, status):
        """This is called (from a separate thread) for each audio block."""
        if status:
            print(status, file=sys.stderr)
        self.q.put(bytes(indata))

    def listen(self):
        parser = argparse.ArgumentParser(add_help=False)
        parser.add_argument("-l", "--list-devices", action="store_true", help="show list of audio devices and exit")
        args, remaining = parser.parse_known_args()
        if args.list_devices:
            print(sd.query_devices())
            parser.exit(0)

        parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter, parents=[parser])
        parser.add_argument("-f", "--filename", type=str, metavar="FILENAME", help="audio file to store recording to")
        parser.add_argument("-d", "--device", type=self.int_or_str, help="input device (numeric ID or substring)")
        parser.add_argument("-r", "--samplerate", type=int, help="sampling rate")
        args = parser.parse_args(remaining)

        try:
            if args.samplerate is None:
                device_info = sd.query_devices(args.device, "input")
                args.samplerate = int(device_info["default_samplerate"])
            model = Model(lang="fr")
            if args.filename:
                dump_fn = open(args.filename, "wb")
            else:
                dump_fn = None

            with sd.RawInputStream(samplerate=args.samplerate, blocksize=1000, device=args.device,
                    dtype="int16", channels=1, callback=self.callback):
                rec = KaldiRecognizer(model, args.samplerate)
                while True:
                    data = self.q.get()
                    if rec.AcceptWaveform(data):
                        spok = json.loads(rec.FinalResult())
                        return spok['text']
                    if dump_fn is not None:
                        dump_fn.write(data)

        except KeyboardInterrupt:
            print("\nDone")
            parser.exit(0)
        except Exception as e:
            parser.exit(type(e).__name__ + ": " + str(e))

class Sender:
    def __init__(self):
        self.history = []
        openai.api_key = os.getenv("OPENAI_API_KEY")

    def check_query(self, query):
        if "dernière page" in query and self.history is not None:
            return self.history[-1]
        else:
            return query

    def send(self, query):
        query = self.check_query(query)
        response = openai.Completion.create(
            model="text-davinci-003",
            prompt=query,
            temperature=1.0,
            max_tokens=4000,
        )
        return response.choices[0].text

class Speaker:
    def __init__(self):
        self.engine = pyttsx3.init()
        self.engine.say('Hello.')
        self.engine.runAndWait()

    def speak(self, str):
        self.engine.say(str)
        self.engine.runAndWait()

if __name__ == "__main__":
    speaker = Speaker()
    listener = Listener()
    sender = Sender()

    while True:
        request = listener.listen()
        if request is None:
            continue
        print("Me : " + request + " ? You : ")
        response = sender.send("Me : " + request + " ? You : ")
        if response == None or response == "":
            continue
        print(response)
        speaker.speak(response)
