from flask import Flask, request
import json

app = Flask(__name__)

@app.route('/')
def routeGetRoot():
    return 'ok'

app.run(debug=True)