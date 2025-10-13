# application.py
from flask import Flask, send_from_directory

app = Flask(__name__, static_folder='.')

@app.route('/')
def serve_index():
    return send_from_directory('.', 'index.html')

if __name__ == '__main__':
    # Run on port 8080 for AWS EB compatibility
    app.run(host='0.0.0.0', port=8080)
