from flask import Flask, request
import json

app = Flask(__name__)

@app.route('/')
def routeGetRoot():
    return 'ok'

@app.route('/init')
def routeGetInit():
    deviceIp = request.form['ip']
    deviceType = request.form['type']
    deviceName = request.form['name']

    print ("ip : " + str(deviceIp))
    print ("type : " + str(deviceType))
    print ("name : " + str(deviceName))

app.run(debug=True, host='0.0.0.0')