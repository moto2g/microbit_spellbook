import radio
import speech
from microbit import *
import music

radio.on()
radio.config(group=8)

display.scroll('Speaker', wait=True, loop=False)
sleep(1000)
display.show(Image.YES)
music.set_tempo(ticks=6, bpm=230)

test_incoming = 1

def play_speech(spell):
    speech.say(spell, pitch=40, speed=75, mouth=120, throat=180)

def play_sfx():
    # ド・レ♯・ド♯・ミ・レ・ファ・ファ♯
    #music_sfx = ["C5:2", "D#:2", "C#:2", "E:2", "D:2", "F:2", "F#:2"]
    music_sfx = ["C5:1", "C", "D#", "D#", "C#", "C#", "E", "E", "D", "D", "F", "F", "F#", "F#"]
    music.play(music_sfx)

while True:
    incoming = radio.receive()

    if button_a.is_pressed():
        test_incoming += 1
        if test_incoming > 4:
            test_incoming = 1
        display.show(test_incoming)

    if button_b.is_pressed():
        incoming = str(test_incoming)

    if button_a.is_pressed() and button_b.is_pressed():
        incoming = '4'

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
        #speech.say("Beh Gih RA Mah!")
        speech.sing("#74BEH#58GIY#58RAH#52MAAAH")

    elif incoming == '4':
        display.show(Image.CLOCK12)
        play_sfx()
        sleep(200)
        speech.sing("#94ZAH#115RAH#120KIYIX")
        #speech.sing("#70ZAH#94RAH#98KIYIX")

    sleep(100)