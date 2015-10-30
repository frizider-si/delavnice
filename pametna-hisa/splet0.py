from RPi import GPIO
GPIO.setmode(GPIO.BOARD)

GPIO.setup(11, GPIO.OUT) 
GPIO.setup(12, GPIO.OUT)
GPIO.setup(13, GPIO.OUT)
GPIO.setup(15, GPIO.OUT)
GPIO.setup(16, GPIO.OUT)
GPIO.setup(18, GPIO.OUT)
GPIO.setup(22, GPIO.OUT)


from flask import Flask
from flask import request

app = Flask(__name__)

html = """<a href="/ledOn0">Prizgi led 0!</a> <a href="/ledOff0">Ugasni led 0!</a><br>
       	<a href="/ledOn1">Prizgi led 1!</a> <a href="/ledOff1">Ugasni led 1!</a><br>
	<a href="/ledOn2">Prizgi led 2!</a> <a href="/ledOff2">Ugasni led 2!</a><br>
	<a href="/ledOn3">Prizgi led 3!</a> <a href="/ledOff3">Ugasni led 3!</a><br>
	<a href="/ledOn4">Prizgi led 4!</a> <a href="/ledOff4">Ugasni led 4!</a><br>
	<a href="/ledOn5">Prizgi led 5!</a> <a href="/ledOff5">Ugasni led 5!</a><br>
	<a href="/ledOn6">Prizgi led 6!</a> <a href="/ledOff6">Ugasni led 6!</a><br>"""


@app.route("/")
def zacetek():
	return html


@app.route("/ledOn0")
def ledOn0():
	GPIO.output(11, 1)
	return html

@app.route("/ledOn1")
def ledOn1():
	GPIO.output(12, 1)
	return html

@app.route("/ledOn2")
def ledOn2():
	GPIO.output(13, 1)
	return html

@app.route("/ledOn3")
def ledOn3():
	GPIO.output(15, 1)
	return html

@app.route("/ledOn4")
def ledOn4():
	GPIO.output(16, 1)
	return html

@app.route("/ledOn5")
def ledOn5():
	GPIO.output(18, 1)
	return html

@app.route("/ledOn6")
def ledOn6():
	GPIO.output(22, 1)
	return html


@app.route("/ledOff0")
def ledOff0():
	GPIO.output(11, 0)
	return html

@app.route("/ledOff1")
def ledOff1():
	GPIO.output(12, 0)
	return html

@app.route("/ledOff2")
def ledOff2():
	GPIO.output(13, 0)
	return html

@app.route("/ledOff3")
def ledOff3():
	GPIO.output(15, 0)
	return html

@app.route("/ledOff4")
def ledOff4():
	GPIO.output(16, 0)
	return html

@app.route("/ledOff5")
def ledOff5():
	GPIO.output(18, 0)
	return html

@app.route("/ledOff6")
def ledOff6():
	GPIO.output(22, 0)
	return html



app.run(host="192.168.1.25") 
