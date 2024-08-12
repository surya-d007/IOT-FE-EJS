from flask_cors import CORS 
from flask import Flask, request, jsonify  # Import jsonify
import json

app = Flask(__name__)
CORS(app) 

@app.route('/receiveData', methods=['POST'])
def receive_data():

    data = request.data.decode('utf-8')
    Serialmonitor = data.split()  # Split the received data by space
    status = {
        "room1": Serialmonitor[0],
        "room2": Serialmonitor[1],
        "room3": Serialmonitor[2],
        "sensorStatus": Serialmonitor[3]
    }
    with open('sample.json', 'w') as json_file:
        json.dump(status, json_file, indent=4)  # Write the room status to JSON file
    print("Data received by Flask server and written to sample.json")
    return "Data received by Flask server"



@app.route('/status', methods=['GET'])
def get_status():
    try:
        with open('sample.json', 'r') as json_file:
            data = json.load(json_file)
        print("JSON data:", data)  # Print the JSON data to the console
        return jsonify(data)
    except FileNotFoundError:
        return "No data available", 404

    
if __name__ == '__main__':          
    app.run(host='0.0.0.0', port=5000)
