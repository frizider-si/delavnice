from RPi import GPIO
GPIO.setmode(GPIO.BOARD)
leds_pin = [11,12,13,15,16,18,22]

for x in range(0, len(leds_pin)):
	GPIO.setup(leds_pin[x], GPIO.OUT) # led out

from flask import Flask
from flask import request

app = Flask(__name__)
html = ""

for x in range(0, len(leds_pin)):
	html = html + """<a href="/ledOn/""" + str(leds_pin[x]) + """">ON D""" + str(x) + """!</a> """ 
	html = html + """<a href="/ledOff/""" + str(leds_pin[x]) + """">OFF D""" + str(x) + """!</a><br>"""

@app.route("/")
def zacetek():
	return html

@app.route("/ledOn/<number>")
def ledOn(number):
	GPIO.output(int(number), 1)
	return html

@app.route("/ledOff/<number>")
def ledOff(number):
	GPIO.output(int(number), 0)
	return html

app.run(host="192.168.1.25") 
