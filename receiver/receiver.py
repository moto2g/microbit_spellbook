import radio
import speech
from microbit import *
import music

radio.on()
display.show(Image.YES)

def play_speech(spell):
    speech.say(spell, pitch=40, speed=75, mouth=120, throat=180)

def play_sfx():
    # ド・レ♯・ド♯・ミ・レ・ファ・ファ♯
    speech_set = [
        "#28PIYIY",
        "#25ROHOH",
        "#28RIYIY",
        "#23ROHOH",
        "#26PIYIY",
        "#22ROHOH",
        "#21ROHOH",
    ]
    speech_sfx = ''.join(speech_set)
    spell_speed = 30
    music_sfx = ["C6:1", "D#", "C#", "E", "D", "F", "F#"]
    # ピロリロリロロ　としゃべるパターンはコメントアウト
    # speech.sing(speech_sfx, speed=spell_speed)
    music.play(music_sfx)


while True:
    incoming = radio.receive()

    if button_a.is_pressed():
        incoming = '1'
    if button_b.is_pressed():
        incoming = '2'
    if button_a.is_pressed() and button_b.is_pressed():
        incoming = '3'

    if incoming == '1':
        display.show(Image.TRIANGLE)
        play_sfx()
        sleep(200)
        speech.say('MERA!',pitch=60, speed=72,mouth=128, throat=128)
    elif incoming == '2':
        display.show(Image.HEART)
        play_sfx()
        sleep(200)
        speech.say("HOI Me!")
    elif incoming == '3':
        display.show(Image.SKULL)
        play_sfx()
        sleep(200)
        speech.say("Beh Gih RA Mah!")

    sleep(100)