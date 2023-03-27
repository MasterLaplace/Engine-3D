#! Installer un model fr depuis : https://alphacephei.com/vosk/models

case $(uname | tr '[:upper:]' '[:lower:]') in
  linux*)
    sudo apt-get install libportaudio2
    sudo apt install espeak
    sudo apt install python3-pyaudio
    sudo apt install python3-devel
    ;;
  msys*)
    echo "windows";;
  *)
    echo "Unknown platform";;
esac

# Installation des modules
python3 -m pip install sounddevice
pip3 install vosk
python3 -m pip install requests
pip3 install beautifulsoup4
pip3 install google
pip3 install pyttsx3
pip3 install pyaudio
pip3 install openia
echo "pip install -r requirements.txt"
